#include "PathFinding.h"
#include "Game Logic\SearchWaypoint.h"
#include "Objects\Waypoint.h"

static const float BIG_VALUE = 99999.9;
static const float ADDED_G_VALUE_DIAGONAL = 14.14213;
static const float ADDED_G_VALUE_NORMAL = 10.0;

PathFinding::PathFinding()
{
	m_initializedStartGOal = false;
	m_foundGoal = false;
}

PathFinding::~PathFinding()
{
	for (unsigned int i = 0; i < m_openList.size(); i++) {
		delete m_openList[i];
	}
	std::vector<SearchWaypoint *>().swap(m_openList);

	for (unsigned int i = 0; i < m_visitedList.size(); i++) {
		delete m_visitedList[i];
	}
	std::vector<SearchWaypoint *>().swap(m_visitedList);

	delete m_goalWaypoint;
}

void PathFinding::setWaypointCostOf(std::vector<int> listOfHighWaypoints)
{
	m_indexWithHighCost = listOfHighWaypoints;
}

std::vector<Waypoint*> PathFinding::findPath(Waypoint * currentPosition, Waypoint * targetPosition)
{
	if (!m_initializedStartGOal)
	{
		for (int i = 0; i < m_openList.size(); i++)
		{
			delete m_openList[i];
		}
		m_openList.clear();

		for (int i = 0; i < m_visitedList.size(); i++)
		{
			delete m_visitedList[i];
		}
		m_visitedList.clear();

		for (int i = 0; i < m_pathToGoal.size(); i++)
		{
			m_pathToGoal.clear();
		}

		m_foundGoal = false;
		setStartAndGoal(*currentPosition, *targetPosition);
		m_initializedStartGOal = true;
		
	}

	while (!m_foundGoal)
	{
		continuePath();
	}

	m_initializedStartGOal = false; 
	return m_pathToGoal;
}

void PathFinding::setStartAndGoal(Waypoint& currentPosition, Waypoint& targetPosition)
{
	m_startWaypoint = new SearchWaypoint(currentPosition);
	m_goalWaypoint = new SearchWaypoint(targetPosition, m_goalWaypoint);

	m_startWaypoint->setG(0);
	m_startWaypoint->setH(m_startWaypoint->ManHattanDistance(m_goalWaypoint));
	m_startWaypoint->setParent(NULL);

	m_openList.push_back(m_startWaypoint);
}

SearchWaypoint* PathFinding::getNextCell()
{
	float bestF = BIG_VALUE;
	int cellIndex = -1;
	SearchWaypoint* nextCell = NULL;

	for (int i = 0; i < m_openList.size(); i++)
	{
		if (m_openList[i]->GetF() < bestF)
		{
			bestF = m_openList[i]->GetF();
			cellIndex = i;
		}
	}

	if (cellIndex >= 0)
	{
		nextCell = m_openList[cellIndex];
		m_visitedList.push_back(nextCell);
		m_openList.erase(m_openList.begin() + cellIndex);
	}

	return nextCell;
}

void PathFinding::pathOpened(Waypoint& waypoint, float newCost, SearchWaypoint *parent)
{
	if (!waypoint.isValid())
	{
		return;
	}

	for (int i = 0; i < m_visitedList.size(); i++)
	{
		if (waypoint.getIndex() == m_visitedList[i]->getWaypoint().getIndex())
		{
			return;
		}
	}

	SearchWaypoint* newChild = new SearchWaypoint(waypoint, parent);
	for (int i = 0; i < m_indexWithHighCost.size(); i++)
	{
		if (newChild->getWaypoint().getIndex() == m_indexWithHighCost[i])
		{
			newChild->setHighCost(9999.9);
		}
	}
	newChild->setG(newCost);
	newChild->setH(newChild->ManHattanDistance(m_goalWaypoint));

	for (int i = 0; i < m_openList.size(); i++)
	{
		if (waypoint.getIndex() == m_openList[i]->getWaypoint().getIndex())
		{
			float newG = newChild->getG();

			if (m_openList[i]->getG() > newG)
			{
				m_openList[i]->setG(newChild->getG());
				m_openList[i]->setParent(parent);
				delete newChild;
				return;
			}
			else
			{
				delete newChild;
				return;
			}
		}
	}

	m_openList.push_back(newChild);
}

void PathFinding::continuePath()
{
	if (m_openList.empty())
	{
		return;
	}

	SearchWaypoint* currentWaypoint = getNextCell();

	if (currentWaypoint->getWaypoint().getIndex() == m_goalWaypoint->getWaypoint().getIndex())
	{
		delete m_goalWaypoint->getParent();
		m_goalWaypoint->setParent(currentWaypoint->getParent());

		SearchWaypoint* getPath;

		for (getPath = m_goalWaypoint; getPath != NULL; getPath = getPath->getParent())
		{
			m_pathToGoal.push_back(&(getPath->getWaypoint()));
		}

		m_foundGoal = true;
		return;
	}
	else
	{
		for (int i = 0; i < currentWaypoint->getWaypoint().getListOfAdjacentWaypoints().size(); i++)
		{
			// Not Diagonal 
			if (fabs(currentWaypoint->getWaypoint().getGlobalPose().x - currentWaypoint->getWaypoint().getListOfAdjacentWaypoints().at(i)->getGlobalPose().x) == 0 ||
				fabs(currentWaypoint->getWaypoint().getGlobalPose().z - currentWaypoint->getWaypoint().getListOfAdjacentWaypoints().at(i)->getGlobalPose().z) == 0)
			{
				pathOpened(*(currentWaypoint->getWaypoint().getListOfAdjacentWaypoints().at(i)),
					currentWaypoint->getG() + ADDED_G_VALUE_NORMAL,
					currentWaypoint);
			}
			else
			{
				pathOpened(*(currentWaypoint->getWaypoint().getListOfAdjacentWaypoints().at(i)),
					currentWaypoint->getG() + ADDED_G_VALUE_DIAGONAL,
					currentWaypoint);
			}
		}

		for (int i = 0; i < m_openList.size(); i++)
		{
			if (currentWaypoint->getWaypoint().getIndex() == m_openList[i]->getWaypoint().getIndex())
			{
				delete m_openList[i];
				m_openList.erase(m_openList.begin() + i);
			}
		}
	}
}


