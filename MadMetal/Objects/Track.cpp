#include "Track.h"
#include "Waypoint.h"
#include "Game Logic\WayPointSystem.h"
#include "Game Logic\WaypointDefinitions.h"

Track::Track(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Object3D *drivablePart, Object3D *nonDrivablePart) : Object3D(id, aable, pable, anable, rable), drivablePart(drivablePart), nonDrivablePart(nonDrivablePart)
{
	WaypointSystem * startLocation = new WaypointSystem(
		getDrivablePart()->getWorldBounds().minimum.x,
		getDrivablePart()->getWorldBounds().minimum.x + 120,
		getDrivablePart()->getWorldBounds().minimum.z,
		getDrivablePart()->getWorldBounds().maximum.z - 120,
		getDrivablePart()->getWorldBounds().maximum.y,
		LEFT);

	//m_waypointList.resize(m_waypointList.size() + (startLocation->getWaypointMap().at(0).size() * startLocation->getWaypointMap().size()));
	for (int i = 0; i < startLocation->getWaypointMap().size(); i++)
	{
		m_waypointList.insert(m_waypointList.end(), startLocation->getWaypointMap().at(i).begin(), startLocation->getWaypointMap().at(i).end());
}

	m_waypointSystems.push_back(startLocation);

	WaypointSystem * nextLocation1 = new WaypointSystem(
		getDrivablePart()->getWorldBounds().minimum.x,
		getDrivablePart()->getWorldBounds().maximum.x - 80,
		getDrivablePart()->getWorldBounds().maximum.z - 120,
		getDrivablePart()->getWorldBounds().maximum.z,
		getDrivablePart()->getWorldBounds().maximum.y,
		TOP);

	//m_waypointList.resize(m_waypointList.size() + (nextLocation1->getWaypointMap().at(0).size() * nextLocation1->getWaypointMap().size()));
	for (int i = 0; i < nextLocation1->getWaypointMap().size(); i++)
	{
		m_waypointList.insert(m_waypointList.end(), nextLocation1->getWaypointMap().at(i).begin(), nextLocation1->getWaypointMap().at(i).end());
	}
	WaypointSystem* lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
	stitchWaypointSystems(RIGHT, LEFT, *lastWaypointSystem, *nextLocation1, 0, 0);

	m_waypointSystems.push_back(nextLocation1);

	WaypointSystem * nextLocation2 = new WaypointSystem(
		getDrivablePart()->getWorldBounds().maximum.x - 80,
		getDrivablePart()->getWorldBounds().maximum.x,
		getDrivablePart()->getWorldBounds().minimum.z + 120,
		getDrivablePart()->getWorldBounds().maximum.z,
		getDrivablePart()->getWorldBounds().maximum.y,
		RIGHT);

	//m_waypointList.resize(m_waypointList.size() + (nextLocation1->getWaypointMap().at(0).size() * nextLocation1->getWaypointMap().size()));
	for (int i = 0; i < nextLocation2->getWaypointMap().size(); i++)
	{
		m_waypointList.insert(m_waypointList.end(), nextLocation2->getWaypointMap().at(i).begin(), nextLocation2->getWaypointMap().at(i).end());
	}

	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
	stitchWaypointSystems(BOTTOM, TOP, *lastWaypointSystem, *nextLocation2, 0, nextLocation2->getWaypointMap().at(0).size() - 3);

	m_waypointSystems.push_back(nextLocation2);


	WaypointSystem * nextLocation3 = new WaypointSystem(
		getDrivablePart()->getWorldBounds().minimum.x + 120,
		getDrivablePart()->getWorldBounds().maximum.x,
		getDrivablePart()->getWorldBounds().minimum.z,
		getDrivablePart()->getWorldBounds().minimum.z + 120,
		getDrivablePart()->getWorldBounds().maximum.y,
		BOTTOM);

	//m_waypointList.resize(m_waypointList.size() + (nextLocation1->getWaypointMap().at(0).size() * nextLocation1->getWaypointMap().size()));
	for (int i = 0; i < nextLocation3->getWaypointMap().size(); i++)
	{
		m_waypointList.insert(m_waypointList.end(), nextLocation3->getWaypointMap().at(i).begin(), nextLocation3->getWaypointMap().at(i).end());
	}

	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
	stitchWaypointSystems(LEFT, RIGHT, *lastWaypointSystem, *nextLocation3, 0, nextLocation3->getWaypointMap().size() - 2);
	stitchWaypointSystems(BOTTOM, TOP, *m_waypointSystems.at(0), *nextLocation3, 0, 0);

	m_waypointSystems.push_back(nextLocation3);

}

