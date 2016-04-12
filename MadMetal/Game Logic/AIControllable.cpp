#include "AIControllable.h"
#include "Game Logic\PathFinding.h"
#include "Game Logic\WayPointSystem.h"
#include "Objects\CollisionVolume.h"
#include "Objects\Track.h"

static const float BACKUP_DAMPING = 0.8;
static const int NUMBER_OF_WRONG_HITS = 10; 
static const int REVERSE_TIMER_AMOUNT = 90;

AIControllable::AIControllable(ControllableTemplate& aiTemplate)
: Controllable(aiTemplate)
{
	m_needsToBackup = false;
	m_counter = 0;
	m_movementState = AiStateMovement::INITIAL_STATE;
	m_counterReverse = REVERSE_TIMER_AMOUNT;
}
AIControllable::~AIControllable()
{
	
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

void AIControllable::accelerateToNextCollisionVolume()
{
	PxVec3 newDirection = (m_car->getGoalCollisionVolume()->getActor().getGlobalPose().p - m_car->getActor().getGlobalPose().p).getNormalized();
	PxVec3 forwardVector = PxVec3(m_car->getForwardVector().x, m_car->getForwardVector().y, m_car->getForwardVector().z).getNormalized();
	

	PxVec3 crossProductResult = forwardVector.cross(newDirection);
	newDirection.y = 0;
	forwardVector.y = 0;
	newDirection = newDirection.getNormalized();
	forwardVector = forwardVector.getNormalized();

	float amountOfDotProduct = forwardVector.dot( newDirection);
	float amountToSteerBy = fabs(amountOfDotProduct - 1);
	amountToSteerBy > 1.0 ? amountToSteerBy = 1.0 : amountToSteerBy = amountToSteerBy;
	float amountToAccelerate;
	amountToSteerBy < 0.5 ? amountToAccelerate = -((2 * amountToSteerBy) - 1) : amountToAccelerate = ((-2 * amountToSteerBy) + 1);

	changeTurning(crossProductResult.y, amountToSteerBy * m_car->getCurrentCollisionVolume()->getSteeringDamping());
	accelerate(amountToAccelerate *  m_car->getCurrentCollisionVolume()->getSpeedDamping());
}

void AIControllable::reverse()
{
	PxVec3 newDirection = (m_car->getGoalCollisionVolume()->getActor().getGlobalPose().p - m_car->getActor().getGlobalPose().p).getNormalized();
	PxVec3 forwardVector = PxVec3(m_car->getForwardVector().x, m_car->getForwardVector().y, m_car->getForwardVector().z).getNormalized();


	PxVec3 crossProductResult = forwardVector.cross(newDirection);
	newDirection.y = 0;
	forwardVector.y = 0;
	newDirection = newDirection.getNormalized();
	forwardVector = forwardVector.getNormalized();

	float amountOfDotProduct = forwardVector.dot(newDirection);
	float amountToSteerBy = fabs(amountOfDotProduct - 1);
	amountToSteerBy > 1.0 ? amountToSteerBy = 1.0 : amountToSteerBy = amountToSteerBy;
	float amountToAccelerate;
	amountToSteerBy < 0.5 ? amountToAccelerate = -((2 * amountToSteerBy) - 1) : amountToAccelerate = ((-2 * amountToSteerBy) + 1);

	changeTurning(-crossProductResult.y, amountToSteerBy * BACKUP_DAMPING);
	backUp(amountToAccelerate);

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
				rotateTowardsNextCollisionVolume();
				m_movementState = AiStateMovement::MOVE_BACKWARDS;
			}
			// Move forward
			else
			{
				m_movementState = AiStateMovement::MOVE_FORWARD;
			}
			m_counter = 0;
		}
	}
	else
	{
		m_counter = 0;
	}
}

void AIControllable::rotateTowardsNextCollisionVolume()
{
	PxVec3 toCollisionVolume = (m_car->getCurrentCollisionVolume()->getActor().getGlobalPose().p- m_car->getActor().getGlobalPose().p).getNormalized();
	PxVec3 forwardVector = PxVec3(m_car->getForwardVector().x, m_car->getForwardVector().y, m_car->getForwardVector().z).getNormalized();

	PxVec3 crossProductResult = forwardVector.cross(toCollisionVolume);
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
		if (m_car->getCurrentCollisionVolume() != NULL)
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

		checkStuckInWall();

		if (m_needsToBackup)
		{
			m_movementState = AiStateMovement::MOVE_BACKWARDS;
		}
		else
		{
			accelerateToNextCollisionVolume();
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
		{
			m_needsToBackup = false;
			m_counter = 0;
			m_counterReverse = REVERSE_TIMER_AMOUNT;
			m_movementState = AiStateMovement::MOVE_FORWARD;
		}
		else
		{
			reverse();
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