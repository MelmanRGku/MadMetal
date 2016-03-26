#pragma once

#include <vector>
class Controllable;

class PositionManager
{
public:
	PositionManager();
	PositionManager(std::vector<Controllable*>& players);
	~PositionManager();
	void updatePlayerPositions();

private: // members
	std::vector<Controllable*>& m_players;

private: // helper functions 
	void swap(Controllable& player1, Controllable& player2);

};