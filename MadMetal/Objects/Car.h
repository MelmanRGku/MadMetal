#pragma once

#include "PxVehicleDrive4W.h"
#include "RenderableObject.h"

class Car : public RenderableObject
{
private:
	PxVehicleDrive4W *car;
public:
	Car();
	~Car();

	void setCar(PxVehicleDrive4W *car) { this->car = car; this->physicsActor = car->getRigidDynamicActor(); }
};

