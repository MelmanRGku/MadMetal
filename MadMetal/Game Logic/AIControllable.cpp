#include "AIControllable.h"
#include "Game Logic\PathFinding.h"
#include "Game Logic\WayPointSystem.h"

AIControllable::AIControllable(ControllableTemplate& aiTemplate, WaypointSystem& waypointSystem) 
	: Controllable(aiTemplate)
	, m_waypointSystem(waypointSystem)
{
	m_pathFinder = new PathFinding();
	m_nextWaypoint = NULL;
	m_goalWaypoint = waypointSystem.getWaypointAt(63);
}
AIControllable::~AIControllable()
{
	delete m_pathFinder;
}

void AIControllable::playFrame(double dt)
{
	if (m_currentPath.empty())
	{
		if (m_car->getCurrentWaypoint() != NULL)
		{
			m_currentPath = m_pathFinder->findPath(m_car->getCurrentWaypoint(), m_goalWaypoint);
			updateNextWaypoint();
		}
	}
	else
	{
		if (m_currentWaypoint->getId() != m_goalWaypoint->getId())
		{
			glm::vec3 vectorToNextWaypoint = m_nextWaypoint->getGlobalPose() - m_car->getGlobalPose();
			glm::normalize(vectorToNextWaypoint);
			float dotVectorResult = glm::dot(vectorToNextWaypoint, m_car->getForwardVector());

			m_car->getForwardVector().ro
			float cosineOfAngle = dotVectorResult / (vectorToNextWaypoint.length() *  m_car->getForwardVector().length());
			float angleBetweenForwardAndNextWaypoint = glm::acos(cosineOfAngle);


			if (cosineOfAngle > 0)


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