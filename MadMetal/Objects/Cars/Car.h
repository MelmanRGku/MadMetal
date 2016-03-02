#pragma once

#include "PxVehicleDrive4W.h"
#include "../TestObject.h"
#include "Objects\DrivingStyle.h"
#include "Game Logic\PowerUp.h"

class Car : public TestObject
{
protected: //members

	//physics object
	DrivingStyle* m_drivingStyle;
	PxVehicleDrive4W &m_car;

	//score based
	float m_damageDealt;
	int m_currentLap;

	//current state 
	float m_currentHealth;
	float m_maxHealth;
	float m_reloadRate; //milliseconds
	float m_reloadRemaining;
	float m_superGuage; // 0-1
	float m_superMaxDuration; //milliseconds
	float m_superDurationRemaining; //milliseconds

	/*
		Need to be implemented
		Projectile * m_ammuntion;
		PowerUp m_heldPowerUp;
		PowerUp m_activePowerUp;
	*/
private:
	//update functions
	void updatePowerUp(float dt);
	void updateReload(float dt);
	void updateSuper(float dt);

public:
	Car(long id, PxVehicleDrive4W &car, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio);
	~Car();

	PxVehicleDrive4W &getCar() { return m_car; }
	DrivingStyle& getDrivingStyle();
	
	//void usePowerUp();
	void useSuper();
	virtual void fire() = 0;
	void takeDamage(float damage);
	void increaseDamageDealt(float damage);
	virtual void update(float dt);
	
	
};

