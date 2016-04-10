#include "AIControllable.h"
#include "Game Logic\PathFinding.h"
#include "Game Logic\WayPointSystem.h"
#include "Objects\CollisionVolume.h"
#include "Objects\Track.h"

static const float BACKUP_DAMPING = 0.7;
static const int NUMBER_OF_WRONG_HITS = 10; 

AIControllable::AIControllable(ControllableTemplate& aiTemplate, Track& track)
	: Controllable(aiTemplate)
	, m_track(track)
{
	m_pathFinder = new PathFinding();
	m_nextWaypoint = NULL;
	m_currentKnownWaypoint = NULL;
	m_lastKnowCollisionVolue = NULL;
	m_goalWaypoint = m_track.getWaypointAt(1946);
	m_currentPath.clear();
	setHighCostWaypointsToHigh();
	m_needsToBackup = false;
	m_counter = 0;
	m_movementState = AiStateMovement::INITIAL_STATE;
	m_speedDamping = 1.0;
	m_steeringDamping = 1.0;
	m_counterReverse = 60;
	m_wrongHits = NUMBER_OF_WRONG_HITS;
}
AIControllable::~AIControllable()
{
	delete m_pathFinder;
}

void AIControllable::processPowerups() {
	if (m_car->getHeldPowerUp() == PowerUpType::ATTACK) {
		if (m_car->getHealthRemaining() <= 50) {
			m_car->usePowerUp();
		}
	}
	else if (m_car->getHeldPowerUp() == PowerUpType::SPEED) {
		if (m_car->getCar().computeForwardSpeed() > 70) {
			m_car->usePowerUp();
		}
	}
	else if (m_car->getHeldPowerUp() == PowerUpType::DEFENSE) {
		if (m_car->getTimeSinceLastTimeHit() > 0.1f && m_car->getTimeSinceLastTimeHit() < .5f) {
			m_car->usePowerUp();
		}
	}
}

void AIControllable::processFire(std::vector<Controllable *> *players) {
	if (!m_controlsPaused) {
		glm::vec3 forwardVector = m_car->getForwardVector();
		forwardVector.y = 0;
		forwardVector = glm::normalize(forwardVector);
		for (unsigned int i = 0; i < players->size(); i++) {
			if (players->at(i) != this && players->at(i)->getCar()->getInvinsibilityTimeRemaining() <= 0.5f) {
				glm::vec3 vecToPlayer = players->at(i)->getCar()->getFullPosition() - m_car->getFullPosition();
				float distance = glm::length(vecToPlayer);
				vecToPlayer.y = 0;
				vecToPlayer = glm::normalize(vecToPlayer);
				if (glm::dot(vecToPlayer, forwardVector) > .9 && distance <= 300) {
					if (m_car->superReady()) {
						m_car->useSuper();
					}
					m_car->fire();
				}
			}
		}
	}

}

void AIControllable::playFrame(double dt)
{
	updateMovementState();
}

void AIControllable::accelerateToNextWaypoint()
{
	glm::vec3 vectorToNextWaypoint3 = glm::vec3(m_nextWaypoint->getPosition() - m_car->getPosition());
	vectorToNextWaypoint3 = glm::normalize(vectorToNextWaypoint3);
	glm::vec3 forwardVector = m_car->getForwardVector();
	forwardVector = glm::normalize(forwardVector);

	glm::vec3 crossProductResult = glm::cross(forwardVector, vectorToNextWaypoint3);
	vectorToNextWaypoint3.y = 0;
	forwardVector.y = 0;
	vectorToNextWaypoint3 = glm::normalize(vectorToNextWaypoint3);
	forwardVector = glm::normalize(forwardVector);
	float amountOfDotProduct = glm::dot(forwardVector, vectorToNextWaypoint3);
	float amountToSteerBy = fabs(amountOfDotProduct - 1);
	amountToSteerBy > 1.0 ? amountToSteerBy = 1.0 : amountToSteerBy = amountToSteerBy;
	float amountToAccelerate;
	amountToSteerBy < 0.5 ? amountToAccelerate = -((2 * amountToSteerBy) - 1) : amountToAccelerate = ((-2 * amountToSteerBy) + 1);

	changeTurning(crossProductResult.y, amountToSteerBy * m_steeringDamping);
	accelerate(amountToAccelerate * m_speedDamping);
}

