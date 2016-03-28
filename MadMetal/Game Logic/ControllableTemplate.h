#pragma once
#include "Input\GamePad.h"

class ControllableTemplate
{
public:
	ControllableTemplate(int carSelection) : m_carSelection(carSelection){ std::cout << carSelection << std::endl; };
	ControllableTemplate(int carSelection, GamePad * gamePad) : m_carSelection(carSelection), m_gamePad(gamePad){};
	ControllableTemplate(GamePad * gamePad) : m_gamePad(gamePad), m_carSelection(-1){};
	
	~ControllableTemplate()
	{
		m_gamePad = NULL;
	}

	GamePad* getGamePad() { return m_gamePad; }
	int getCarSelection() { return m_carSelection; }
	void setCarSelection(int selection) { m_carSelection = selection; }
	bool isHumanPlayer() { return m_gamePad == NULL; }
	bool carSelected() { return m_carSelection != -1; }
	void setFinalScore(int finalScore) { this->finalScore = finalScore; }
	int getFinalScore() { return finalScore; }
	void setPlayerNumber(int number) { playerNumber = number; }
	int getPlayerNumber() { return playerNumber; }
	void setFinalPosition(int pos) { finalPosition = pos; }
	int getFinalPosition() { return finalPosition; }
	
private://members
	GamePad * m_gamePad;
	//needs to be changed to an enum
	int m_carSelection;
	int finalScore;
	int playerNumber;
	int finalPosition;

};