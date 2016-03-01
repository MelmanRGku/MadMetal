#pragma once
#include "Simulation\World.h"
#include "Projectile.h"
#include "PowerUp.h"
#include "WayPointSystem.h"

class Controllable
{
protected:

	float m_currentTime;

	bool m_isAlive;
	float m_points;
	int m_laps;
	float m_currentHealth;
	float m_maxHealth;

	//float m_currentSpeed;
	//float m_maxSpeed;
	//float m_currentAcceleration;

	float m_accelMultiplier;
	float m_turnMultiplier;
	float m_defenseMultiplier;
	
	float m_reloadRate;
	double m_reloadRemaining;

	float m_superGuage;
	float m_superMaxDuration;
	double m_superDurationRemaining;
	bool m_isSuperMode;



	PowerUp m_heldPowerUp;
	PowerUp m_activePowerUp;
	
	WayPoint * m_currentWayPoint;
	WayPoint * m_nextWayPoint;

	Projectile * m_ammuntion;

	World * m_gameWorld;

	double m_powerUpDurationRemaining;

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
	void setWayPoint(WayPoint * wayPoint, bool finishLine);
	void setAmmunition(Projectile * newAmmo);
	void setGameWorld(World * world);
	void useSuper();
	
	virtual void fire();
	void takeDamage(float damage);
	void receivePoints(float points);

	
	
};