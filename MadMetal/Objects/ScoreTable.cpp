#include "ScoreTable.h"
#include <sstream>

ScoreTable::ScoreTable(std::vector<Controllable *> players) : m_players(players)
{
}


ScoreTable::~ScoreTable()
{
}


void ScoreTable::updateTable(){
	callNumber++;
	if (callNumber > UPDATE_EVERY_N_FRAMES)
		callNumber = 0;
	else
		return;

	m_playerNames.clear();
	for (int i = 0; i < m_players.size(); i++) {
		std::stringstream ss;
		ss << "Player " << (i+1);
		m_playerNames.push_back(ss.str());
	}

	m_playerPositionsInRaceStrings.clear();
	for (int i = 0; i < m_players.size(); i++) {
		int posInRace = m_players.at(i)->getCar()->getPositionInRace();
		std::stringstream ss;
		ss << posInRace;
		if (posInRace == 1)
			ss << "st";
		else if (posInRace == 2)
			ss << "nd";
		else if (posInRace == 3)
			ss << "rd";
		else
			ss << "th";
		m_playerPositionsInRaceStrings.push_back(ss.str());
	}

	m_playerPositionsInRace.clear();
	for (int i = 0; i < m_players.size(); i++) {
		int posInRace = m_players.at(i)->getCar()->getPositionInRace();
		m_playerPositionsInRace.push_back(posInRace);
	}

	m_playerPoints.clear();
	for (int i = 0; i < m_players.size(); i++) {
		m_playerPoints.push_back(m_players.at(i)->getCar()->getScore());
	}

	m_playerPointsStrings.clear();
	for (int i = 0; i < m_players.size(); i++) {
		std::stringstream ss;
		ss << m_players.at(i)->getCar()->getScore();
		m_playerPointsStrings.push_back(ss.str());
	}

	sort();
}

void ScoreTable::sort() {
	for (int i = 0; i < m_playerPositionsInRace.size(); i++) {
		for (int j = 0; j < m_playerPositionsInRace.size() - 1; j++) {
			if (m_playerPositionsInRace.at(j) > m_playerPositionsInRace.at(j + 1)) {
				std::iter_swap(m_playerPositionsInRace.begin() + j, m_playerPositionsInRace.begin() + j + 1);
				std::iter_swap(m_playerNames.begin() + j, m_playerNames.begin() + j + 1);
				std::iter_swap(m_playerPositionsInRaceStrings.begin() + j, m_playerPositionsInRaceStrings.begin() + j + 1);
				std::iter_swap(m_playerPoints.begin() + j, m_playerPoints.begin() + j + 1);
			}
		}
	}
}