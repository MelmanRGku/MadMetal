#include "Track.h"
#include "Waypoint.h"
#include "Game Logic\WayPointSystem.h"
#include "Game Logic\WaypointDefinitions.h"

Track::Track(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Object3D *drivablePart, Object3D *nonDrivablePart) : Object3D(id, aable, pable, anable, rable, NULL), drivablePart(drivablePart), nonDrivablePart(nonDrivablePart)
{
	WaypointSystem * startLocation = new WaypointSystem(
		getDrivablePart()->getWorldBounds().maximum.x - 180,
		getDrivablePart()->getWorldBounds().maximum.x - 140,
		getDrivablePart()->getWorldBounds().minimum.z + 200,
		getDrivablePart()->getWorldBounds().minimum.z + 360,
		getDrivablePart()->getWorldBounds().maximum.y,
		TOP);

	for (int i = 0; i < startLocation->getWaypointMap().size(); i++)
	{
		m_waypointList.insert(m_waypointList.end(), startLocation->getWaypointMap().at(i).begin(), startLocation->getWaypointMap().at(i).end());
}

	m_waypointSystems.push_back(startLocation);

	WaypointSystem * nextLocation1 = new WaypointSystem(
		getDrivablePart()->getWorldBounds().maximum.x - 280,
		getDrivablePart()->getWorldBounds().maximum.x - 40,
		getDrivablePart()->getWorldBounds().minimum.z + 360,
		getDrivablePart()->getWorldBounds().maximum.z - 520,
		getDrivablePart()->getWorldBounds().maximum.y,
		TOP);

	for (int i = 0; i < nextLocation1->getWaypointMap().size(); i++)
	{
		m_waypointList.insert(m_waypointList.end(), nextLocation1->getWaypointMap().at(i).begin(), nextLocation1->getWaypointMap().at(i).end());
	}
	WaypointSystem* lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
	stitchWaypointSystems(BOTTOM, TOP, *lastWaypointSystem, *nextLocation1, 0, 5, true);

	m_waypointSystems.push_back(nextLocation1);

	setInvalid();

	WaypointSystem * nextLocation2 = new WaypointSystem(
		getDrivablePart()->getWorldBounds().maximum.x - 180,
		getDrivablePart()->getWorldBounds().maximum.x - 140,
		getDrivablePart()->getWorldBounds().maximum.z - 520,
		getDrivablePart()->getWorldBounds().maximum.z - 60,
		getDrivablePart()->getWorldBounds().maximum.y,
		TOP);

	for (int i = 0; i < nextLocation2->getWaypointMap().size(); i++)
	{
		m_waypointList.insert(m_waypointList.end(), nextLocation2->getWaypointMap().at(i).begin(), nextLocation2->getWaypointMap().at(i).end());
	}

	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
	stitchWaypointSystems(BOTTOM, TOP, *lastWaypointSystem, *nextLocation2, 5, 0, true);

	m_waypointSystems.push_back(nextLocation2);

	WaypointSystem * nextLocation3 = new WaypointSystem(
		getDrivablePart()->getWorldBounds().minimum.x + 40,
		getDrivablePart()->getWorldBounds().maximum.x - 200,
		getDrivablePart()->getWorldBounds().maximum.z - 100,
		getDrivablePart()->getWorldBounds().maximum.z - 40,
		getDrivablePart()->getWorldBounds().maximum.y,
		RIGHT);

	for (int i = 0; i < nextLocation3->getWaypointMap().size(); i++)
	{
		m_waypointList.insert(m_waypointList.end(), nextLocation3->getWaypointMap().at(i).begin(), nextLocation3->getWaypointMap().at(i).end());
	}

	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
	stitchWaypointSystems(LEFT, RIGHT, *lastWaypointSystem, *nextLocation3, lastWaypointSystem->getWaypointMap().size() - 2, 0, true);

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
	m_audioable->getAudioHandle().playMusic(m_sound);
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

void Track::stitchWaypointSystems(Boundry lastWaypointSystemLocation, Boundry newWaypointSystemPosition, WaypointSystem& lastWaypointSystem, WaypointSystem& newWaypointSystem, int lastWaypointSystemIntialPosition, int newWaypointSystemIntialPosition, bool recalculateIds)
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
			recalculateWaypointSystemIds(lastWaypointSystem, newWaypointSystem, recalculateIds);
		}
		else
		{
			std::cerr << "Cannot Stitch row to column\n";
		}
	}
	else
	{
		if (isStichingRowForNewWaypoint)
		{
			std::cerr << "Cannot Stitch column to row\n";
		}
		else
		{
			stitch(lastWaypointSystem, isStichingRowForLastWaypoint, lastWaypointRowIndex, lastWaypointColumnIndex, newWaypointSystem, isStichingRowForNewWaypoint, newWaypointRowIndex, newWaypointColumnIndex);

			recalculateWaypointSystemIds(lastWaypointSystem, newWaypointSystem, recalculateIds);
		}
	}


	//for (int i = 0; i < m_waypointList.size(); i++)
	//{
	//	std::cout << "waypoint: " << m_waypointList[i]->getIndex() << " " << " and is connected to ";
	//	for (int k = 0; k < m_waypointList[i]->getListOfAdjacentWaypoints().size(); k++)
	//	{
	//		std::cout << m_waypointList[i]->getListOfAdjacentWaypoints().at(k)->getIndex() << ", ";
	//	}
	//	std::cout << "\n";
	//}

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

