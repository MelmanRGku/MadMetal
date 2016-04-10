#pragma once

#include "PxVehicleDrive4W.h"
#include "../Object3D.h"
#include "Objects\Cars\DrivingStyle.h"
#include "Objects\PowerUp.h"
#include "Objects/UI.h"
#include "Global\Definitions.h"

#define INVINICIBILITY_FLASH_PERIOD 0.2f
#define BRAKE_SOUND_DURATION 2.2f

class Waypoint;
class CollisionVolume;

class Car : public Object3D
{
protected: //members

	//physics object
	DrivingStyle* m_drivingStyle;
	PxVehicleDrive4W &m_car;

	//score based
	float m_damageDealt;
	int m_currentLap;
	int m_positionInRace;
	bool m_finishedRace;
	int m_score;

	//current state 
	float m_currentHealth;
	float m_maxHealth;
	float m_reloadRateSeconds; //seconds
	float m_superReloadRateSeconds;
	float m_reloadRemainingSeconds;
	float m_superGauge; // 0-1
	float m_superMaxDurationSeconds; //seconds
	float m_superDurationRemainingSeconds; //seconds
	float m_deathTimerMillis;
	Waypoint* m_currentWaypoint, *m_lastWayPoint;
	Waypoint *m_nextWaypoint;
	bool m_isAtStartingCollisionVolume;
	bool m_isAtMidCollisionVolume;
	bool m_isInAir;
	CollisionVolume* m_lastCollisionVolume;

	bool m_newLap;

	Sound soundChassis;

	virtual void unuseSuper() = 0;
	
	PowerUpType m_heldPowerUp;
	PowerUpType m_activePowerUp;
	float m_powerUpRemaining;
	static int positionGlobalID;

	float m_invincibilityTimeRemaining;
	float m_timeSinceLastTimeHit;
	float m_timeSinceRespawn;
	float m_smokeCounterTime;

	Object3D *m_shadow;
	float lastKnownDistanceBetweenCarAndShadow;

	int brakeChannelNumber;
	float brakeStartTime;
private:
	//update functions
	void updatePowerUp(float dt);
	void updateReload(float dt);
	void updateSuper(float dt);
	void updateOrientation(float dt);
	void createSmoke(float dt);

public:

	UI *ui;
	float distanceTraveled = 0;

	Car(long id, DrivingStyle* style, PxVehicleDrive4W &car, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);
	virtual ~Car();

	PxVehicleDrive4W &getCar() { return m_car; }
	DrivingStyle& getDrivingStyle();
	
	//void usePowerUp();
	bool isAlive() { return m_currentHealth > 0; }
	virtual void useSuper();
	virtual void fire() = 0;
	bool takeDamage(float damage, bool applyAnyway = false);
	
	virtual void update(float dt);
	void addDamageDealt(float damage, bool addToSuper = true);
	bool superReady() { return m_superGauge >= 1.f; }
	float getSuperGauge() { return m_superGauge > 1.f ? 1.f : m_superGauge; }
	int getScore() { return m_score; }
	void addToScore(int points) { m_score += points; }
	void respawn();
	bool setCurrentWaypoint(Waypoint* waypoint);							//true if the waypoint is new, false otherwise
	Waypoint* getCurrentWaypoint();
	void incrementLap();
	int getLap();
	int getPositionInRace();
	void setPositionInRace(int position);
	void setSoundChassis(Sound sound);
	void playSoundChassis();
	bool isAtStartingCollisionVolume();
	bool isAtMidCollisionVolume();
	int tallyScore() { return m_score; }
	Waypoint* Car::getLastWaypoint();
	void setLastWaypoint(Waypoint* waypoint);
	bool isFinishedRace() { return m_finishedRace; }
	void setFinishedRace(bool finished) { m_finishedRace = finished; }
	void setStartingCollisionVolumeFlag(bool isHit);
	void setMidCollisionVolumeFlag(bool isHit);
	void pickUpPowerUp(PowerUpType type);
	void usePowerUp();
	PowerUpType getActivePowerUpType();
	PowerUpType getHeldPowerUp();
	UI *getUI() { return ui; }
	void deactivatePowerUp(){ m_activePowerUp = PowerUpType::NONE; }
	void updateHealth(float dtMillis);

	float getSuperMaxDuration() { return m_superMaxDurationSeconds; }
	float getSuperDurationRemaining(){ return m_superDurationRemainingSeconds; }
	
	float getHealthRemaining(){ return m_currentHealth; }

	void addWaypointHit(Waypoint* waypoint);
	std::vector<Waypoint*> m_waypointHitList;
	void setIsInAir(bool inAir) { m_isInAir = inAir; }

	void setLastHitCollisionVolume(CollisionVolume* collisionVolume);
	CollisionVolume* getLastHitCollisionVolume();

	static void resetGlobalPositionID();

	virtual bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	bool isInvincible();
	float getInvinsibilityTimeRemaining();
	void setInvincibility(float time);
	float getTimeSinceLastTimeHit();

	void setShadow(Object3D *shadow);
	void onBrake();
	void onUnbrake();

};

