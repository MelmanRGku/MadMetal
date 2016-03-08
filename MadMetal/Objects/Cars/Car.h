#pragma once

#include "PxVehicleDrive4W.h"
#include "../TestObject.h"
#include "Objects\DrivingStyle.h"
#include "Game Logic\PowerUp.h"
#include "Objects/UI.h"

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
	float m_superReloadRateSeconds;
	float m_reloadRemainingSeconds;
	float m_superGauge; // 0-1
	float m_superMaxDurationSeconds; //seconds
	float m_superDurationRemainingSeconds; //seconds
	Waypoint* m_currentWaypoint, *m_lastWayPoint;
	Waypoint *m_nextWaypoint;
	bool m_isAtStartingCollisionVolume;
	bool m_isAtMidCollisionVolume;

	Sound * soundChassis;

	virtual void unuseSuper() = 0;
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

	UI *ui;

	Car(long id, DrivingStyle& style, PxVehicleDrive4W &car, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable);
	~Car();

	PxVehicleDrive4W &getCar() { return m_car; }
	DrivingStyle& getDrivingStyle();
	
	//void usePowerUp();
	bool isAlive() { return m_currentHealth > 0; }
	virtual void useSuper() = 0;
	virtual void fire() = 0;
	void takeDamage(float damage);
	void increaseDamageDealt(float damage);
	virtual void update(float dt);
	void addDamageDealt(float damage);
	bool superReady() { return m_superGauge >= 1.f; }
	float getSuperGauge() { return m_superGauge > 1.f ? 1.f : m_superGauge; }
	int getScore();
	void respawn();
	bool setCurrentWaypoint(Waypoint* waypoint);							//true if the waypoint is new, false otherwise
	Waypoint* getCurrentWaypoint();
	void incrementLap();
	int getLap();
	void setSoundChassis(Sound * sound);
	void playSoundChassis();
	bool isAtStartingCollisionVolume();
	bool isAtMidCollisionVolume();

	void setStartingCollisionVolumeFlag(bool isHit);
	void setMidCollisionVolumeFlag(bool isHit);
};

