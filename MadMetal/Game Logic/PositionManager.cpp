#include "Game Logic\PositionManager.h"
#include "Game Logic\Controllable.h"
#include "Objects\CollisionVolume.h"
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
			if (m_players.at(i)->getCar()->getCurrentCollisionVolume() == NULL || m_players.at(j)->getCar()->getCurrentCollisionVolume() == NULL)
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
				if (m_players.at(i)->getCar()->getCurrentCollisionVolume()->getId() > m_players.at(j)->getCar()->getCurrentCollisionVolume()->getId())
				{
					if (m_players.at(i)->getCar()->getPositionInRace() > m_players.at(j)->getCar()->getPositionInRace())
					{
						swap(*m_players.at(i), *m_players.at(j));
					}
				}
				else if (m_players.at(i)->getCar()->getCurrentCollisionVolume()->getId() < m_players.at(j)->getCar()->getCurrentCollisionVolume()->getId())
				{
					if (m_players.at(i)->getCar()->getPositionInRace() < m_players.at(j)->getCar()->getPositionInRace())
					{
						swap(*m_players.at(i), *m_players.at(j));
					}
				}
				else if (m_players.at(i)->getCar()->getCurrentCollisionVolume()->getId() == m_players.at(j)->getCar()->getCurrentCollisionVolume()->getId())
				{
					if (m_players.at(i)->getCar()->getLastMainPathCollisionVolume() == NULL || m_players.at(j)->getCar()->getLastMainPathCollisionVolume() == NULL)
					{
						continue;
					}
					glm::vec3 player1Position = m_players.at(i)->getCar()->getGlobalPose();
					player1Position.y = 0;

					glm::vec3 player2Position = m_players.at(j)->getCar()->getGlobalPose();
					player2Position.y = 0;

					glm::vec3 player1Goal = m_players.at(i)->getCar()->getLastMainPathCollisionVolume()->getGlobalPose();
					player1Goal.y = 0;

					glm::vec3 player2Goal = m_players.at(j)->getCar()->getLastMainPathCollisionVolume()->getGlobalPose();
					player2Goal.y = 0;

					float distanceToGoalPlayer1 = glm::distance2(player1Position, player1Goal);
					float distanceToGoalPlayer2 = glm::distance2(player2Position, player2Goal);

					if (distanceToGoalPlayer1 < distanceToGoalPlayer2 && m_players.at(j)->getCar()->getPositionInRace() > m_players.at(i)->getCar()->getPositionInRace())
					{
						swap(*m_players.at(i), *m_players.at(j));
					}
					else if (distanceToGoalPlayer1 > distanceToGoalPlayer2 && m_players.at(j)->getCar()->getPositionInRace() < m_players.at(i)->getCar()->getPositionInRace())
					{
						swap(*m_players.at(i), *m_players.at(j));
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

