#include "Controllable.h"

void Controllable::usePowerUp()
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

void Controllable::fire()
{
	if (m_reloadRemaining > 0)
		return;
	
	m_reloadRemaining = m_reloadRate;
	if (m_superDurationRemaining > 0)
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

}

void Controllable::pickUpPowerUp(PowerUpType type)
{
	m_heldPowerUp.setPowerUp(type);
}


void Controllable::takeDamage(float damage)
{
	if ((m_currentHealth -= damage) <= 0)
	{
		m_isAlive = false;
		//respawn
	}
}

void Controllable::receivePoints(float points)
{
	m_points += points;
}

void Controllable::useSuper()
{
	if (m_superGuage == 1)
	{
		m_superDurationRemaining = m_superMaxDuration;
		m_currentModel = &m_superModel;
	}
}

void Controllable::updatePowerUpRemaining(double dt)
{
	if (m_powerUpDurationRemaining > 0)
	{

		if ((m_powerUpDurationRemaining -= dt) <= 0)
		{
			m_activePowerUp.setPowerUp(NONE);
		}
		
	}
}

void Controllable::updateReloadTime(double dt)
{
	if (m_reloadRemaining > 0)
		m_reloadRemaining -= dt;
}

void Controllable::updateSuperRemaining(double dt)
{
	if (m_superDurationRemaining > 0)
	{
		if ((m_superDurationRemaining -= dt) <= 0)
		{
			m_currentModel = &m_normalModel;
		}

	}
}

void Controllable::update(double dt)
{
	updatePowerUpRemaining(dt);
	updateReloadTime(dt);
	updateSuperRemaining(dt);
}

