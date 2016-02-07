#pragma once

#include "PowerUp.h"

class Controllable
{
protected:

	float m_currentTime;

	bool m_isAlive;
	float m_points;
	
	float m_currentHealth;
	float m_maxHealth;

	//float m_currentSpeed;
	//float m_maxSpeed;
	//float m_currentAcceleration;

	float m_accelMultiplier;
	float m_turnMultiplier;
	float m_defenseMultiplier;
	
	float m_reloadRate;
	float m_reloadRemaining;

	float m_superGuage;
	float m_superMaxDuration;
	float m_superDurationRemaining;
	bool m_isSuperMode;

	PowerUp m_heldPowerUp;
	PowerUp m_activePowerUp;
	float m_powerUpDurationRemaining;

public:
	Controllable(){};
	~Controllable(){};
	virtual void playFrame(double dt) = 0;

	void update(double dt);
	void updateReloadTime(double dt);
	void updatePowerUpRemaining(double dt);
	void updateSuperRemaining(double dt);
	void usePowerUp();
	void pickUpPowerUp(PowerUpType type);

	void useSuper();
	
	void fire();
	void takeDamage(float damage);
	void receivePoints(float points);
	
};