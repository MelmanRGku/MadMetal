#pragma once
#include "Controllable.h"
#include "..\Input\GamePad.h"
#include "Objects\Object.h"
#include "Objects\Camera.h"
class PlayerControllable : public Controllable
{
private:
	char * m_fileName;
	GamePad * m_gamePad;
	Object * m_car;
	Camera * m_camera;

public:
	PlayerControllable(char * fileName, GamePad * gamePad);
	virtual ~PlayerControllable();
	void playFrame(double dt);
	void setCamera(Camera * camera);
	GamePad * getGamePad();
	void setObject(Object * toAdd);
};