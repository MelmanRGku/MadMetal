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
			if (m_players.at(i)->getCar()->getLap() < m_players.at(j)->getCar()->getLap())
			{
				if (m_players.at(i)->getCar()->getPositionInRace() > m_players.at(j)->getCar()->getPositionInRace())
				{
					int temp = m_players.at(j)->getCar()->getPositionInRace();
					m_players.at(i)->getCar()->setPositionInRace(m_players.at(j)->getCar()->getPositionInRace());
					m_players.at(j)->getCar()->setPositionInRace(temp);
				}
			}
			else
			{
				if (m_players.at(i)->getCar()->getCurrentWaypoint()->getId() > m_players.at(j)->getCar()->getCurrentWaypoint()->getId())
				{
					if (m_players.at(i)->getCar()->getPositionInRace() > m_players.at(j)->getCar()->getPositionInRace())
					{
						int temp = m_players.at(j)->getCar()->getPositionInRace();
						m_players.at(i)->getCar()->setPositionInRace(m_players.at(j)->getCar()->getPositionInRace());
						m_players.at(j)->getCar()->setPositionInRace(temp);
					}
				}
				else if (m_players.at(i)->getCar()->getCurrentWaypoint()->getId() == m_players.at(j)->getCar()->getCurrentWaypoint()->getId())
				{
					std::cout << "in same waypoint\n";
				}
			}
		}
	}
}


