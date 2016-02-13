#pragma once
#include "Controllable.h"
#include "..\Input\GamePad.h"
#include "Objects\Object.h"
#include "Objects\Car.h"

class PlayerControllable : public Controllable
{
private:
	char * m_fileName;
	GamePad * m_gamePad;
	Car* m_car;

public:
	PlayerControllable(char * fileName, GamePad * gamePad);
	virtual ~PlayerControllable();
	void playFrame(double dt);
	GamePad * getGamePad();
	void setObject(Car * toAdd);
	Car *getObject() { return m_car; }
};