#include "AIControllable.h"
#include "Game Logic\PathFinding.h"
#include "Game Logic\WayPointSystem.h"

AIControllable::AIControllable(ControllableTemplate& aiTemplate, WaypointSystem* waypointSystem) 
	: Controllable(aiTemplate)
{
	m_pathFinder = new PathFinding();
	m_nextWaypoint = NULL;
	m_currentKnownWaypoint = NULL;
	m_waypointSystem = waypointSystem;
	m_waypointSystem == NULL ? m_goalWaypoint = NULL : m_goalWaypoint = m_waypointSystem->getWaypointAt(48);
	m_currentPath.clear();
	m_listOfWaypointsHighCost.push_back(4);
	m_listOfWaypointsHighCost.push_back(14);
	m_listOfWaypointsHighCost.push_back(24);
	setHighCostWaypointsToHigh();
}
AIControllable::~AIControllable()
{
	delete m_pathFinder;
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

	checkCollisionVolumes();

	if (m_currentKnownWaypoint == NULL)
	{
		m_currentKnownWaypoint = m_car->getCurrentWaypoint();
	}
	else if (m_currentKnownWaypoint->getId() != m_car->getCurrentWaypoint()->getId() && m_car->getCurrentWaypoint()->getId() != m_nextWaypoint->getId())
	{
		recalculatePath();
		m_currentKnownWaypoint = m_car->getCurrentWaypoint();

	}
	else if (m_currentKnownWaypoint->getId() != m_car->getCurrentWaypoint()->getId())
	{
		m_currentKnownWaypoint = m_car->getCurrentWaypoint();
	}

	if (m_currentPath.empty() && (m_nextWaypoint == NULL || m_car->getCurrentWaypoint()->getId() == m_goalWaypoint->getId()))
	{

		//if (m_car->getCurrentWaypoint()->getId() == m_goalWaypoint->getId())
		//{
		//	if (m_goalWaypoint->getId() == 15)
		//	{
		//		m_goalWaypoint = m_waypointSystem->getWaypointAt(48);
		//	}
		//	else if (m_goalWaypoint->getId() == 48)
		//	{
		//		m_goalWaypoint = m_waypointSystem->getWaypointAt(96);
		//	}
		//	else if (m_goalWaypoint->getId() == 96)
		//	{
		//		m_goalWaypoint = m_waypointSystem->getWaypointAt(41);
		//	}
		//	else if (m_goalWaypoint->getId() == 41)
		//	{
		//		m_goalWaypoint = m_waypointSystem->getWaypointAt(15);
		//	}
		//	//m_goalWaypoint->getId() == 38 ? m_goalWaypoint = m_waypointSystem->getWaypointAt(42) : m_goalWaypoint = m_waypointSystem->getWaypointAt(12);
		//	//std::cout << "The current goal is: " << m_goalWaypoint->getId() << "\n";
		//}
		recalculatePath();
	}
	else
	{
		//std::cout << "path exists\n";
		if (m_car->getCurrentWaypoint()->getId() == m_nextWaypoint->getId())
		{
			//std::cout << "Reached Next Waypoint\n";
			updateNextWaypoint();
		}

		if (m_car->getCurrentWaypoint()->getId() != m_goalWaypoint->getId())
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
			float amountOfDotProduct = glm::dot(forwardVector, vectorToNextWaypoint3);

			//std::cout << "length of forward: " << forwardVector.length() << " | " << "length of vectorToPosition: " << vectorToNextWaypoint3.length() << "\n";
			//std::cout << "Amount of dot product: " << amountOfDotProduct << "\n";
			float amountToSteerBy = fabs(amountOfDotProduct - 1);
			amountToSteerBy > 1.0 ? amountToSteerBy = 1.0 : amountToSteerBy = amountToSteerBy;
			float amountToAccelerate;
			amountToSteerBy < 0.5 ? amountToAccelerate = -((2 * amountToSteerBy) - 1) : amountToAccelerate = ((-2 * amountToSteerBy) + 1);

			accelerate(amountToAccelerate);

			//std::cout << "amount to accelerate: " << amountToAccelerate << " amount to steer by: " << amountToSteerBy<< "\n";
			//std::cout << "z value: " << crossProductResult.z << "\n";

			if (crossProductResult.y < 0)
			{
				//std::cout << "turning Left\n";
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_RIGHT, 0);
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_LEFT, amountToSteerBy);
			}
			else if (crossProductResult.y > 0)
			{
				//std::cout << "turning right\n";
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_LEFT, 0);
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_RIGHT, amountToSteerBy);
			}
			else
			{
				//std::cout << "Do not turn\n";
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_LEFT, 0);
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_RIGHT, 0);
			}

			//glm::normalize(vectorToNextWaypoint);
			//float dotVectorResult = glm::dot(vectorToNextWaypoint, m_car->getForwardVector());

			//m_car->getActor().getGlobalPose().
			//float cosineOfAngle = dotVectorResult / (vectorToNextWaypoint.length() *  m_car->getForwardVector().length());
			//float angleBetweenForwardAndNextWaypoint = glm::acos(cosineOfAngle);


			/*if (cosineOfAngle > 0)*/


		}
		}
	
		}
		else {
		m_car->respawn();
		m_currentPath.clear();
		m_currentPath = m_pathFinder->findPath(m_car->getCurrentWaypoint(),m_goalWaypoint);
		updateNextWaypoint();
	}
	}
	//if (m_car->getCurrentWaypoint() != NULL && m_nextWaypoint != NULL && m_goalWaypoint != NULL)
		//std::cout << "current: " << m_car->getCurrentWaypoint()->getId() << " | next : " << m_nextWaypoint->getId() << " | " << "goal: " << m_goalWaypoint->getId() << "\n";
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
		std::cout << m_currentPath[i]->getId() << ", ";
	}

	std::cout << "\n";

	updateNextWaypoint();
}

