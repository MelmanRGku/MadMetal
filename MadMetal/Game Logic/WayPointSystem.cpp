#include "WaypointSystem.h"
#include "Game Logic\PathFinding.h"

static const int WAYPOINT_RADIUS = 35;

WaypointSystem::WaypointSystem(GameFactory& gameFactory, int trackWidth, int trackLength) : m_gameFactory(gameFactory)
{
	float minLength = -trackWidth;
	float minWidth = -trackLength;

	int index = 0;
	for (int i = minWidth + WAYPOINT_RADIUS + 5; i < trackWidth; i += ((WAYPOINT_RADIUS+ 5)  * 2))
	{
		std::vector<Waypoint*> newVectorWaypoint;
		m_waypointMap.push_back(newVectorWaypoint);
		for (int j = minLength + WAYPOINT_RADIUS + 5; j < trackLength; j += ((WAYPOINT_RADIUS + 5) * 2))
		{
			Waypoint* tempWaypoint = dynamic_cast<Waypoint*>(m_gameFactory.makeObject(GameFactory::OBJECT_WAYPOINT, new PxTransform(i, -100, j), new PxSphereGeometry(static_cast<float>(WAYPOINT_RADIUS)), NULL));
			m_waypointMap[index].push_back(tempWaypoint);
			m_waypoints.push_back(tempWaypoint);
		}
		index++;
	}


	std::cout << "number of waypoints" << m_waypoints.size() << "\n";
	std::cout << "width: " << trackWidth << " | " << "tack length: " << trackLength << "\n";
	// Populate Waypoints
	for (int i = 0; i < m_waypointMap.size(); i++)
	{
		for (int j = 0; j < m_waypointMap[i].size(); j++)
		{
			// Row 1
			if ((i - 1) >= 0)
			{
				if ((j - 1) >= 0)
				{
					m_waypointMap[i][j]->addAdjecentWaypoint(m_waypointMap[i - 1][j - 1]);
				}

				m_waypointMap[i][j]->addAdjecentWaypoint(m_waypointMap[i - 1][j]);

				if ((j + 1) < m_waypointMap[i].size())
				{
					m_waypointMap[i][j]->addAdjecentWaypoint(m_waypointMap[i - 1][j + 1]);
				}
			}

			// Row 2
			if ((j - 1) >= 0)
			{
				m_waypointMap[i][j]->addAdjecentWaypoint(m_waypointMap[i][j - 1]);
			}

			if ((j + 1) < m_waypointMap[i].size())
			{
				m_waypointMap[i][j]->addAdjecentWaypoint(m_waypointMap[i][j + 1]);
			}

			//Row 3
			if ((i + 1) < m_waypointMap.size())
			{
				if ((j - 1) >= 0)
				{
					m_waypointMap[i][j]->addAdjecentWaypoint(m_waypointMap[i + 1][j - 1]);
				}

				m_waypointMap[i][j]->addAdjecentWaypoint(m_waypointMap[i + 1][j]);

				if ((j + 1) < m_waypointMap[i].size())
				{
					m_waypointMap[i][j]->addAdjecentWaypoint(m_waypointMap[i + 1][j + 1]);
				}
			}
		}
	}

	//for (int i = 33; i < 37; i++)
	//{
	//	m_waypoints[i]->setValid(false);
	//}

	//for (int i = 0; i < m_waypoints.size(); i++)
	//{
	//	std::cout << "waypoint: " << m_waypoints[i]->getId() << " " << " and is connected to ";
	//	for (int k = 0; k < m_waypoints[i]->getListOfAdjacentWaypoints().size(); k++)
	//	{
	//		std::cout << m_waypoints[i]->getListOfAdjacentWaypoints().at(k)->getId() << ", ";
	//	}
	//	std::cout << "\n";
	//}

	//test();

}

WaypointSystem::~WaypointSystem()
{
	for (unsigned int i = 0; i < m_waypoints.size(); i++)
	{
		delete m_waypoints[i];
	}
	m_waypoints.clear();
}

void WaypointSystem::test()
{
	PathFinding* pathFinding = new PathFinding();

	std::vector<Waypoint*> result = pathFinding->findPath(m_waypoints[0], m_waypoints[46]);

	std::cout << "The optimal path is: ";

	for (int i = 0; i < result.size(); i++)
	{
		std::cout << result[i]->getId() << ", ";
	}

	std::cout << "\n";

	delete pathFinding;
}