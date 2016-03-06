#pragma once
#include "AIControllable.h"

void AIControllable::playFrame(double dtmilli)
{
	/*
	if (m_gamePad->getRightTrigger())
	{
		if (m_car->getCar().mDriveDynData.getCurrentGear() == PxVehicleGearsData::eREVERSE)
		{
			m_car->getCar().mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
		}
		m_car->getCar().mDriveDynData.setAnalogInput(PxVehicleDrive4WControl::eANALOG_INPUT_ACCEL, m_gamePad->getRightTrigger());
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
	*/
}

void AIControllable::setCar(Car* toAdd)
{
	m_car = toAdd;
}