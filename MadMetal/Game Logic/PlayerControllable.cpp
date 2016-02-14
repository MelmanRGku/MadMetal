
#include "PlayerControllable.h"
#include <iostream>
PlayerControllable::PlayerControllable(char * fileName, GamePad * gamePad)
{
	if (fileName == "")
		std::cout << "Passed null gameObject reference to Player Controllable Constructor ABORT!!!!!\n";
	else
		std::cout << "New Player created with character " << fileName << " \n";
	if (gamePad == NULL)
		std::cout << "Passed null gamePad reference to Player Controllable Constructor ABORT!!!!!\n";
	//m_currentModel = &gameObject;
	//m_normalModel = gameObject;
	m_gamePad = gamePad;

	m_currentTime = 0;
	m_isAlive = true;
	m_points = 0;
	m_reloadRate = .500;

	m_isSuperMode = false;

}

PlayerControllable::~PlayerControllable()
{
	m_gamePad = NULL;
	delete m_camera;
}

void PlayerControllable::setObject(Car * toAdd) { m_car = toAdd; }
void PlayerControllable::setCamera(Camera * camera){ m_camera = camera; }

GamePad * PlayerControllable::getGamePad(){ return m_gamePad; }

void PlayerControllable::playFrame(double dt)
{
	update(dt);
	if (m_gamePad->checkConnection())
	{
		
		if (m_isAlive)
		{
			
			if (m_gamePad->isPressed(GamePad::DPadLeft))
			{
				
				//m_car->getActor().setLinearVelocity(PxVec3(10, 0, 0));
				//m_car->getActor().setAngularVelocity(PxVec3(10, 10, 10));
			}

			if (m_gamePad->isPressed(GamePad::DPadRight))
			{
				
				//m_car->getActor().setLinearVelocity(PxVec3(-10, 0, 0));
			}

			if (m_gamePad->isPressed(GamePad::DPadUp))
			{

				//m_car->getActor().setLinearVelocity(PxVec3(0, 0, 10));
			}

			if (m_gamePad->isPressed(GamePad::DPadDown))
			{

				//m_car->getActor().setLinearVelocity(PxVec3(0, 0, -10));
			}


			/*if (m_gamePad->isPressed(GamePad::XButton))
			{
				std::cout << "Xpressed \n";
			}

			if (m_gamePad->isPressed(GamePad::YButton))
			{
				std::cout << "Ypressed \n";
			}

			if (m_gamePad->isPressed(GamePad::AButton))
			{
				std::cout << "Apressed \n";
			}

			if (m_gamePad->isPressed(GamePad::BButton))
			{
				std::cout << "Bpressed \n";
			}

			if (m_gamePad->isPressed(GamePad::StartButton))
			{
				std::cout << "Startpressed \n";
			}

			if (m_gamePad->isPressed(GamePad::LShoulder))
			{
				std::cout << "LShoulderpressed \n";
			}

			if (m_gamePad->isPressed(GamePad::RShoulder))
			{
				std::cout << "RShoulderpressed \n";
			}
			*/
			if (m_gamePad->getRightTrigger())
			{
				if (m_reloadRemaining <= 0)
				{
					m_reloadRemaining = m_reloadRate;
					PxRigidDynamic * projectile = m_car->getActor().getScene()->getPhysics().createRigidDynamic(m_car->getActor().getGlobalPose());
					projectile->setLinearVelocity(PxVec3(0, 0, 20));
					projectile->createShape(PxSphereGeometry(0.5), *m_car->getActor().getScene()->getPhysics().createMaterial(PxReal(0.1), PxReal(0.1), PxReal(0.1)));
					m_car->getActor().getScene()->addActor(*projectile);
			}

			}
			/*
			if (m_gamePad->getLeftTrigger())
			{
				std::cout << "LeftTriggpressed \n";
			}*/
			if (m_camera != NULL)
			{
				m_camera->rotateCamera(m_gamePad->getRightStick().x, m_gamePad->getRightStick().y);
			}
		}
		else {
			//do nothing cause you dead bro
		}
		
		float speed = 20;
		//m_car->setLinearVelocity(PxVec3(-m_gamePad->getLeftStick().x * speed, 0, m_gamePad->getLeftStick().y * speed));

		//change force direction
		//m_currentGameObject->setDirection(vec3(m_gamePad->getLeftStick().x, 0, m_gamePad->getLeftStick().y)

		//change camera direction
		//m_camera->rotate(vec3(m_gamePad->getRightStick().x, m_gamePad->getRightStick().y,0)
	}
	else {
		//pause(this);
	}
	
	
}