void AIControllable::accelerate(float amount)
{
	if (m_car->getCar().mDriveDynData.getCurrentGear() == PxVehicleGearsData::eREVERSE)
	{
		//std::cout << "changing gear\n";
		m_car->getCar().mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
	}

	//std::cout << "speed: " << m_car->getCar().computeForwardSpeed() << "\n";
	if (amount > 0)
	{
		//std::cout << "Applying acceleration : " << -amount << "\n";
		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_BRAKE, 0);
		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, amount);
	}
	else if (amount < 0 && m_car->getCar().computeForwardSpeed() > 10.0)
	{
		//std::cout << "Applying break with : " << -amount << "\n";
		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, 0);
		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_BRAKE, -amount);
	}
	else if (amount < 0 && m_car->getCar().computeForwardSpeed() < 10.0)
	{
		//std::cout << "Applying acceleration : " << -amount << "\n";
		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_BRAKE, 0);
		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, (-amount * 0.5));
	}
	else
	{
		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, 0);
		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_BRAKE, 0);
	}
}

void AIControllable::setCar(Car * toAdd)
{
	m_car = toAdd;
}

void AIControllable::setWaypointSystem(WaypointSystem* waypointSystem)
{
	m_waypointSystem = waypointSystem;
	m_goalWaypoint = m_waypointSystem->getWaypointAt(13);
}

void AIControllable::checkCollisionVolumes()
{
	if (m_car->isAtStartingCollisionVolume())
	{
		setHighCostWaypointsToHigh();
		m_goalWaypoint = m_waypointSystem->getWaypointAt(13);
		recalculatePath();
		m_car->setStartingCollisionVolumeFlag(false);
	}
	else if (m_car->isAtMidCollisionVolume())
	{
		setHighCostWaypointsToLow();
		m_goalWaypoint = m_waypointSystem->getWaypointAt(16);
		recalculatePath();
		m_car->setMidCollisionVolumeFlag(false);
	}
}

void AIControllable::setHighCostWaypointsToHigh()
{
	for (int i = 0; i < m_listOfWaypointsHighCost.size(); i++)
	{
		m_pathFinder->setWaypointCostOf(m_listOfWaypointsHighCost);
	}
}

void AIControllable::setHighCostWaypointsToLow()
{
	for (int i = 0; i < m_listOfWaypointsHighCost.size(); i++)
	{
		std::vector<int> temp;
		m_pathFinder->setWaypointCostOf(temp);
	}
}