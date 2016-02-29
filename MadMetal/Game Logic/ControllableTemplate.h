#pragma once
#include "Input\GamePad.h"

class ControllableTemplate
{
public:
	ControllableTemplate(int carSelection): m_carSelection(carSelection){};
	ControllableTemplate(GamePad * gamePad) : m_gamePad(gamePad){};
	
	~ControllableTemplate()
	{
		m_gamePad = NULL;
	}

	GamePad* getGamePad() { return m_gamePad; }
	int getCarSelection() { return m_carSelection; }
	void setCarSelection(int selection) { m_carSelection = selection; }
	bool isHumanPlayer() { return m_gamePad == NULL; }
	
private://members
	GamePad * m_gamePad;
	//needs to be changed to an enum
	int m_carSelection;


};