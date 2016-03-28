#include "AIControllable.h"
#include "Game Logic\PathFinding.h"
#include "Game Logic\WayPointSystem.h"
#include "Objects\Track.h"

AIControllable::AIControllable(ControllableTemplate& aiTemplate, Track& track)
	: Controllable(aiTemplate)
	, m_track(track)
{
	m_pathFinder = new PathFinding();
	m_nextWaypoint = NULL;
	m_currentKnownWaypoint = NULL;
	m_goalWaypoint = m_track.getWaypointAt(15);
	m_currentPath.clear();
	//m_listOfWaypointsHighCost.push_back(4);
	//m_listOfWaypointsHighCost.push_back(11);
	//m_listOfWaypointsHighCost.push_back(18);
	setHighCostWaypointsToHigh();
	m_needsToBackup = false;
	m_counter = 0;
}
AIControllable::~AIControllable()
{
	delete m_pathFinder;
}

void AIControllable::processFire(std::vector<Controllable *> *players) {

	glm::vec3 forwardVector = m_car->getForwardVector();
	forwardVector.y = 0;
	forwardVector = glm::normalize(forwardVector);
	for (unsigned int i = 0; i < players->size(); i++) {
		if (players->at(i) != this) {
			glm::vec3 vecToPlayer = players->at(i)->getCar()->getFullPosition() - m_car->getFullPosition();
			vecToPlayer.y = 0;
			vecToPlayer = glm::normalize(vecToPlayer);
			if (glm::dot(vecToPlayer, forwardVector) > .9) {
				if (m_car->superReady()) {
					m_car->useSuper();
				}
				m_car->fire();
			}
		}
	}

}

void AIControllable::playFrame(double dt)
{
	
	if (!m_controlsPaused) {
	if (m_car->isAlive())
	{
	if (m_car->getCurrentWaypoint() == NULL || m_goalWaypoint == NULL)
	{
		return;
	}


	//checkCollisionVolumes();


	if (m_currentKnownWaypoint == NULL)
	{
		m_currentKnownWaypoint = m_car->getCurrentWaypoint();
	}
	else if (m_currentKnownWaypoint->getIndex() != m_car->getCurrentWaypoint()->getIndex() && m_needsToBackup)
	{
		m_needsToBackup = false;
		recalculatePath();
		m_currentKnownWaypoint = m_car->getCurrentWaypoint();
		m_counter = 0;
	}
	else if (m_currentKnownWaypoint->getIndex() != m_car->getCurrentWaypoint()->getIndex() && m_car->getCurrentWaypoint()->getIndex() != m_nextWaypoint->getIndex())
	{
		recalculatePath();
		m_currentKnownWaypoint = m_car->getCurrentWaypoint();
	}
	else if (m_currentKnownWaypoint->getIndex() != m_car->getCurrentWaypoint()->getIndex())
	{
		m_currentKnownWaypoint = m_car->getCurrentWaypoint();
	}

	if (m_currentPath.empty() && (m_nextWaypoint == NULL || m_car->getCurrentWaypoint()->getIndex() == m_goalWaypoint->getIndex()))
	{
		if (m_goalWaypoint->getIndex() == 15)
		{
			m_goalWaypoint = m_track.getWaypointAt(367);
			recalculatePath();
		}
		//else if (m_goalWaypoint->getIndex() == 206)
		//{
		//	m_goalWaypoint = m_track.getWaypointAt(367);
		//	recalculatePath();
		//}
		else if (m_goalWaypoint->getIndex() == 367)
		{
			m_goalWaypoint = m_track.getWaypointAt(550);
			recalculatePath();
		}
		else if (m_goalWaypoint->getIndex() == 550)
		{
			m_goalWaypoint = m_track.getWaypointAt(657);
			recalculatePath();
		}
		else if (m_goalWaypoint->getIndex() == 657)
		{
			m_goalWaypoint = m_track.getWaypointAt(813);
			recalculatePath();
		}
		else if (m_goalWaypoint->getIndex() == 813)
		{
			m_goalWaypoint = m_track.getWaypointAt(716);
			recalculatePath();
		}
		else if (m_goalWaypoint->getIndex() == 716)
		{
			m_goalWaypoint = m_track.getWaypointAt(895);
			recalculatePath();
		}
		else if (m_goalWaypoint->getIndex() == 895)
		{
			m_goalWaypoint = m_track.getWaypointAt(953);
			recalculatePath();
		}
		else if (m_goalWaypoint->getIndex() == 953)
		{
			m_goalWaypoint = m_track.getWaypointAt(1003);
			recalculatePath();
		}
		else if (m_goalWaypoint->getIndex() == 1003)
		{
			m_goalWaypoint = m_track.getWaypointAt(1074);
			recalculatePath();
		}
		else if (m_goalWaypoint->getIndex() == 1074)
		{
			m_goalWaypoint = m_track.getWaypointAt(1133);
			recalculatePath();
		}
		else if (m_goalWaypoint->getIndex() == 1133)
		{
			m_goalWaypoint = m_track.getWaypointAt(15);
			recalculatePath();
		}

		//recalculatePath();
	}
	else
	{

		//std::cout << "path exists\n";
		if (m_car->getCurrentWaypoint()->getIndex() == m_nextWaypoint->getIndex())
		{
			//std::cout << "Reached Next Waypoint\n";
			updateNextWaypoint();
		}
		float engineRotationSpeed = static_cast<float>(m_car->getCar().mDriveDynData.getEngineRotationSpeed());
		float forwardSpeed = static_cast<float>(m_car->getCar().computeForwardSpeed());
		//std::cout << "rotation speed:" << engineRotationSpeed << "\n";
		//std::cout << "linear speed:" << forwardSpeed << "\n";

		// Car is stuck in a wall
		if (engineRotationSpeed > 50.0 &&
			m_car->getCar().computeForwardSpeed() < 0.5)
		{
			m_counter++;
			if (m_counter > 120)
			{
				m_needsToBackup = !m_needsToBackup;
				if (m_needsToBackup)
				{
					m_currentKnownWaypoint = m_car->getCurrentWaypoint();
					if (m_car->getLastWaypoint() != NULL)
					{
						m_nextWaypoint = m_car->getLastWaypoint();
					}
					else
					{
						m_nextWaypoint = m_track.getWaypointAt(13);
					}
				}
				else
				{
					recalculatePath();
					m_currentKnownWaypoint = m_car->getCurrentWaypoint();
				}
				m_counter = 0;
			}
		}

		if (m_car->getCurrentWaypoint()->getIndex() != m_goalWaypoint->getIndex())
		{
			if (m_needsToBackup)
			{
				reverseToPreviousWaypoint();
			}
			else
			{
				accelerateToNextWaypoint();
			}
		}
	}
		
		} else {
		
		m_currentPath.clear();
		m_currentPath = m_pathFinder->findPath(m_car->getCurrentWaypoint(),m_goalWaypoint);
		updateNextWaypoint();
	}
	}
	//if (m_car->getCurrentWaypoint() != NULL && m_nextWaypoint != NULL && m_goalWaypoint != NULL)
		//std::cout << "current: " << m_car->getCurrentWaypoint()->getIndex() << " | next : " << m_nextWaypoint->getIndex() << " | " << "goal: " << m_goalWaypoint->getIndex() << "\n";
}

