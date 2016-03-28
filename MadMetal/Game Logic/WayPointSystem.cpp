#include "WaypointSystem.h"
#include "Game Logic\PathFinding.h"
#include "Factory\GameFactory.h"

static const float WAYPOINT_WIDTH_COLLISION = 8;
static const float WAYPOINT_LENGTH_COLLISION = 8;
static const float WAYPOINT_TRUE_WIDTH = 10;
static const float WAYPOINT_TRUE_LENGTH = 10;

WaypointSystem::WaypointSystem(int trackWidthMin, int trackWidthMax, int trackLengthMin, int trackLengthMax, int yposition, Boundry startingPosition)
{
	int index = 0;
	int numberOfRows = 0;
	switch (startingPosition)
	{
	case TOP:
		for (int i = trackLengthMin + WAYPOINT_TRUE_LENGTH; i < trackLengthMax; i += ((WAYPOINT_TRUE_LENGTH) * 2))
		{
			std::vector<Waypoint*> newVectorWaypoint;
			m_waypointMap.push_back(newVectorWaypoint);
			for (int j = trackWidthMin + WAYPOINT_TRUE_WIDTH; j < trackWidthMax; j += ((WAYPOINT_TRUE_WIDTH)* 2))
			{
				PxGeometry **geom = new PxGeometry *[1];
				geom[0] = new PxBoxGeometry(PxVec3(WAYPOINT_LENGTH_COLLISION, yposition, WAYPOINT_WIDTH_COLLISION));
				PxTransform *pos = new PxTransform(j, yposition, i);
				Waypoint* tempWaypoint = dynamic_cast<Waypoint*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_WAYPOINT, pos, geom, NULL));
				tempWaypoint->setId(index);
				delete pos;
				delete geom[0];
				delete[] geom;
				tempWaypoint->setId(index);
				m_waypointMap[index].push_back(tempWaypoint);
				m_waypoints.push_back(tempWaypoint);
			}
			index++;
		}
		break;
	case BOTTOM:
		numberOfRows = (abs(trackLengthMax - trackLengthMin) / (WAYPOINT_TRUE_LENGTH * 2));
		numberOfRows--;
		for (int i = trackLengthMin + WAYPOINT_TRUE_LENGTH; i < trackLengthMax; i += ((WAYPOINT_TRUE_LENGTH)* 2))
		{
			std::vector<Waypoint*> newVectorWaypoint;
			m_waypointMap.push_back(newVectorWaypoint);
			for (int j = trackWidthMin + WAYPOINT_TRUE_WIDTH; j < trackWidthMax; j += ((WAYPOINT_TRUE_WIDTH)* 2))
			{
				PxGeometry **geom = new PxGeometry *[1];
				geom[0] = new PxBoxGeometry(PxVec3(WAYPOINT_LENGTH_COLLISION, yposition, WAYPOINT_WIDTH_COLLISION));
				PxTransform *pos = new PxTransform(j, yposition, i);
				Waypoint* tempWaypoint = dynamic_cast<Waypoint*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_WAYPOINT, pos, geom, NULL));
				tempWaypoint->setId(index);
				delete pos;
				delete geom[0];
				delete[] geom;
				tempWaypoint->setId(numberOfRows);
				m_waypointMap[index].push_back(tempWaypoint);
				m_waypoints.push_back(tempWaypoint);
			}
			index++;
			numberOfRows--;
		}
		break;
	case LEFT:
		for (int i = trackLengthMin + WAYPOINT_TRUE_LENGTH; i < trackLengthMax; i += ((WAYPOINT_TRUE_LENGTH)* 2))
	{
		std::vector<Waypoint*> newVectorWaypoint;
		m_waypointMap.push_back(newVectorWaypoint);
			int columnIndex = 0;
			for (int j = trackWidthMin + WAYPOINT_TRUE_WIDTH; j < trackWidthMax; j += ((WAYPOINT_TRUE_WIDTH)* 2))
		{
				PxGeometry **geom = new PxGeometry *[1];
				geom[0] = new PxBoxGeometry(PxVec3(WAYPOINT_LENGTH_COLLISION, yposition, WAYPOINT_WIDTH_COLLISION));
				PxTransform *pos = new PxTransform(j, yposition, i);
			Waypoint* tempWaypoint = dynamic_cast<Waypoint*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_WAYPOINT, pos, geom, NULL));
				tempWaypoint->setId(index);
			delete pos;
			delete geom[0];
			delete[] geom;
				tempWaypoint->setId(columnIndex);
				m_waypointMap[index].push_back(tempWaypoint);
				m_waypoints.push_back(tempWaypoint);
				columnIndex++;
			}
			index++;
		}
		break;
	case RIGHT:
		int numberOfColumns = (abs(trackWidthMax - trackWidthMin) / (WAYPOINT_TRUE_WIDTH * 2));
		for (int i = trackLengthMin + WAYPOINT_TRUE_LENGTH; i < trackLengthMax; i += ((WAYPOINT_TRUE_LENGTH)* 2))
		{
			std::vector<Waypoint*> newVectorWaypoint;
			m_waypointMap.push_back(newVectorWaypoint);
			int columnIndex = numberOfColumns - 1;
			for (int j = trackWidthMin + WAYPOINT_TRUE_WIDTH; j < trackWidthMax; j += ((WAYPOINT_TRUE_WIDTH)* 2))
			{
				PxGeometry **geom = new PxGeometry *[1];
				geom[0] = new PxBoxGeometry(PxVec3(WAYPOINT_LENGTH_COLLISION, yposition, WAYPOINT_WIDTH_COLLISION));
				PxTransform *pos = new PxTransform(j, yposition, i);
				Waypoint* tempWaypoint = dynamic_cast<Waypoint*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_WAYPOINT, pos, geom, NULL));
			tempWaypoint->setId(index);
				delete pos;
				delete geom[0];
				delete[] geom;
				tempWaypoint->setId(columnIndex);
			m_waypointMap[index].push_back(tempWaypoint);
			m_waypoints.push_back(tempWaypoint);
				columnIndex--;
		}
		index++;
	}
		break;
	}
	
	createWaypointConnections();
	//std::cout << "number of waypoints" << m_waypoints.size() << "\n";
	//std::cout << "Rows" << m_waypointMap.size() << "\n";
	//std::cout << "Columns: " << m_waypointMap[0].size() << "\n";
	//std::cout << "width: " << trackWidthMax << " | " << "tack length: " << trackLengthMax << "\n";
	// Populate Waypoints

	
	//for (int i = 30; i < 80; i++)
	//{
	//	if (i % 10 > 2 && i % 10 < 8)
	//	{
	//		//std::cout << "Setting invalid index: " << i << "\n";
	//		m_waypoints[i]->setValid(false);
	//	}
	//}
	//m_waypoints[77]->setValid(false);
	//m_waypoints[83]->setValid(false);
	//m_waypoints[26]->setValid(false);


	//for (int i = 0; i < m_waypoints.size(); i++)
	//{
	//	std::cout << "waypoint: " << m_waypoints[i]->getIndex() << " " << " and is connected to ";
	//	for (int k = 0; k < m_waypoints[i]->getListOfAdjacentWaypoints().size(); k++)
	//	{
	//		std::cout << m_waypoints[i]->getListOfAdjacentWaypoints().at(k)->getIndex() << ", ";
	//	}
	//	std::cout << "\n";
	//}

	//test();

}

void WaypointSystem::createWaypointConnections()
{
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

}

void WaypointSystem::addIdToAllWaypointsInTheSystem(int id)
{
	std::cout << "applying a change of: " << id << " \n";
	for (int i = 0; i < m_waypointMap.size(); i++)
	{
		for (int j = 0; j < m_waypointMap.at(i).size(); j++)
		{
			m_waypointMap[i][j]->setId(m_waypointMap[i][j]->getId() + id);
		}
	}
}

WaypointSystem::~WaypointSystem()
{
	for (unsigned int i = 0; i < m_waypoints.size(); i++)
	{
		//delete m_waypoints[i];
	}
	m_waypoints.clear();
}

void WaypointSystem::test()
{
	PathFinding* pathFinding = new PathFinding();

	std::vector<Waypoint*> result = pathFinding->findPath(m_waypoints[0], m_waypoints[46]);

	//std::cout << "The optimal path is: ";

	for (int i = 0; i < result.size(); i++)
	{
		//std::cout << result[i]->getIndex() << ", ";
	}

	//std::cout << "\n";

	delete pathFinding;
}