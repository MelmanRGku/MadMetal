#include "Track.h"
#include "Waypoint.h"
#include "Game Logic\WayPointSystem.h"

Track::Track(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable *rable, TestObject *drivablePart, TestObject *nonDrivablePart) : TestObject(id, aable, pable, anable, rable), drivablePart(drivablePart), nonDrivablePart(nonDrivablePart)
{
	WaypointSystem * startLocation = new WaypointSystem(
		getDrivablePart()->getWorldBounds().minimum.x,
		getDrivablePart()->getWorldBounds().minimum.x + 120,
		getDrivablePart()->getWorldBounds().minimum.z,
		getDrivablePart()->getWorldBounds().maximum.z - 120,
		getDrivablePart()->getWorldBounds().maximum.y);

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
		getDrivablePart()->getWorldBounds().maximum.y);

	//m_waypointList.resize(m_waypointList.size() + (nextLocation1->getWaypointMap().at(0).size() * nextLocation1->getWaypointMap().size()));
	for (int i = 0; i < nextLocation1->getWaypointMap().size(); i++)
	{
		m_waypointList.insert(m_waypointList.end(), nextLocation1->getWaypointMap().at(i).begin(), nextLocation1->getWaypointMap().at(i).end());
	}
	WaypointSystem* lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
	stitchWaypointSystem(RIGHT, LEFT, *lastWaypointSystem, *nextLocation1, 0, 0);

	m_waypointSystems.push_back(nextLocation1);

	WaypointSystem * nextLocation2 = new WaypointSystem(
		getDrivablePart()->getWorldBounds().maximum.x - 80,
		getDrivablePart()->getWorldBounds().maximum.x,
		getDrivablePart()->getWorldBounds().minimum.z + 120,
		getDrivablePart()->getWorldBounds().maximum.z,
		getDrivablePart()->getWorldBounds().maximum.y);

	//m_waypointList.resize(m_waypointList.size() + (nextLocation1->getWaypointMap().at(0).size() * nextLocation1->getWaypointMap().size()));
	for (int i = 0; i < nextLocation2->getWaypointMap().size(); i++)
	{
		m_waypointList.insert(m_waypointList.end(), nextLocation2->getWaypointMap().at(i).begin(), nextLocation2->getWaypointMap().at(i).end());
	}

	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
	stitchWaypointSystem(BOTTOM, TOP, *lastWaypointSystem, *nextLocation2, 0, nextLocation2->getWaypointMap().at(0).size() - 3);

	m_waypointSystems.push_back(nextLocation2);


	WaypointSystem * nextLocation3 = new WaypointSystem(
		getDrivablePart()->getWorldBounds().minimum.x + 120,
		getDrivablePart()->getWorldBounds().maximum.x,
		getDrivablePart()->getWorldBounds().minimum.z,
		getDrivablePart()->getWorldBounds().minimum.z + 120,
		getDrivablePart()->getWorldBounds().maximum.y);

	//m_waypointList.resize(m_waypointList.size() + (nextLocation1->getWaypointMap().at(0).size() * nextLocation1->getWaypointMap().size()));
	for (int i = 0; i < nextLocation3->getWaypointMap().size(); i++)
	{
		m_waypointList.insert(m_waypointList.end(), nextLocation3->getWaypointMap().at(i).begin(), nextLocation3->getWaypointMap().at(i).end());
	}

	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
	stitchWaypointSystem(LEFT, RIGHT, *lastWaypointSystem, *nextLocation3, 0, nextLocation3->getWaypointMap().size() - 2);
	stitchWaypointSystem(BOTTOM, TOP, *m_waypointSystems.at(0), *nextLocation3, 0, 0);

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