void AIControllable::accelerateToNextWaypoint()
{
	//glm::vec4 vectorToNextWaypoint4 = glm::vec4(m_nextWaypoint->getPosition() - m_car->getPosition(), 1.0);
	glm::vec3 vectorToNextWaypoint3 = glm::vec3(m_nextWaypoint->getPosition() - m_car->getPosition());
	//glm::normalize(vectorToNextWaypoint4);
	vectorToNextWaypoint3 = glm::normalize(vectorToNextWaypoint3);
	//glm::vec4 vectorOfSideOfCar = m_car->getModelMatrix() * glm::vec4(1.0, 0.0, 0.0, 1.0);
	//glm::normalize(vectorOfSideOfCar);
	glm::vec3 forwardVector = m_car->getForwardVector();
	forwardVector = glm::normalize(forwardVector);

	glm::vec3 crossProductResult = glm::cross(forwardVector, vectorToNextWaypoint3);
	//float dotVectorResult = - glm::dot(vectorToNextWaypoint4, vectorOfSideOfCar);
	vectorToNextWaypoint3.y = 0;
	forwardVector.y = 0;
	vectorToNextWaypoint3 = glm::normalize(vectorToNextWaypoint3);
	forwardVector = glm::normalize(forwardVector);
	float amountOfDotProduct = glm::dot(forwardVector, vectorToNextWaypoint3);


	//std::cout << "length of forward: " << forwardVector.length() << " | " << "length of vectorToPosition: " << vectorToNextWaypoint3.length() << "\n";
	//std::cout << "Amount of dot product: " << amountOfDotProduct << "\n";
	float amountToSteerBy = fabs(amountOfDotProduct - 1);
	amountToSteerBy > 1.0 ? amountToSteerBy = 1.0 : amountToSteerBy = amountToSteerBy;
	float amountToAccelerate;
	amountToSteerBy < 0.5 ? amountToAccelerate = -((2 * amountToSteerBy) - 1) : amountToAccelerate = ((-2 * amountToSteerBy) + 1);

	changeTurning(crossProductResult.y, amountToSteerBy);
	accelerate(amountToAccelerate * 0.65);

	//std::cout << "amount to accelerate: " << amountToAccelerate << " amount to steer by: " << amountToSteerBy<< "\n";
	//std::cout << "z value: " << crossProductResult.z << "\n";
}

