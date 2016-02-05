#include "PlayerControllable.h"
PlayerControllable::PlayerControllable(GameObject * gameObject, GamePad * gamePad)
{
	if (gameObject == NULL)
		std::cout << "Passed null gameObject reference to Player Controllable Constructor ABORT!!!!!\n";
	if (gamePad == NULL)
		std::cout << "Passed null gamePad reference to Player Controllable Constructor ABORT!!!!!\n";
	m_currentModel = &gameObject;
	m_normalModel = gameObject;
	m_gamePad = gamePad;

	m_currentTime = 0;
	m_isAlive = true;
	m_points = 0;

	m_isSuperMode = false;

}

PlayerControllable::~PlayerControllable()
{
	m_currentModel = NULL;
	m_normalModel = NULL;
	m_superModel = NULL;
	m_gamePad = NULL;
}

void PlayerControllable::playFrame(double dt)
{
	update(dt);
	if (m_gamePad->checkConnection())
	{
		if (m_isAlive)
		{
			if (m_gamePad->isPressed(GamePad::XButton))
			{

			}

			if (m_gamePad->isPressed(GamePad::YButton))
			{

			}

			if (m_gamePad->isPressed(GamePad::AButton))
			{

			}

			if (m_gamePad->isPressed(GamePad::BButton))
			{

			}

			if (m_gamePad->isPressed(GamePad::StartButton))
			{

			}

			if (m_gamePad->isPressed(GamePad::LShoulder))
			{

			}

			if (m_gamePad->isPressed(GamePad::RShoulder))
			{

			}

			if (m_gamePad->getRightTrigger())
			{

			}

			if (m_gamePad->getLeftTrigger())
			{

			}
		}
		else {
			//do nothing cause you dead bro
		}
		

		//change force direction
		//m_currentGameObject->setDirection(vec3(m_gamePad->getLeftStick().x, 0, m_gamePad->getLeftStick().y)

		//change camera direction
		//m_camera->rotate(vec3(m_gamePad->getRightStick().x, m_gamePad->getRightStick().y,0)
	}
	else {
		//pause(this);
	}
	
	
}

