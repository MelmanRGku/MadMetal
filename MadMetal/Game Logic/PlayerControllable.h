#pragma once
#include "Controllable.h"
#include "..\Input\GamePad.h"
#include "Objects\Object.h"
#include "Objects\Cars\Car.h"
#include "Objects\Camera.h"


class PlayerControllable : public Controllable
{
private:
	char * m_fileName;
	GamePad * m_gamePad;
	Car* m_car;

	Camera * m_camera;

public:
	PlayerControllable(ControllableTemplate& controllableTemplate) : Controllable(controllableTemplate);
	virtual ~PlayerControllable();
	void playFrame(double dt);
	void setCamera(Camera * camera);
	GamePad * getGamePad();
	void setObject(Car * toAdd);
	Car *getObject() { return m_car; }
};