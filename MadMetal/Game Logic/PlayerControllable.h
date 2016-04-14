#pragma once
#include "Controllable.h"
#include "..\Input\GamePad.h"
#include "Objects\Camera.h"
#include "Audio\Audio.h"
#include "Audio\Sound.h"


class PlayerControllable : public Controllable
{
private:
	GamePad * m_gamePad;
	float m_positionPenalty;
	Camera* m_camera;
	

public:
	
	PlayerControllable(ControllableTemplate& controllableTemplate) : Controllable(controllableTemplate)
	{
		m_gamePad = controllableTemplate.getGamePad();
		m_camera = new Camera();
		m_positionPenalty = 0;
	}

	PlayerControllable::~PlayerControllable()
	{
		m_gamePad = NULL;
		delete m_camera;
		//delete m_car;
	}
	
	void playFrame(double dt);
	void setCar(Car* toAdd);
	GamePad * getGamePad();
	Camera * getCamera() { return m_camera; }
	void assignPositionPenalty();
	
};