void AIControllable::reverseToPreviousWaypoint()
{
	glm::vec3 vectorToNextWaypoint3 = glm::vec3(m_nextWaypoint->getPosition() - m_car->getPosition());

	vectorToNextWaypoint3 = glm::normalize(vectorToNextWaypoint3);
	glm::vec3 forwardVector = m_car->getForwardVector();
	glm::vec3 reverseForwardVector = -forwardVector;
	reverseForwardVector = glm::normalize(reverseForwardVector);

	glm::vec3 crossProductResult = glm::cross(reverseForwardVector, vectorToNextWaypoint3);
	vectorToNextWaypoint3.y = 0;
	reverseForwardVector.y = 0;
	vectorToNextWaypoint3 = glm::normalize(vectorToNextWaypoint3);
	reverseForwardVector = glm::normalize(reverseForwardVector);
	float amountOfDotProduct = glm::dot(reverseForwardVector, vectorToNextWaypoint3);
	float amountToSteerBy = fabs(amountOfDotProduct - 1);
	amountToSteerBy > 1.0 ? amountToSteerBy = 1.0 : amountToSteerBy = amountToSteerBy;
	float amountToAccelerate;
	amountToSteerBy < 0.5 ? amountToAccelerate = -((2 * amountToSteerBy) - 1) : amountToAccelerate = ((-2 * amountToSteerBy) + 1);

	changeTurning(-crossProductResult.y, amountToSteerBy * BACKUP_DAMPING);
	backUp(amountToAccelerate);

}

void AIControllable::updateNextWaypoint()
{
	if (!m_currentPath.empty())
	{
		m_nextWaypoint = m_currentPath[m_currentPath.size() - 1];
		m_currentPath.pop_back();
	}
}

void AIControllable::recalculatePath()
{
	m_currentPath.clear();
	m_currentPath = m_pathFinder->findPath(m_car->getCurrentWaypoint(), m_goalWaypoint);

	std::cout << "THe new path is: ";

	for (int i = 0; i < m_currentPath.size(); i++)
	{
		std::cout << m_currentPath[i]->getIndex() << ", ";
	}

	std::cout << "\n";
	updateNextWaypoint();
}

void AIControllable::accelerate(float amount)
{
	if (m_car->getCar().mDriveDynData.getCurrentGear() == PxVehicleGearsData::eREVERSE)
	{
		m_car->getCar().mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
	}
	if (m_car->getCar().computeForwardSpeed() > 0)
	{
		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_BRAKE, 1);
	}
	
	processInputAcceleration(amount);
}

void AIControllable::backUp(float amount)
{
	if (m_car->getCar().computeForwardSpeed() > 0)
	{
		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_BRAKE, 1);
	}
	else
	{
		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_BRAKE, 0);
		if (m_car->getCar().mDriveDynData.getCurrentGear() != PxVehicleGearsData::eREVERSE) 
		{
			m_car->getCar().mDriveDynData.forceGearChange(PxVehicleGearsData::eREVERSE);
		}
		if (m_car->getCar().mDriveDynData.getCurrentGear() == PxVehicleGearsData::eNEUTRAL)
		{
			m_car->getCar().getRigidDynamicActor()->addForce(PxVec3(0, -1, 0));
		}
		processInputAcceleration(amount);
	}
}

void AIControllable::setCar(Car * toAdd)
{
	m_car = toAdd;
}


void AIControllable::checkCollisionVolumes()
{
	if (m_car->getLastHitCollisionVolume() == NULL)
	{
		return;
	}
	else
	{
		if (m_lastKnowCollisionVolue == NULL)
		{
			m_lastKnowCollisionVolue = m_car->getLastHitCollisionVolume();
			m_goalWaypoint = m_lastKnowCollisionVolue->getGoalWaypointIndex();
			m_speedDamping = m_lastKnowCollisionVolue->getSpeedDamping();
			m_steeringDamping = m_lastKnowCollisionVolue->getSteeringDamping();
		}
		else if (m_lastKnowCollisionVolue != m_car->getLastHitCollisionVolume())
		{
			m_lastKnowCollisionVolue = m_car->getLastHitCollisionVolume();
			m_goalWaypoint = m_lastKnowCollisionVolue->getGoalWaypointIndex();
			recalculatePath();
			m_speedDamping = m_lastKnowCollisionVolue->getSpeedDamping();
			m_steeringDamping = m_lastKnowCollisionVolue->getSteeringDamping();
		}
	}

}

