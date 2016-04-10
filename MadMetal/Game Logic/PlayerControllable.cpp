
#include "PlayerControllable.h"
#include <iostream>
#include <Files\FIleHandlingHelpers.h>
#include <string>

// assign car to player and set camera to follow it
void PlayerControllable::setCar(Car * toAdd)
{
	m_car = toAdd;
	m_camera->setToFollow(toAdd);

}

GamePad * PlayerControllable::getGamePad(){ return m_gamePad; }

void PlayerControllable::playFrame(double dt)
{
	if (m_car->isAlive()) m_camera->update(dt);

	if (!m_controlsPaused) {
			
		if (m_car->isAlive())
		{
			
			if (m_gamePad != NULL && m_gamePad->checkConnection())
			{
				if (m_car->getCar().getRigidDynamicActor()->isSleeping()) {
					m_car->getCar().getRigidDynamicActor()->wakeUp();
				}
				
				if (m_gamePad->isHeld(GamePad::XButton))
				{
					m_car->fire();
				}
				if (m_gamePad->isPressed(GamePad::DPadUp))
				{
					float angle;
					PxVec3 axis;
					m_car->getCar().getRigidDynamicActor()->getGlobalPose().q.toRadiansAndUnitAxis(angle, axis);
					PxVec3 position = m_car->getCar().getRigidDynamicActor()->getGlobalPose().p;
					std::cout << "Position " << position.x << "," << position.y << "," << position.z << std::endl;
					std::cout << "Angle " << angle << "    " << axis.x << "," << axis.y << "," << axis.z << std::endl;
				}

				if (m_gamePad->isPressed(GamePad::YButton)) {
					if (m_car->superReady()) {
						m_car->useSuper();
					}
				}

				if (m_gamePad->isPressed(GamePad::BButton)) {
					m_car->onBrake();
				}
				else if (!m_gamePad->isHeld(GamePad::BButton)){
					m_car->onUnbrake();
				}

				if (m_gamePad->isHeld(GamePad::BButton))
				{
					m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_HANDBRAKE, 1);
					if (m_car->getActivePowerUpType() == PowerUpType::SPEED)
					{
						m_car->deactivatePowerUp();
					}

				}
				else {
					m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_HANDBRAKE, 0);
				}

				
				if (m_gamePad->isPressed(GamePad::AButton))
				{
					m_car->usePowerUp();


				}

				if (m_gamePad->isPressed(GamePad::BackButton))
				{
					m_car->respawn();
				}

				if (m_gamePad->getRightTrigger())
				{
					if (m_car->getActivePowerUpType() != PowerUpType::SPEED)
					{
						if (m_car->getCar().computeForwardSpeed() < -0.1)
						{
							m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_HANDBRAKE, 1);
						}
						else {
							m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_HANDBRAKE, 0);
							if (m_car->getCar().mDriveDynData.getCurrentGear() == PxVehicleGearsData::eREVERSE)
							{
								m_car->getCar().mDriveDynData.setCurrentGear(PxVehicleGearsData::eFIRST);
							}
							m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL,
								m_car->getDrivingStyle().getMaxSpeed() > m_car->getCar().computeForwardSpeed() ? m_gamePad->getRightTrigger() : 0);
						}
					}

				}
				else if (m_gamePad->getLeftTrigger())
				{
					if (m_car->getCar().computeForwardSpeed() > 0.1)
					{
						m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_HANDBRAKE, 1);
					} 
					else {
						m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_HANDBRAKE, 0);
						if (m_car->getCar().mDriveDynData.getCurrentGear() != PxVehicleGearsData::eREVERSE) {
							m_car->getCar().mDriveDynData.setCurrentGear(PxVehicleGearsData::eREVERSE);
						}
						m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, m_gamePad->getLeftTrigger());
					}
				}
				else
				{
					m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, 0);
				}

				float turnScalar = 1;
				if (m_car->getActivePowerUpType() == PowerUpType::SPEED)
				{
					turnScalar = 0.2;
				}
				if (m_gamePad->getLeftStick().x)
				{
					if (m_gamePad->getLeftStick().x < 0)
					{
						const PxF32 vz = m_car->getCar().computeForwardSpeed();
						const PxF32 vzAbs = PxAbs(vz);
						const PxF32 maxSteer = gSteerVsForwardSpeedTable.getYVal(vzAbs);
						PxF32 steer = PxAbs(m_gamePad->getLeftStick().x);
						if (steer>maxSteer)
						{
							const PxF32 k = maxSteer / steer;
							steer *= k;
						}
						m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_RIGHT, 0);
						m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_LEFT, -steer * turnScalar);

					}

					if (m_gamePad->getLeftStick().x > 0)
					{
						const PxF32 vz = m_car->getCar().computeForwardSpeed();
						const PxF32 vzAbs = PxAbs(vz);
						const PxF32 maxSteer = gSteerVsForwardSpeedTable.getYVal(vzAbs);
						PxF32 steer = PxAbs(m_gamePad->getLeftStick().x);
						if (steer>maxSteer)
						{
							steer = maxSteer;
						}
						m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_LEFT, 0);
						m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_STEER_RIGHT, -steer * turnScalar);
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
		}
	}
}

