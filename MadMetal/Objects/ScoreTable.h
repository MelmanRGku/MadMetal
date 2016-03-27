#pragma once

#include "Game Logic\Controllable.h"
#define UPDATE_EVERY_N_FRAMES 10

class ScoreTable
{
private:
	std::vector<Controllable *> m_players;
	std::vector<std::string> m_playerNames;
	std::vector<int> m_playerPositionsInRace;
	std::vector<std::string> m_playerPositionsInRaceStrings;
	std::vector<int> m_playerPoints;
	int callNumber = UPDATE_EVERY_N_FRAMES;

	void sort();
public:
	ScoreTable(std::vector<Controllable *> players);
	~ScoreTable();
	void updateTable();
};

