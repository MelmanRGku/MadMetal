#pragma once
#include "Controllable.h"
#include "..\Input\GamePad.h"
#include "Objects\Object.h"
#include "Objects\Cars\Car.h"
#include "Objects\Camera.h"
#include "Audio\Audio.h"
#include "Audio\Sound.h"


class PlayerControllable : public Controllable
{
private:
	GamePad * m_gamePad;
	//Car* m_car;
	Camera* m_camera;
	

public:
	
	PlayerControllable(ControllableTemplate& controllableTemplate) : Controllable(controllableTemplate)
	{
		m_gamePad = controllableTemplate.getGamePad();
		m_camera = new Camera();
	}

	PlayerControllable::~PlayerControllable()
	{
		m_gamePad = NULL;
		delete m_camera;
		//delete m_car;
	}
	
	void playFrame(double dt);
	GamePad * getGamePad();
	Camera * getCamera() { return m_camera; }
	void setCar(Car * toAdd);
	//Car *getCar() { return m_car; }
};