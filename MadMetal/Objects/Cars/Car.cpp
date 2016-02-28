#include "Car.h"
#include "../DrivingStyleFast.h"

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

/*
void Car::usePowerUp()
{
	//if not holding a power up do nothing
	if (m_heldPowerUp.getType() == NONE)
		return;

	//set active power up to power up being held. Set held power up to NONE
	m_activePowerUp.setPowerUp(m_heldPowerUp.getType());
	m_heldPowerUp.setPowerUp(NONE);
	//start duration of power up to specific power up time
	m_powerUpDurationRemaining = m_activePowerUp.getPowerUpDuration();

}

void Controllable::pickUpPowerUp(PowerUpType type)
{
	m_heldPowerUp.setPowerUp(type);
}
*/

void Car::fire()
{
	if (m_reloadRemaining > 0)
		return;

	m_reloadRemaining = m_reloadRate;
	/*if (m_superDurationRemaining > 0)
	{
		if (m_activePowerUp.getType() == ATTACK)
		{
			//spawn a super projectile with vampiric callback
		}

		else {
			//spawn a super projectile
		}
	}
	else {
		if (m_activePowerUp.getType() == ATTACK)
		{
			//spawn a regular projectile with vampiric callback
		}

		else {
			//spawn a regular projectile
		}
	}
	*/

}

void Car::takeDamage(float damage)
{
	//car set to dead will be dealt with in the update function
	m_currentHealth -= damage;
}

void Car::increaseDamageDealt(float damage)
{
	m_damageDealt += damage;
}

void Car::useSuper()
{
	if (m_superGuage == 1)
	{
		m_superDurationRemaining = m_superMaxDuration;
		//	Handle swaping character model
	}
}

void Car::updateReload(float dt)
{
	if (m_reloadRemaining > 0)
		m_reloadRemaining -= dt;
}

void Car::updatePowerUp(float dt)
{
	/*if (m_powerUpDurationRemaining > 0)
	{

		if ((m_powerUpDurationRemaining -= dt) <= 0)
		{
			m_activePowerUp.setPowerUp(NONE);
		}
	}*/
}

void Car::updateSuper(float dt)
{
	if (m_superDurationRemaining > 0)
	{
		if ((m_superDurationRemaining -= dt) <= 0)
		{
			//m_currentModel = &m_normalModel;
		}

	}
}
