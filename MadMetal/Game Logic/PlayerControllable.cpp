
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

void PlayerControllable::setObject(PxRigidDynamic * toAdd) { m_car = toAdd; }
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
				
				m_car->setLinearVelocity(PxVec3(10, 0, 0));
				
			}

			if (m_gamePad->isPressed(GamePad::DPadRight))
			{
				
				m_car->setLinearVelocity(PxVec3(-10, 0, 0 ));
			}

			if (m_gamePad->isPressed(GamePad::DPadUp))
			{
				std::cout << "pressed";
				m_car->setLinearVelocity(PxVec3(0, 0, 10));
			}

			if (m_gamePad->isPressed(GamePad::DPadDown))
			{

				m_car->setLinearVelocity(PxVec3(0, 0, -10));
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
					PxRigidDynamic * projectile = m_car->getScene()->getPhysics().createRigidDynamic(m_car->getGlobalPose());
					projectile->setLinearVelocity(PxVec3(0, 10, 20));
					projectile->createShape(PxSphereGeometry(0.1), *m_car->getScene()->getPhysics().createMaterial(0, 0, 0));
					projectile->setGlobalPose(m_car->getGlobalPose());
					m_car->getScene()->addActor(*projectile);
					RenderableObject * newShot = new RenderableObject(*m_ammuntion->getObject());
					newShot->setActor(projectile);
					m_gameWorld->addGameObject(newShot);
					
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
		
		float speed = 50;
		if (m_gamePad->getLeftStick().x || m_gamePad->getLeftStick().y)
		{
			m_car->setLinearVelocity(PxVec3(m_gamePad->getLeftStick().x * -speed, 0, m_gamePad->getLeftStick().y * speed));
		}
			
		
		
		

		
	}
	else {
		//pause(this);
	}
	
	
}