void AIControllable::setHighCostWaypointsToHigh()
{
	for (int i = 0; i < m_listOfWaypointsHighCost.size(); i++)
	{
		//m_pathFinder->setWaypointCostOf(m_listOfWaypointsHighCost);
	}
}

void AIControllable::setHighCostWaypointsToLow()
{
	for (int i = 0; i < m_listOfWaypointsHighCost.size(); i++)
	{
		std::vector<int> temp;
		//m_pathFinder->setWaypointCostOf(temp);
	}
}

void AIControllable::processInputAcceleration(float amount)
{
	if (m_car->getCar().getRigidDynamicActor()->isSleeping())
		m_car->getCar().getRigidDynamicActor()->wakeUp();

		if (amount > 0.1)
		{
			//std::cout << "Applying acceleration : " << -amount << "\n";
			m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_BRAKE, 0);
			m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, amount);
		}
		//else if (amount < 0.1 && m_car->getCar().computeForwardSpeed() > 10.0)
		//{
		//	//std::cout << "Applying break with : " << -amount << "\n";
		//	m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, 0.0);
		//	if (amount < 0)
		//	{
		//		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_BRAKE, -amount);
		//	}
		//	else
		//	{
		//		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_BRAKE, amount);
		//	}
		//}
		else if (amount < 0 && m_car->getCar().computeForwardSpeed() < 20.0)
		{
			//std::cout << "Applying acceleration : " << -amount << "\n";
			m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_BRAKE, 0);
			m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, (-amount));
		}
		else
		{
			m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, 0);
			m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_BRAKE, 0);
		}
}

void AIControllable::changeTurning(float turningDirectionValue, float turningAmountValue)
{
	if (m_car->getCar().getRigidDynamicActor()->isSleeping()) 
		m_car->getCar().getRigidDynamicActor()->wakeUp();
		if (turningDirectionValue < 0)
		{
			//std::cout << "turning Left\n";
			m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_RIGHT, 0);
			m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_LEFT, turningAmountValue);
		}
		else if (turningDirectionValue > 0)
		{
			//std::cout << "turning right\n";
			m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_LEFT, 0);
			m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_RIGHT, turningAmountValue);
		}
		else
		{
			//std::cout << "Do not turn\n";
			m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_LEFT, 0);
			m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_RIGHT, 0);
		}
}

void AIControllable::checkStuckInWall()
{
	float engineRotationSpeed = static_cast<float>(m_car->getCar().mDriveDynData.getEngineRotationSpeed());
	float forwardSpeed = static_cast<float>(m_car->getCar().computeForwardSpeed());
	// Car is stuck in a wall
	if (engineRotationSpeed > 50.0 &&
		forwardSpeed < 5.0 &&
		!(m_car->getInvinsibilityTimeRemaining() > 0))
	{
		m_counter++;
		if (m_counter > 30)
		{
			m_needsToBackup = !m_needsToBackup;
			if (m_needsToBackup)
			{
				rotateTowardsNextWaypoint();
				m_movementState = AiStateMovement::MOVE_BACKWARDS;
				m_currentKnownWaypoint = m_car->getCurrentWaypoint();
				// Reverse to Last Waypoint
				if (m_car->getLastWaypoint() != NULL)
				{
					m_nextWaypoint = m_car->getLastWaypoint();
				}
				else
				{
					m_nextWaypoint = m_lastKnowCollisionVolue->getCurrentWaypointIndex();
				}

			}
			// Move forward
			else
			{
				m_movementState = AiStateMovement::MOVE_FORWARD;
				recalculatePath();
				m_currentKnownWaypoint = m_car->getCurrentWaypoint();
			}
			m_counter = 0;
		}
	}
	else
	{
		m_counter = 0;
	}
}

void AIControllable::rotateTowardsNextWaypoint()
{
	glm::vec3 vectorToNextWaypoint3 = glm::vec3(m_nextWaypoint->getPosition() - m_car->getPosition());
	vectorToNextWaypoint3 = glm::normalize(vectorToNextWaypoint3);
	glm::vec3 forwardVector = m_car->getForwardVector();
	forwardVector = glm::normalize(forwardVector);

	glm::vec3 crossProductResult = glm::cross(forwardVector, vectorToNextWaypoint3);
	PxQuat tempQauternion;
	if (crossProductResult.y > 0)
	{
		std::cout << "turning right" << std::endl;
		tempQauternion = PxQuat(0.0873, PxVec3(0, 1, 0));
	}
	else if (crossProductResult.y < 0)
	{
		tempQauternion = PxQuat(-0.0873, PxVec3(0, 1, 0));
		std::cout << "turning left" << std::endl;
	}
	m_car->getCar().getRigidDynamicActor()->setGlobalPose(PxTransform(m_car->getCar().getRigidDynamicActor()->getGlobalPose().p, m_car->getCar().getRigidDynamicActor()->getGlobalPose().q * tempQauternion));
}

