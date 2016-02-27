#pragma once

#include "PxVehicleDrive4W.h"
#include "../TestObject.h"
#include "Objects\DrivingStyle.h"

class Car : public TestObject
{
private:
	PxVehicleDrive4W *m_car;
	DrivingStyle* m_drivingStyle;

public:
	Car();
	~Car();

	void setCar(PxVehicleDrive4W *m_car);
	PxVehicleDrive4W *getCar();

	DrivingStyle& getDrivingStyle();
};