Track::~Track()
{
	for (std::vector<Waypoint*>::iterator it = m_waypointList.begin(); it != m_waypointList.end(); ++it)
	{
		delete *it;
	}
	
	for (std::vector<WaypointSystem*>::iterator it = m_waypointSystems.begin(); it != m_waypointSystems.end(); ++it)
	{
		delete *it;
}
}

bool Track::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	
	//do nothing
	return false;

}

void Track::playTrackMusic()
{
	//m_audioable->getAudioHandle().playMusic(m_sound);
}

Waypoint * Track::getWaypointAt(int index)
{
	if (index < m_waypointList.size())
	{
		return m_waypointList[index];
	}
	else
	{
		std::cerr << "ERROR: trying to acquire out of index pointer\n";
		return NULL;
	}
}

void Track::stitchWaypointSystems(Boundry lastWaypointSystemLocation, Boundry newWaypointSystemPosition, WaypointSystem& lastWaypointSystem, WaypointSystem& newWaypointSystem, int lastWaypointSystemIntialPosition, int newWaypointSystemIntialPosition)
{
	bool isStichingRowForLastWaypoint;
	int lastWaypointRowIndex;
	int lastWaypointColumnIndex;

	determineStitchingBoundaries(lastWaypointSystemLocation, lastWaypointSystemIntialPosition, isStichingRowForLastWaypoint, lastWaypointRowIndex, lastWaypointColumnIndex, lastWaypointSystem);

	bool isStichingRowForNewWaypoint;
	int newWaypointRowIndex;
	int newWaypointColumnIndex;

	determineStitchingBoundaries(newWaypointSystemPosition, newWaypointSystemIntialPosition, isStichingRowForNewWaypoint, newWaypointRowIndex, newWaypointColumnIndex, newWaypointSystem);

	if (isStichingRowForLastWaypoint)
	{
		if (isStichingRowForNewWaypoint)
		{
			stitch(lastWaypointSystem, isStichingRowForLastWaypoint, lastWaypointColumnIndex, lastWaypointRowIndex, newWaypointSystem, isStichingRowForNewWaypoint, newWaypointColumnIndex, newWaypointRowIndex);
		}
		else
		{
			stitch(lastWaypointSystem, isStichingRowForLastWaypoint, lastWaypointColumnIndex, lastWaypointRowIndex, newWaypointSystem, isStichingRowForNewWaypoint, newWaypointRowIndex, newWaypointRowIndex);
		}
	}
	else
	{
		if (isStichingRowForNewWaypoint)
		{
			stitch(lastWaypointSystem, isStichingRowForLastWaypoint, lastWaypointRowIndex, lastWaypointColumnIndex, newWaypointSystem, isStichingRowForNewWaypoint, newWaypointColumnIndex, newWaypointRowIndex);
		}
		else
		{
			stitch(lastWaypointSystem, isStichingRowForLastWaypoint, lastWaypointRowIndex, lastWaypointColumnIndex, newWaypointSystem, isStichingRowForNewWaypoint, newWaypointRowIndex, newWaypointColumnIndex);
		}
	}


	for (int i = 0; i < m_waypointList.size(); i++)
	{
		std::cout << "waypoint: " << m_waypointList[i]->getIndex() << " " << " and is connected to ";
		for (int k = 0; k < m_waypointList[i]->getListOfAdjacentWaypoints().size(); k++)
		{
			std::cout << m_waypointList[i]->getListOfAdjacentWaypoints().at(k)->getIndex() << ", ";
		}
		std::cout << "\n";
	}

}

void Track::determineStitchingBoundaries(Boundry locationOfStiching, int initialPosition,  bool& isStichingRow, int& RowIndex, int& ColumnIndex, WaypointSystem& system)
{
	switch (locationOfStiching)
	{
	case TOP:
		isStichingRow = true;
		RowIndex = 0;
		ColumnIndex = initialPosition;
		break;
	case BOTTOM:
		isStichingRow = true;
		RowIndex = system.getWaypointMap().size() - 1;
		ColumnIndex = initialPosition;
		break;
	case LEFT:
		isStichingRow = false;
		RowIndex = initialPosition;
		ColumnIndex = 0;
		break;
	case RIGHT:
		isStichingRow = false;
		RowIndex = initialPosition;
		ColumnIndex = system.getWaypointMap().at(0).size() - 1;
		break;
	}
}