void AIControllable::reverseToPreviousWaypoint()
{
	//glm::vec4 vectorToNextWaypoint4 = glm::vec4(m_nextWaypoint->getPosition() - m_car->getPosition(), 1.0);
	glm::vec3 vectorToNextWaypoint3 = glm::vec3(m_nextWaypoint->getPosition() - m_car->getPosition());
	//glm::normalize(vectorToNextWaypoint4);
	vectorToNextWaypoint3 = glm::normalize(vectorToNextWaypoint3);
	//glm::vec4 vectorOfSideOfCar = m_car->getModelMatrix() * glm::vec4(1.0, 0.0, 0.0, 1.0);
	//glm::normalize(vectorOfSideOfCar);
	glm::vec3 forwardVector = m_car->getForwardVector();
	glm::vec3 reverseForwardVector = -forwardVector;
	reverseForwardVector = glm::normalize(reverseForwardVector);

	glm::vec3 crossProductResult = glm::cross(reverseForwardVector, vectorToNextWaypoint3);
	//float dotVectorResult = - glm::dot(vectorToNextWaypoint4, vectorOfSideOfCar);
	vectorToNextWaypoint3.y = 0;
	reverseForwardVector.y = 0;
	vectorToNextWaypoint3 = glm::normalize(vectorToNextWaypoint3);
	reverseForwardVector = glm::normalize(reverseForwardVector);
	float amountOfDotProduct = glm::dot(reverseForwardVector, vectorToNextWaypoint3);


	//std::cout << "length of forward: " << forwardVector.length() << " | " << "length of vectorToPosition: " << vectorToNextWaypoint3.length() << "\n";
	//std::cout << "Amount of dot product: " << amountOfDotProduct << "\n";
	float amountToSteerBy = fabs(amountOfDotProduct - 1);
	amountToSteerBy > 1.0 ? amountToSteerBy = 1.0 : amountToSteerBy = amountToSteerBy;
	float amountToAccelerate;
	amountToSteerBy < 0.5 ? amountToAccelerate = -((2 * amountToSteerBy) - 1) : amountToAccelerate = ((-2 * amountToSteerBy) + 1);

	changeTurning(-crossProductResult.y, amountToSteerBy);
	backUp(amountToAccelerate);

	//std::cout << "amount to accelerate: " << amountToAccelerate << " amount to steer by: " << amountToSteerBy<< "\n";
	//std::cout << "z value: " << crossProductResult.z << "\n";
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

	//std::cout << "THe new path is: ";

	//for (int i = 0; i < m_currentPath.size(); i++)
	//{
	//	std::cout << m_currentPath[i]->getIndex() << ", ";
	//}

	//std::cout << "\n";
	updateNextWaypoint();
}

void AIControllable::accelerate(float amount)
{
	if (m_car->getCar().mDriveDynData.getCurrentGear() == PxVehicleGearsData::eREVERSE)
	{
		//std::cout << "changing gear\n";
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
	if (m_car->isAtStartingCollisionVolume())
	{
		setHighCostWaypointsToHigh();
		m_goalWaypoint = m_track.getWaypointAt(10);
		recalculatePath();

		m_car->setStartingCollisionVolumeFlag(false);
	}
	else if (m_car->isAtMidCollisionVolume())
	{
		setHighCostWaypointsToLow();
		m_goalWaypoint = m_track.getWaypointAt(13);
		recalculatePath();
		
		m_car->setMidCollisionVolumeFlag(false);
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
	if (amount > 0.3)
	{
		//std::cout << "Applying acceleration : " << -amount << "\n";
		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_BRAKE, 0);
		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, amount);
	}
	else if (amount < 0.3 && m_car->getCar().computeForwardSpeed() > 10.0)
	{
		//std::cout << "Applying break with : " << -amount << "\n";
		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, 0.0);
		if (amount < 0)
		{
			m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_BRAKE, -amount);
		}
		else
		{
			m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_BRAKE, amount);
		}
	}
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