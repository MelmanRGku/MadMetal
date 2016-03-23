#include "Game Logic\PositionManager.h"
#include "Game Logic\Controllable.h"
PositionManager::PositionManager() : m_players(std::vector<Controllable*>())
{

}

PositionManager::PositionManager(std::vector<Controllable*>& players) : m_players(players)
{

}

PositionManager::~PositionManager()
{
}

void PositionManager::updatePlayerPositions()
{
	for (int i = 0; i < m_players.size(); i++)
	{
		for (int j = i + 1; j < m_players.size(); j++)
		{
			if (m_players.at(i)->getCar()->getCurrentWaypoint() == NULL || m_players.at(j)->getCar()->getCurrentWaypoint() == NULL)
				continue;
			if (m_players.at(i)->getCar()->getLap() < m_players.at(j)->getCar()->getLap())
			{
				if (m_players.at(i)->getCar()->getPositionInRace() < m_players.at(j)->getCar()->getPositionInRace())
				{
					swap(*m_players.at(i), *m_players.at(j));
				}
			}
			else if (m_players.at(i)->getCar()->getLap() > m_players.at(j)->getCar()->getLap())
			{
				if (m_players.at(i)->getCar()->getPositionInRace() > m_players.at(j)->getCar()->getPositionInRace())
				{
					swap(*m_players.at(i), *m_players.at(j));
				}
			}
			else
			{
				if (m_players.at(i)->getCar()->getCurrentWaypoint()->getId() > m_players.at(j)->getCar()->getCurrentWaypoint()->getId())
				{
					if (m_players.at(i)->getCar()->getPositionInRace() > m_players.at(j)->getCar()->getPositionInRace())
					{
						swap(*m_players.at(i), *m_players.at(j));
					}
				}
				else if (m_players.at(i)->getCar()->getCurrentWaypoint()->getId() < m_players.at(j)->getCar()->getCurrentWaypoint()->getId())
				{
					if (m_players.at(i)->getCar()->getPositionInRace() < m_players.at(j)->getCar()->getPositionInRace())
					{
						swap(*m_players.at(i), *m_players.at(j));
					}
				}
				else if (m_players.at(i)->getCar()->getCurrentWaypoint()->getId() == m_players.at(j)->getCar()->getCurrentWaypoint()->getId())
				{
					if (i == 0)
					{
						//std::cout << "in same waypoint\n";
					}
				}
			}
		}
	}
}

void PositionManager::swap(Controllable& player1, Controllable& player2)
{
	int temp = player1.getCar()->getPositionInRace();
	player1.getCar()->setPositionInRace(player2.getCar()->getPositionInRace());
	player2.getCar()->setPositionInRace(temp);
}

