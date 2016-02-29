#pragma once

#include "PxVehicleDrive4W.h"
#include "../RenderableObject.h"
#include "Objects\DrivingStyle.h"
#include "Game Logic\PowerUp.h"


class Car : public RenderableObject
{
protected: //members

	//physics object
	PxVehicleDrive4W *m_car;
	DrivingStyle* m_drivingStyle;

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
	Car();
	~Car();

	void setCar(PxVehicleDrive4W *m_car);
	PxVehicleDrive4W *getCar();
	DrivingStyle& getDrivingStyle();
	
	//void usePowerUp();
	void useSuper();
	void fire();
	void takeDamage(float damage);
	void increaseDamageDealt(float damage);
	
	
};