void Track::stitchWaypointSystem(Boundry lastWaypointSystemLocation, Boundry newWaypointSystemPosition, WaypointSystem& lastWaypointSystem, WaypointSystem& newWaypointSystem, int lastWaypointSystemIntialPosition, int newWaypointSystemIntialPosition)
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
			for (int i = lastWaypointColumnIndex, j = newWaypointColumnIndex;
				i < lastWaypointSystem.getWaypointMap().at(0).size() &&
				j < newWaypointSystem.getWaypointMap().at(0).size();
				i++, j++)
			{
				if ((j - 1) >= 0)
				{
					lastWaypointSystem.getWaypointMap().at(lastWaypointRowIndex).at(i)->getListOfAdjacentWaypoints().push_back(
						newWaypointSystem.getWaypointMap().at(newWaypointRowIndex).at(j - 1));
				}

				lastWaypointSystem.getWaypointMap().at(lastWaypointRowIndex).at(i)->getListOfAdjacentWaypoints().push_back(
					newWaypointSystem.getWaypointMap().at(newWaypointRowIndex).at(j));

				if ((j + 1) < newWaypointSystem.getWaypointMap().at(0).size())
				{
					lastWaypointSystem.getWaypointMap().at(lastWaypointRowIndex).at(i)->getListOfAdjacentWaypoints().push_back(
						newWaypointSystem.getWaypointMap().at(newWaypointRowIndex).at(j + 1));
				}

				if ((i - 1) >= 0)
				{
					newWaypointSystem.getWaypointMap().at(newWaypointRowIndex).at(j)->getListOfAdjacentWaypoints().push_back(
						lastWaypointSystem.getWaypointMap().at(lastWaypointRowIndex).at(i - 1));
				}

				newWaypointSystem.getWaypointMap().at(newWaypointRowIndex).at(j)->getListOfAdjacentWaypoints().push_back(
					lastWaypointSystem.getWaypointMap().at(lastWaypointRowIndex).at(i));

				if ((i + 1) < lastWaypointSystem.getWaypointMap().at(0).size())
				{
					newWaypointSystem.getWaypointMap().at(newWaypointRowIndex).at(j)->getListOfAdjacentWaypoints().push_back(
						lastWaypointSystem.getWaypointMap().at(lastWaypointRowIndex).at(i + 1));
				}
			}
		}
		else
		{
			for (int i = lastWaypointColumnIndex, j = newWaypointRowIndex;
				i < lastWaypointSystem.getWaypointMap().at(0).size() &&
				j < newWaypointSystem.getWaypointMap().size();
				i++, j++)
			{
				if ((j - 1) >= 0)
				{
					lastWaypointSystem.getWaypointMap().at(lastWaypointRowIndex).at(i)->getListOfAdjacentWaypoints().push_back(
						newWaypointSystem.getWaypointMap().at(j - 1).at(newWaypointColumnIndex));
				}

				lastWaypointSystem.getWaypointMap().at(lastWaypointRowIndex).at(i)->getListOfAdjacentWaypoints().push_back(
					newWaypointSystem.getWaypointMap().at(j).at(newWaypointColumnIndex));

				if ((j + 1) < newWaypointSystem.getWaypointMap().size())
				{
					lastWaypointSystem.getWaypointMap().at(lastWaypointRowIndex).at(i)->getListOfAdjacentWaypoints().push_back(
						newWaypointSystem.getWaypointMap().at(j+1).at(newWaypointColumnIndex));
				}

				if ((i - 1) >= 0)
				{
					newWaypointSystem.getWaypointMap().at(j).at(newWaypointColumnIndex)->getListOfAdjacentWaypoints().push_back(
						lastWaypointSystem.getWaypointMap().at(lastWaypointRowIndex).at(i - 1));
				}

				newWaypointSystem.getWaypointMap().at(j).at(newWaypointColumnIndex)->getListOfAdjacentWaypoints().push_back(
					lastWaypointSystem.getWaypointMap().at(lastWaypointRowIndex).at(i));

				if ((i + 1) < lastWaypointSystem.getWaypointMap().at(0).size())
				{
					newWaypointSystem.getWaypointMap().at(j).at(newWaypointColumnIndex)->getListOfAdjacentWaypoints().push_back(
						lastWaypointSystem.getWaypointMap().at(lastWaypointRowIndex).at(i + 1));
				}
			}
		}
	}
	else
	{
		if (isStichingRowForNewWaypoint)
		{
			for (int i = lastWaypointRowIndex, j = newWaypointColumnIndex;
				i < lastWaypointSystem.getWaypointMap().size() &&
				j < newWaypointSystem.getWaypointMap().at(0).size();
			i++, j++)
			{
				if ((j - 1) >= 0)
				{
					lastWaypointSystem.getWaypointMap().at(i).at(lastWaypointColumnIndex)->getListOfAdjacentWaypoints().push_back(
						newWaypointSystem.getWaypointMap().at(newWaypointRowIndex).at(j - 1));
				}

				lastWaypointSystem.getWaypointMap().at(i).at(lastWaypointColumnIndex)->getListOfAdjacentWaypoints().push_back(
					newWaypointSystem.getWaypointMap().at(newWaypointRowIndex).at(j));

				if ((j + 1) < newWaypointSystem.getWaypointMap().at(0).size())
				{
					lastWaypointSystem.getWaypointMap().at(i).at(lastWaypointColumnIndex)->getListOfAdjacentWaypoints().push_back(
						newWaypointSystem.getWaypointMap().at(newWaypointRowIndex).at(j + 1));
				}

				if ((i - 1) >= 0)
				{
					newWaypointSystem.getWaypointMap().at(newWaypointRowIndex).at(j)->getListOfAdjacentWaypoints().push_back(
						lastWaypointSystem.getWaypointMap().at(i-1).at(lastWaypointColumnIndex));
				}

				newWaypointSystem.getWaypointMap().at(newWaypointRowIndex).at(j)->getListOfAdjacentWaypoints().push_back(
					lastWaypointSystem.getWaypointMap().at(i).at(lastWaypointColumnIndex));

				if ((i + 1) < lastWaypointSystem.getWaypointMap().size())
				{
					newWaypointSystem.getWaypointMap().at(newWaypointRowIndex).at(j)->getListOfAdjacentWaypoints().push_back(
						lastWaypointSystem.getWaypointMap().at(i + 1).at(lastWaypointColumnIndex));
				}
			}
		}
		else
		{
			for (int i = lastWaypointRowIndex, j = newWaypointRowIndex;
				i < lastWaypointSystem.getWaypointMap().size() &&
				j < newWaypointSystem.getWaypointMap().size();
				i++, j++)
			{
				if ((j - 1) >= 0)
				{
					lastWaypointSystem.getWaypointMap().at(i).at(lastWaypointColumnIndex)->getListOfAdjacentWaypoints().push_back(
						newWaypointSystem.getWaypointMap().at(j-1).at(newWaypointColumnIndex));
				}

				lastWaypointSystem.getWaypointMap().at(i).at(lastWaypointColumnIndex)->getListOfAdjacentWaypoints().push_back(
					newWaypointSystem.getWaypointMap().at(j).at(newWaypointColumnIndex));

				if ((j + 1) < newWaypointSystem.getWaypointMap().size())
				{
					lastWaypointSystem.getWaypointMap().at(i).at(lastWaypointColumnIndex)->getListOfAdjacentWaypoints().push_back(
						newWaypointSystem.getWaypointMap().at(j+1).at(newWaypointColumnIndex));
				}

				if ((i - 1) >= 0)
				{
					newWaypointSystem.getWaypointMap().at(j).at(newWaypointColumnIndex)->getListOfAdjacentWaypoints().push_back(
						lastWaypointSystem.getWaypointMap().at(i-1).at(lastWaypointColumnIndex));
				}

				newWaypointSystem.getWaypointMap().at(j).at(newWaypointColumnIndex)->getListOfAdjacentWaypoints().push_back(
					lastWaypointSystem.getWaypointMap().at(i).at(lastWaypointColumnIndex));

				if ((i + 1) < lastWaypointSystem.getWaypointMap().size())
				{
					newWaypointSystem.getWaypointMap().at(j).at(newWaypointColumnIndex)->getListOfAdjacentWaypoints().push_back(
						lastWaypointSystem.getWaypointMap().at(i+1).at(lastWaypointColumnIndex));
				}
			}
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
