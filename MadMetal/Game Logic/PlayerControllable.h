#pragma once
#include "Controllable.h"
#include "..\Input\GamePad.h"
#include "Objects\Object.h"
class PlayerControllable : public Controllable
{
private:
	char * m_fileName;
	GamePad * m_gamePad;
	Object * m_car;

public:
	PlayerControllable(char * fileName, GamePad * gamePad);
	virtual ~PlayerControllable();
	void playFrame(double dt);
	GamePad * getGamePad();
	void setObject(Object * toAdd);
};