void Track::stitch(WaypointSystem& waypointSystem1, bool isRowStiching1, int limitOfStichingIteration1, int indexOfEdge1, WaypointSystem& waypointSystem2, bool isRowStiching2, int limitOfStichingIteration2, int indexOfEdge2)
{
	int waypointSystem1EdgeLimit;
	int waypointSystem2EdgeLimit;

	isRowStiching1 ? waypointSystem1EdgeLimit = waypointSystem1.getWaypointMap().at(0).size() : waypointSystem1EdgeLimit = waypointSystem1.getWaypointMap().size();
	isRowStiching2 ? waypointSystem2EdgeLimit = waypointSystem2.getWaypointMap().at(0).size() : waypointSystem2EdgeLimit = waypointSystem2.getWaypointMap().size();

	for (int i = limitOfStichingIteration1, j = limitOfStichingIteration2;
		i < waypointSystem1EdgeLimit &&
		j < waypointSystem2EdgeLimit;
	i++, j++)
	{
		if ((j - 1) >= 0)
		{
			determinePlaceInAdjecencyListAndPush(waypointSystem1, isRowStiching1, indexOfEdge1, i, waypointSystem2, isRowStiching2, indexOfEdge2, j - 1);
		}

		determinePlaceInAdjecencyListAndPush(waypointSystem1, isRowStiching1, indexOfEdge1, i, waypointSystem2, isRowStiching2, indexOfEdge2, j);

		if ((j + 1) < waypointSystem2EdgeLimit)
		{
			determinePlaceInAdjecencyListAndPush(waypointSystem1, isRowStiching1, indexOfEdge1, i, waypointSystem2, isRowStiching2, indexOfEdge2, j + 1);
		}

		if ((i - 1) >= 0)
		{
			determinePlaceInAdjecencyListAndPush(waypointSystem2, isRowStiching2, indexOfEdge2, j, waypointSystem1, isRowStiching1, indexOfEdge1, i - 1);
		}

		determinePlaceInAdjecencyListAndPush(waypointSystem2, isRowStiching2, indexOfEdge2, j, waypointSystem1, isRowStiching1, indexOfEdge1, i);

		if ((i + 1) < waypointSystem1EdgeLimit)
		{
			determinePlaceInAdjecencyListAndPush(waypointSystem2, isRowStiching2, indexOfEdge2, j, waypointSystem1, isRowStiching1, indexOfEdge1, i + 1);
		}
	}
}

void Track::determinePlaceInAdjecencyListAndPush(WaypointSystem& waypointSystem1, bool isRowStiching1, int indexOfEdge1, int indexOfIncrement1, WaypointSystem& waypointSystem2, bool isRowStiching2, int indexOfEdge2, int indexOfIncrement2)
{
	if (isRowStiching1 && isRowStiching2)
	{
		waypointSystem1.getWaypointMap().at(indexOfEdge1).at(indexOfIncrement1)->getListOfAdjacentWaypoints().push_back(
			waypointSystem2.getWaypointMap().at(indexOfEdge2).at(indexOfIncrement2));
	}
	else if (isRowStiching1 && !isRowStiching2)
	{
		waypointSystem1.getWaypointMap().at(indexOfEdge1).at(indexOfIncrement1)->getListOfAdjacentWaypoints().push_back(
			waypointSystem2.getWaypointMap().at(indexOfIncrement2).at(indexOfEdge2)); 
	}
	else if (isRowStiching2 && !isRowStiching1)
	{
		waypointSystem1.getWaypointMap().at(indexOfIncrement1).at(indexOfEdge1)->getListOfAdjacentWaypoints().push_back(
			waypointSystem2.getWaypointMap().at(indexOfEdge2).at(indexOfIncrement2));
	}
	else
	{
		waypointSystem1.getWaypointMap().at(indexOfIncrement1).at(indexOfEdge1)->getListOfAdjacentWaypoints().push_back(
			waypointSystem2.getWaypointMap().at(indexOfIncrement2).at(indexOfEdge2));
	}
}
