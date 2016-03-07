#include "Car.h"
#include "../DrivingStyleFast.h"
#include "Factory\GameFactory.h"
#include <sstream>

Car::Car(long id, DrivingStyle& style, PxVehicleDrive4W &car, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable) : TestObject(id, aable, pable, anable, rable), m_car(car), m_drivingStyle(style)
{
}


Car::~Car()
{
}

DrivingStyle& Car::getDrivingStyle()
{
	return m_drivingStyle;
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
}

void Car::increaseDamageDealt(float damage)
{
	m_damageDealt += damage;
}

void Car::updateReload(float dt)
{
	if (m_reloadRemainingSeconds > 0)
		m_reloadRemainingSeconds -= dt;
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
	if (m_superDurationRemainingSeconds > 0)
	{
		if ((m_superDurationRemainingSeconds -= dt) <= 0)
		{
			//m_currentModel = &m_normalModel;
		}

	}
}

void Car::update(float dt) {
	m_reloadRemainingSeconds -= dt;
	if (m_superDurationRemainingSeconds > 0) m_superDurationRemainingSeconds -= dt;
	healthBar->setHealthPercentage(m_currentHealth / m_maxHealth);
	gaugeBar->setGaugePercentage(getSuperGauge());

	std::stringstream s;
	s << "Score: " << getScore();
	score->setString(s.str());
	if (m_currentHealth < 0) {
		hasToBeDeleted = true;
	}
}

void Car::addDamageDealt(float damage) {
	m_damageDealt += damage;
	m_superGauge += damage / 100;
}

int Car::getScore() {
	return m_damageDealt;
}