void Track::recalculateWaypointSystemIds(WaypointSystem& waypointSystem1, WaypointSystem& waypointSystem2, bool& recalculateIds)
{
	if (recalculateIds)
	{
		int difference1 = abs(waypointSystem1.getWaypointMap().at(waypointSystem1.getWaypointMap().size() - 1).at(waypointSystem1.getWaypointMap().at(0).size() - 1)->getId() -
			waypointSystem2.getWaypointMap().at(0).at(waypointSystem2.getWaypointMap().at(0).size() - 1)->getId());
		int secondValue = waypointSystem1.getWaypointMap().at(waypointSystem1.getWaypointMap().size() - 1).at(waypointSystem1.getWaypointMap().at(0).size() - 1)->getId() == waypointSystem1.getWaypointMap().at(0).at(waypointSystem1.getWaypointMap().at(0).size() - 1)->getId() ?
			waypointSystem1.getWaypointMap().at(0).at(0)->getId() :
			waypointSystem1.getWaypointMap().at(0).at(waypointSystem1.getWaypointMap().at(0).size() - 1)->getId();
		int difference2 = abs(secondValue -
			waypointSystem2.getWaypointMap().at(0).at(waypointSystem2.getWaypointMap().at(0).size() - 1)->getId());

		if (difference1 > difference2)
		{
			waypointSystem2.addIdToAllWaypointsInTheSystem(waypointSystem1.getWaypointMap().at(waypointSystem1.getWaypointMap().size() - 1).at(waypointSystem1.getWaypointMap().at(0).size() - 1)->getId());
		}
		else
		{
			waypointSystem2.addIdToAllWaypointsInTheSystem(secondValue);
		}
	}
}

void Track::setInvalid()
{
	m_waypointList[0]->setValid(false);
	m_waypointList[1]->setValid(false);

	for (int i = 16; i < 555; i++)
	{
		if ((i > 16 && i < 21) ||
			(i > 22 && i < 33) ||
			(i > 34 && i < 45) ||
			(i > 46 && i < 57) ||
			(i > 59 && i < 69) ||
			(i > 71 && i < 81) ||
			(i > 83 && i < 93) ||
			(i > 95 && i < 105) ||
			(i > 107 && i < 118) ||
			(i > 120 && i < 131) ||
			(i > 132 && i < 143) ||
			(i > 144 && i < 155) ||
			(i > 157 && i < 168) || 
			(i > 170 && i < 180) || 
			(i > 182 && i < 193) || 
			(i > 195 && i < 205) ||
			(i > 207 && i < 217) ||
			(i > 219 && i < 229) || 
			(i > 231 && i < 241) || 
			(i > 243 && i < 252) || 
			(i > 255 && i < 264) ||
			(i > 266 && i < 276) ||
			(i > 277 && i < 287) ||
			
			
			(i > 289 && i < 298) ||
			(i > 300 && i < 310) ||
			(i > 311 && i < 321) ||
			(i > 322 && i < 333) ||
			(i > 334 && i < 344) ||
			(i > 345 && i < 355) ||
			(i > 356 && i < 366) ||
			(i > 367 && i < 377) ||
			(i > 379 && i < 390) ||
			(i > 391 && i < 400) ||
			(i > 402 && i < 412) ||
			(i > 414 && i < 424) ||
			(i > 426 && i < 436) ||
			(i > 438 && i < 448) ||
			(i > 451 && i < 461) ||
			(i > 463 && i < 473) ||
			(i > 475 && i < 486) ||
			(i > 488 && i < 498) ||
			(i > 500 && i < 511) ||
			(i > 512 && i < 524) ||
			(i > 525 && i < 536) ||
			(i > 538 && i < 548) ||
			(i > 550 && i < 555))
		{
			m_waypointList[i]->setValid(false);

			//std::cout << "making invalid: " << m_waypointList[i]->getIndex() << "\n";
		}
	}
}