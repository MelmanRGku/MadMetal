#include "WaypointSystem.h"

static const int WAYPOINT_RADIUS = 10;

WaypointSystem::WaypointSystem(GameFactory& gameFactory, int trackWidth, int trackLength) : m_gameFactory(gameFactory)
{
	float minLength = -trackWidth;
	float minWidth = -trackLength;

	std::vector<std::vector<Waypoint*>> waypointMap;

	int index = 0;
	for (int i = minWidth + WAYPOINT_RADIUS + 10; i < trackWidth; i += ((WAYPOINT_RADIUS+ 10)  * 2))
	{
		std::vector<Waypoint*> newVectorWaypoint;
		waypointMap.push_back(newVectorWaypoint);
		for (int j = minLength + WAYPOINT_RADIUS + 10; j < trackLength; j += ((WAYPOINT_RADIUS + 10) * 2))
		{
			Waypoint* tempWaypoint = dynamic_cast<Waypoint*>(m_gameFactory.makeObject(GameFactory::OBJECT_WAYPOINT, new PxTransform(i, -100, j), new PxSphereGeometry(static_cast<float>(WAYPOINT_RADIUS)), NULL));
			waypointMap[index].push_back(tempWaypoint);
			m_waypoints.push_back(tempWaypoint);
		}
		index++;
	}

	// Populate Waypoints
	for (int i = 0; i < waypointMap.size(); i++)
	{
		for (int j = 0; j < waypointMap[i].size(); j++)
		{
			// Row 1
			if ((i - 1) >= 0)
			{
				if ((j - 1) >= 0)
				{
					waypointMap[i][j]->addAdjecentWaypoint(waypointMap[i - 1][j - 1]);
				}

				waypointMap[i][j]->addAdjecentWaypoint(waypointMap[i - 1][j]);

				if ((j + 1) < waypointMap[i].size())
				{
					waypointMap[i][j]->addAdjecentWaypoint(waypointMap[i - 1][j + 1]);
				}
			}

			// Row 2
			if ((j - 1) >= 0)
			{
				waypointMap[i][j]->addAdjecentWaypoint(waypointMap[i][j - 1]);
			}

			if ((j + 1) < waypointMap[i].size())
			{
				waypointMap[i][j]->addAdjecentWaypoint(waypointMap[i][j + 1]);
			}

			//Row 3
			if ((i + 1) < waypointMap.size())
			{
				if ((j - 1) >= 0)
				{
					waypointMap[i][j]->addAdjecentWaypoint(waypointMap[i + 1][j - 1]);
				}

				waypointMap[i][j]->addAdjecentWaypoint(waypointMap[i + 1][j]);

				if ((j + 1) < waypointMap[i].size())
				{
					waypointMap[i][j]->addAdjecentWaypoint(waypointMap[i + 1][j + 1]);
				}
			}
		}
	}

	//for (int i = 0; i < m_waypoints.size(); i++)
	//{
	//	std::cout << "waypoint: " << m_waypoints[i]->getId() << " " << " and is connected to ";
	//	for (int k = 0; k < m_waypoints[i]->getListOfAdjacentWaypoints().size(); k++)
	//	{
	//		std::cout << m_waypoints[i]->getListOfAdjacentWaypoints().at(k)->getId() << ", ";
	//	}
	//	std::cout << "\n";
	//}

}

WaypointSystem::~WaypointSystem()
{
	for (unsigned int i = 0; i < m_waypoints.size(); i++)
	{
		delete m_waypoints[i];
	}
	m_waypoints.clear();
}