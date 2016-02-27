#pragma once

#include "PxVehicleDrive4W.h"
#include "../TestObject.h"
#include "Objects\DrivingStyle.h"

class Car : public TestObject
{
private:
	PxVehicleDrive4W &m_car;

public:
	Car(PxVehicleDrive4W &car, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio);
	~Car();

	PxVehicleDrive4W &getCar();
};

