#include "AIControllable.h"
#include "Game Logic\PathFinding.h"
#include "Game Logic\WayPointSystem.h"

AIControllable::AIControllable(ControllableTemplate& aiTemplate, WaypointSystem& waypointSystem) 
	: Controllable(aiTemplate)
	, m_waypointSystem(waypointSystem)
{
	m_pathFinder = new PathFinding();
	m_nextWaypoint = NULL;
	m_goalWaypoint = m_waypointSystem.getWaypointAt(8);
	m_currentPath.clear();
}
AIControllable::~AIControllable()
{
	delete m_pathFinder;
}

void AIControllable::playFrame(double dt)
{
	//std::cout << "Updating\n";
	if (m_currentPath.empty())
	{
		//std::cout << "empty path\n";
		if (m_car->getCurrentWaypoint() != NULL)
		{
			m_currentPath = m_pathFinder->findPath(m_car->getCurrentWaypoint(), m_goalWaypoint);
			updateNextWaypoint();
		}
	}
	else
	{
		//std::cout << "path exists\n";
		if (m_car->getCurrentWaypoint()->getId() == m_nextWaypoint->getId())
		{
			std::cout << "Reached Next Waypoint\n";
			updateNextWaypoint();
		}

		if (m_car->getCurrentWaypoint()->getId() != m_goalWaypoint->getId())
		{
			accelerate();
			glm::vec4 vectorToNextWaypoint = glm::vec4(m_nextWaypoint->getPosition() - m_car->getPosition(), 1.0);
			glm::normalize(vectorToNextWaypoint);
			glm::vec4 vectorOfSideOfCar = m_car->getModelMatrix() * glm::vec4(1.0, 0.0, 0.0,1.0);
			glm::normalize(vectorOfSideOfCar);

			float dotVectorResult = glm::dot(vectorToNextWaypoint, vectorOfSideOfCar);
			if (dotVectorResult > 0)
			{
				std::cout << "turning Left\n";
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_RIGHT, 0);
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_LEFT, 1.0);
			}
			else if (dotVectorResult < 0)
			{
				std::cout << "turning right\n";
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_LEFT, 0);
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_RIGHT, 1.0);
			}
			else
			{
				std::cout << "Do not turn\n";
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
		else
		{
			std::cout << "Resetting goal\n";
			m_goalWaypoint->getId() == 8 ? m_goalWaypoint = m_waypointSystem.getWaypointAt(16) : m_goalWaypoint = m_waypointSystem.getWaypointAt(8);

		}
	}
}

void AIControllable::updateNextWaypoint()
{
	if (!m_currentPath.empty())
	{
		m_nextWaypoint = m_currentPath[m_currentPath.size() - 1];
		m_currentPath.pop_back();
	}
}

void AIControllable::accelerate()
{
	if (m_car->getCar().mDriveDynData.getCurrentGear() == PxVehicleGearsData::eREVERSE)
	{
		//std::cout << "changing gear\n";
		m_car->getCar().mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
	}
	//std::cout << "moving\n";
	m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, 0.5);
}

void AIControllable::setCar(Car * toAdd)
{
	m_car = toAdd;
}