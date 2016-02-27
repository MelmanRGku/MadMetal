#include "Car.h"
#include "../DrivingStyleFast.h"

Car::Car(PxVehicleDrive4W &car, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio) : TestObject(aable, pable, anable, rable, audio), m_car(car)
{
}


Car::~Car()
{
}

PxVehicleDrive4W& Car::getCar()
{
	return m_car;
}