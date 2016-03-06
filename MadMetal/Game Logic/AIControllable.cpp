#include "AIControllable.h"
#include "Game Logic\PathFinding.h"
#include "Game Logic\WayPointSystem.h"

AIControllable::AIControllable(ControllableTemplate& aiTemplate, WaypointSystem& waypointSystem) 
	: Controllable(aiTemplate)
	, m_waypointSystem(waypointSystem)
{
	m_pathFinder = new PathFinding();
	m_nextWaypoint = NULL;
	m_goalWaypoint = m_waypointSystem.getWaypointAt(7);
	m_currentPath.clear();
}
AIControllable::~AIControllable()
{
	delete m_pathFinder;
}

void AIControllable::playFrame(double dt)
{
	if (m_car->getCurrentWaypoint() == NULL)
	{
		return;
	}
	if (m_currentPath.empty() && (m_nextWaypoint == NULL || m_car->getCurrentWaypoint()->getId() == m_goalWaypoint->getId()))
	{

		if (m_car->getCurrentWaypoint()->getId() == m_goalWaypoint->getId())
		{
			m_goalWaypoint->getId() == 7 ? m_goalWaypoint = m_waypointSystem.getWaypointAt(23) : m_goalWaypoint = m_waypointSystem.getWaypointAt(7);
			//std::cout << "The current goal is: " << m_goalWaypoint->getId() << "\n";
		}
		std::cout << "The current goal is: " << m_goalWaypoint->getId() << "\n";
		m_currentPath = m_pathFinder->findPath(m_car->getCurrentWaypoint(), m_goalWaypoint);

		std::cout << "The optimal path is: ";

		for (int i = 0; i < m_currentPath.size(); i++)
		{
			std::cout << m_currentPath[i]->getId() << ", ";
		}

		//std::cout << "\n";
		updateNextWaypoint();

		//std::cout << "Current path is: ";

		//for (int i = 0; i < m_currentPath.size(); i++)
		//{
		//	std::cout << m_currentPath[i]->getId() << ", ";
		//}

		//std::cout << "\n";
		//std::cout << "next : " << m_nextWaypoint->getId() << "\n";

		//	std::cout << "updating path\n";

		//	std::cout << "Stupid Melvin\n";
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
			glm::vec4 vectorToNextWaypoint = glm::vec4(m_nextWaypoint->getPosition() - m_car->getPosition(), 1.0);
			glm::normalize(vectorToNextWaypoint);
			glm::vec4 vectorOfSideOfCar = m_car->getModelMatrix() * glm::vec4(1.0, 0.0, 0.0, 1.0);
			glm::normalize(vectorOfSideOfCar);
			float dotVectorResult = glm::dot(vectorToNextWaypoint, vectorOfSideOfCar);

			float amountToSteerBy = fabs(dotVectorResult - 1);
			amountToSteerBy > 1.0 ? amountToSteerBy = 1.0 : amountToSteerBy = amountToSteerBy;
			float amountToAccelerate;
			amountToSteerBy < 0.5 ? amountToAccelerate = -((2 * amountToSteerBy) - 1) : amountToAccelerate = ((-2 * amountToSteerBy) + 1);

			accelerate(amountToAccelerate);

			//std::cout << "amount to accelerate: " << amountToAccelerate << " amount to steer by: " << amountToSteerBy<< "\n";

			if (dotVectorResult > 0)
			{
				//std::cout << "turning Left\n";
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_RIGHT, 0);
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_LEFT, amountToSteerBy);
			}
			else if (dotVectorResult < 0)
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
	//if (m_car->getCurrentWaypoint() != NULL && m_nextWaypoint != NULL && m_goalWaypoint != NULL)
	//	std::cout << "current: " << m_car->getCurrentWaypoint()->getId() << " | next : " << m_nextWaypoint->getId() << " | " << "goal: " << m_goalWaypoint->getId() << "\n";
}

void AIControllable::updateNextWaypoint()
{
	if (!m_currentPath.empty())
	{
		m_nextWaypoint = m_currentPath[m_currentPath.size() - 1];
		m_currentPath.pop_back();
	}
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