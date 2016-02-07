#pragma once
#include "Controllable.h"
#include "..\Input\GamePad.h"
class PlayerControllable : public Controllable
{
private:
	char * m_fileName;
	GamePad * m_gamePad;

public:
	PlayerControllable(char * fileName, GamePad * gamePad);
	virtual ~PlayerControllable();
	void playFrame(double dt);
	GamePad * getGamePad();
};