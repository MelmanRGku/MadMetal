
#include "PlayerControllable.h"
#include <iostream>

// assign car to player and set camera to follow it
void PlayerControllable::setCar(Car * toAdd) 
{ 
	m_car = toAdd; 
	m_camera->setToFollow(toAdd);
	
}

GamePad * PlayerControllable::getGamePad(){ return m_gamePad; }

void PlayerControllable::playFrame(double dt)
{
	m_camera->update(dt);
	if (m_car->isAlive())
	{
		if (m_gamePad != NULL && m_gamePad->checkConnection())
		{
			//std::cout << m_car->getCar().computeForwardSpeed() << std::endl;
			/*
			if (m_gamePad->isPressed(GamePad::LJoyRight))
			{
			std::cout << "Left Joy Pressed \n";
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
			}*/


			if (m_gamePad->isHeld(GamePad::XButton))
			{
				m_car->fire();
			}

			if (m_gamePad->isPressed(GamePad::YButton)) {
				if (m_car->superReady()) {
					m_car->useSuper();
					std::cout << "I shot" << std::endl;
				}
			}

			if (m_gamePad->isHeld(GamePad::BButton))
			{
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_HANDBRAKE, 1);

			}
			else {
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_HANDBRAKE, 0);
			}

			/*
			if (m_gamePad->isPressed(GamePad::AButton))
			{


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
			}*/

			if (m_gamePad->getRightTrigger())
			{

				if (m_car->getCar().mDriveDynData.getCurrentGear() == PxVehicleGearsData::eREVERSE)
				{
					m_car->getCar().mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
				}
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL,
					m_car->getDrivingStyle().getMaxSpeed() > m_car->getCar().computeForwardSpeed() ? m_gamePad->getRightTrigger() : 0);


			}
			else if (m_gamePad->getLeftTrigger())
			{
				m_car->getCar().mDriveDynData.forceGearChange(PxVehicleGearsData::eREVERSE);
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, m_gamePad->getLeftTrigger());
			}
			else
			{
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, 0);
			}

			if (m_gamePad->getLeftStick().x)
			{
				if (m_gamePad->getLeftStick().x < 0)
				{
					m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_RIGHT, 0);
					m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_LEFT, m_gamePad->getLeftStick().x);

				}

				if (m_gamePad->getLeftStick().x > 0)
				{
					m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_LEFT, 0);
					m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_RIGHT, -m_gamePad->getLeftStick().x);
				}
			}
			else
			{
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_RIGHT, 0);
				m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_LEFT, 0);
			}

			if (m_camera != NULL)
			{
				m_camera->rotateCamera(m_gamePad->getRightStick().x, m_gamePad->getRightStick().y);
			}
		}
		else
		{
			//do nothing cause you dead bro
		}
	}
 else {
	 m_car->respawn();
 }
	
}

