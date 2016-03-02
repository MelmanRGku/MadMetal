#include "Car.h"
#include "../DrivingStyleFast.h"
#include "Factory\GameFactory.h"

Car::Car(long id, PxVehicleDrive4W &car, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio) : TestObject(id, aable, pable, anable, rable, audio), m_car(car)
{
}


Car::~Car()
{
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

void Car::takeDamage(float damage)
{
	//car set to dead will be dealt with in the update function
	m_currentHealth -= damage;
	std::cout << "Oh no, my health just decreased to " << m_currentHealth << std::endl;
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

void Car::update(float dt) {
	m_reloadRemaining -= dt;
}