void AIControllable::updateMovementState()
{
	switch (m_movementState)
	{
	case AiStateMovement::INITIAL_STATE:
		if (m_currentKnownWaypoint == NULL)
		{
			m_currentKnownWaypoint = m_car->getCurrentWaypoint();
		}
		if (m_car->getCurrentWaypoint() != NULL && m_goalWaypoint != NULL)
		{
			recalculatePath();
		}
		if (m_nextWaypoint != NULL && !m_currentPath.empty())
		{
			m_movementState = AiStateMovement::CONTROLS_PAUSED;
		}
		break;
	case AiStateMovement::CONTROLS_PAUSED:
		if (!m_controlsPaused)
		{
			if (m_needsToBackup)
			{
				m_movementState = AiStateMovement::MOVE_BACKWARDS;
			}
			else
			{
				m_movementState = AiStateMovement::MOVE_FORWARD;
			}
		}
		break;
	case AiStateMovement::MOVE_FORWARD:

		if (m_controlsPaused)
		{
			m_movementState = AiStateMovement::CONTROLS_PAUSED;
			break;
		}
		if (!m_car->isAlive())
		{
			m_movementState = AiStateMovement::DEAD;
			break;
		}

		checkCollisionVolumes();

		// Waypoint hit is not the next waypoint
		if (m_currentKnownWaypoint->getIndex() != m_car->getCurrentWaypoint()->getIndex() &&
			m_car->getCurrentWaypoint()->getIndex() != m_nextWaypoint->getIndex())
		{
			m_wrongHits--;
			if (m_wrongHits <= 0)
			{
				recalculatePath();
			}
			//m_currentKnownWaypoint = m_car->getCurrentWaypoint();
		}
		// Hit the goal node
		if (m_car->getCurrentWaypoint()->getIndex() == m_goalWaypoint->getIndex())
		{
			recalculatePath();
		}
		// Update the last known waypoint
		if (m_currentKnownWaypoint->getIndex() != m_car->getCurrentWaypoint()->getIndex())
		{
			m_currentKnownWaypoint = m_car->getCurrentWaypoint();
		}

		if (m_car->getCurrentWaypoint()->getIndex() == m_nextWaypoint->getIndex())
		{
			//std::cout << "Reached Next Waypoint\n";
			m_wrongHits = NUMBER_OF_WRONG_HITS;
			updateNextWaypoint();
		}

		checkStuckInWall();

		if (m_needsToBackup)
		{
			m_movementState = AiStateMovement::MOVE_BACKWARDS;
		}
		else
		{
			accelerateToNextWaypoint();
		}

		break;
	case AiStateMovement::MOVE_BACKWARDS:
		m_counterReverse--;
		if (m_controlsPaused)
		{
			m_movementState = AiStateMovement::CONTROLS_PAUSED;
			break;
		}
		if (!m_car->isAlive())
		{
			m_movementState = AiStateMovement::DEAD;
			break;
		}
		if (m_counterReverse <= 0)
		//if (m_currentKnownWaypoint->getIndex() != m_car->getCurrentWaypoint()->getIndex() &&
		//	m_car->getCurrentWaypoint()->isValid())
		{
			recalculatePath();
			m_needsToBackup = false;
			m_currentKnownWaypoint = m_car->getCurrentWaypoint();
			m_counter = 0;
			m_counterReverse = 60;
			m_movementState = AiStateMovement::MOVE_FORWARD;
		}
		else
		{
			reverseToPreviousWaypoint();
		}

		break;
	case AiStateMovement::DEAD:
		if (m_car->isAlive())
		{
				if (m_needsToBackup)
				{
					m_movementState = AiStateMovement::MOVE_BACKWARDS;
				}
				else
				{
					m_movementState = AiStateMovement::MOVE_FORWARD;
				}

		}
		break;
	}

}