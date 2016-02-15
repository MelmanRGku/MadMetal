#include "Car.h"
#include "DrivingStyleFast.h"

Car::Car()
{
	m_drivingStyle = new DrivingStyleFast();
}


Car::~Car()
{
	delete m_drivingStyle;
}

void Car::setCar(PxVehicleDrive4W *m_car)
{ 
	this->m_car = m_car; 
	this->physicsActor = m_car->getRigidDynamicActor(); 
}

PxVehicleDrive4W* Car::getCar()
{
	return m_car;
}

DrivingStyle& Car::getDrivingStyle()
{
	return *m_drivingStyle;
}