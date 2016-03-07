#pragma once

#include "PxVehicleDrive4W.h"
#include "../TestObject.h"
#include "Objects\DrivingStyle.h"
#include "Game Logic\PowerUp.h"
#include "Objects\HealthBar2D.h"
#include "Objects\GaugeBar.h"
#include "Objects\Text2D.h"

class Waypoint;

class Car : public TestObject
{
protected: //members

	//physics object
	DrivingStyle& m_drivingStyle;
	PxVehicleDrive4W &m_car;

	//score based
	float m_damageDealt;
	int m_currentLap;

	//current state 
	float m_currentHealth;
	float m_maxHealth;
	float m_reloadRateSeconds; //seconds
	float m_reloadRemainingSeconds;
	float m_superGauge; // 0-1
	float m_superMaxDurationSeconds; //seconds
	float m_superDurationRemainingSeconds; //seconds
	Waypoint* m_currentWaypoint;

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

	//TODO: change to separate UI class
	HealthBar2D *healthBar;
	GaugeBar *gaugeBar;
	Text2D *score;


	Car(long id, DrivingStyle& style, PxVehicleDrive4W &car, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio* audio);
	~Car();

	PxVehicleDrive4W &getCar() { return m_car; }
	DrivingStyle& getDrivingStyle();
	
	//void usePowerUp();
	virtual void useSuper() = 0;
	virtual void fire() = 0;
	void takeDamage(float damage);
	void increaseDamageDealt(float damage);
	virtual void update(float dt);
	void addDamageDealt(float damage);
	bool superReady() { return m_superGauge >= 1.f; }
	float getSuperGauge() { return m_superGauge > 1.f ? 1.f : m_superGauge; }
	int getScore();
	void setCurrentWaypoint(Waypoint* waypoint);
	Waypoint* getCurrentWaypoint();
	
	
};

