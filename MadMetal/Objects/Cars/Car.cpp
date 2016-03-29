#include "Car.h"
#include "../Cars/DrivingStyleMeowMix.h"
#include "Factory\GameFactory.h"
#include <sstream>
#include "Objects\Waypoint.h"
#include "Objects\CollisionVolume.h"

int Car::positionGlobalID = 0;

void Car::resetGlobalPositionID()
{
	Car::positionGlobalID = 0;
}

Car::Car(long id, DrivingStyle* style, PxVehicleDrive4W &car, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable, NULL), m_car(car), m_drivingStyle(style)
{
	m_currentWaypoint = NULL;
	m_isAtMidCollisionVolume = false;
	m_isAtStartingCollisionVolume = false;
	m_lastCollisionVolume = NULL;
	m_newLap = true;
	m_powerUpRemaining = 0;
	Car::positionGlobalID++;
	m_positionInRace = positionGlobalID;
	m_waypointHitList.clear();
}


Car::~Car()
{
	delete ui;
	delete m_drivingStyle;
}

DrivingStyle& Car::getDrivingStyle()
{
	return *m_drivingStyle;
}

void Car::respawn()
{
	//std::cout << "Respawned? \n";
	m_currentHealth = m_maxHealth;
	
	if (m_lastCollisionVolume != NULL)
	{
		
		
		m_car.getRigidDynamicActor()->setGlobalPose(m_lastCollisionVolume->getActor().getGlobalPose());
		
	}
	else {
		//std::cout << "Invalid Waypoint Respawn" << std::endl;
		PxTransform currentPosition = m_car.getRigidDynamicActor()->getGlobalPose();
		m_car.getRigidDynamicActor()->setGlobalPose(PxTransform(PxVec3(currentPosition.p.x, 5, currentPosition.p.z)));
	}

	//m_car.getRigidDynamicActor()->setGlobalPose(PxTransform(PxVec3(0, 5, 0)));

	m_car.getRigidDynamicActor()->setLinearVelocity(PxVec3(0, 0, 0));
	m_car.getRigidDynamicActor()->setAngularVelocity(PxVec3(0, 0, 0));
	
	
}

void Car::useSuper() {
	m_superDurationRemainingSeconds = m_superMaxDurationSeconds;
	m_superGauge = 0;
	if (ui != NULL)
	{
		ui->gaugeBar->superUsed(m_superMaxDurationSeconds);
		ui->gaugeBar->setSuperDurationRemaining(m_superDurationRemainingSeconds);
	}
}

PowerUpType Car::getActivePowerUpType()
{
	return m_activePowerUp;
}

void Car::pickUpPowerUp(PowerUpType type)
{
	if (m_heldPowerUp == PowerUpType::NONE)
	{
		std::cout << "Picked up Power up " << type << std::endl;
		m_heldPowerUp = type;
		if (ui != NULL)
		{
			ui->setPowerup(type);
		}
	}
	
}

void Car::usePowerUp()
{
	if (m_heldPowerUp != PowerUpType::NONE)
	{
		if (ui != NULL)
		{
			ui->unsetPowerup();
		}
		m_activePowerUp = m_heldPowerUp;
		m_heldPowerUp = PowerUpType::NONE;
		m_powerUpRemaining = PowerUp::getPowerUpDuration(m_activePowerUp);
		PxVec3 dim = m_car.getRigidDynamicActor()->getWorldBounds().getDimensions();
		glm::vec3 pos = getGlobalPose();
		pos.y += dim.y/2;
		
		PxGeometry* geom[1];
		switch (m_activePowerUp)
		{
		case (PowerUpType::ATTACK) :
			//add particle system
			geom[0] = new PxSphereGeometry(.1);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_ATTACK_POWERUP, &PxTransform(PxVec3(pos.x, pos.y, pos.x)), geom, this);
			delete geom[0];
			break;
		case (PowerUpType::DEFENSE) :
			
			geom[0] = new PxBoxGeometry(dim.x, dim.y, dim.z);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_SHIELD_POWERUP, &PxTransform(PxVec3(pos.x,pos.y,pos.x)), geom, this);
			delete geom[0];
			break;
		case (PowerUpType::SPEED) :
			//add particle system
			
			geom[0] = new PxBoxGeometry(dim.x, dim.y, dim.z);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_SPEED_POWERUP, &PxTransform(PxVec3(getGlobalPose().p)), geom, this);
			PxRigidDynamic* actor = static_cast<PxRigidDynamic*>(&getActor());
			glm::vec3 direction = glm::normalize(getForwardVector());
			direction.y = 0;
			float currentSpeed = getCar().computeForwardSpeed();
			direction *= (getDrivingStyle().getMaxSpeed() - currentSpeed) / getDrivingStyle().getMaxSpeed() * PowerUp::getSpeedImpulse() * 20;
			actor->setAngularVelocity(PxVec3(0, 0, 0));
			actor->addForce(PxVec3(direction.x, direction.y, direction.z), PxForceMode::eIMPULSE);
			delete geom[0];
			break;

		}
		

	}
	

}


void Car::takeDamage(float damage)
{
	m_currentHealth -= damage;
}


void Car::updateReload(float dt)
{
	if (m_reloadRemainingSeconds > 0)
		m_reloadRemainingSeconds -= dt;
}

void Car::updatePowerUp(float dt)
{
	if (m_powerUpRemaining > 0)
	{
		if ((m_powerUpRemaining -= dt) <= 0)
		{
			m_activePowerUp = PowerUpType::NONE;
			
		}
		else {
			if (m_activePowerUp == PowerUpType::SPEED)
			{
				std::cout << "Speed: " << getCar().computeForwardSpeed() << std::endl;
			}
		}
	}
}

void Car::updateSuper(float dt)
{
	if (m_superDurationRemainingSeconds > 0)
	{
		m_superDurationRemainingSeconds -= dt;
		if (ui != NULL)
		{
			ui->gaugeBar->setSuperDurationRemaining(m_superDurationRemainingSeconds);
		}
		if (m_superDurationRemainingSeconds <= 0)
		{
			unuseSuper();
		}

	}
}

#define CAR_DEATH_DELAY .75
#define CAR_LAUNCH_SPEED 100000
#define CAR_SPIN 45, 0, 45
void Car::updateHealth(float dtMillis)
{

	if (m_currentHealth <= 0)	
	{
		if (m_deathTimerMillis > 0)
		{
			m_deathTimerMillis -= dtMillis;
			if (m_deathTimerMillis < 0)
				respawn();
		}
		else {
			m_deathTimerMillis = CAR_DEATH_DELAY;
			getCar().getRigidDynamicActor()->setAngularVelocity(PxVec3(CAR_SPIN));
			getCar().getRigidDynamicActor()->addForce(PxVec3(0, CAR_LAUNCH_SPEED, 0), PxForceMode::eIMPULSE);
			PxGeometry **explosionGeom = new PxGeometry*[1];
			explosionGeom[0] = new PxSphereGeometry(7);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_EXPLOSION_1, &getCar().getRigidDynamicActor()->getGlobalPose(), explosionGeom, NULL);
			delete explosionGeom[0];
			delete[] explosionGeom;
		}
		m_superDurationRemainingSeconds = 0.1;
	}
	
}

void Car::update(float dt) {
	float angle;
	PxVec3 axis;
	m_car.getRigidDynamicActor()->getGlobalPose().q.toRadiansAndUnitAxis(angle, axis);
	//std::cout << angle << "  :  " << axis.x << "," << axis.y << "," << axis.z << std::endl;
	if (abs(axis.y) != 0)
		m_car.getRigidDynamicActor()->setGlobalPose(PxTransform(m_car.getRigidDynamicActor()->getGlobalPose().p, PxQuat(angle, PxVec3(0, abs(axis.y) / axis.y, 0))));
	PxVec3 angVel = m_car.getRigidDynamicActor()->getAngularVelocity();
	m_car.getRigidDynamicActor()->setAngularVelocity(PxVec3(0, angVel.y, 0), true);
	
	
	updateHealth(dt);
	m_reloadRemainingSeconds -= dt;
	updateSuper(dt);
	updatePowerUp(dt);
	if (ui != NULL) {
		ui->healthBar->setHealthPercentage(m_currentHealth / m_maxHealth);
		ui->gaugeBar->setGaugePercentage(getSuperGauge());

		{
	std::stringstream s;
			s << "Lap: " << getLap();
			ui->lap->setString(s.str());
		}
		ui->update(dt);
	}
}

void Car::addDamageDealt(float damage) {
	m_damageDealt += damage;
	m_score += damage;
	
	if (m_activePowerUp == PowerUpType::ATTACK)
	{

		m_currentHealth += PowerUp::getLifeStealPercentage() * damage;
		if (m_currentHealth > m_maxHealth) m_currentHealth = m_maxHealth;
	}
	
	if (m_superDurationRemainingSeconds <= 0) {
		m_superGauge += damage / 100;
	}
}


bool Car::setCurrentWaypoint(Waypoint* waypoint)
{
	//std::cout << "current waypoint is " << waypoint->getIndex() << "\n";
	if (waypoint != m_currentWaypoint) {
		m_lastWayPoint = m_currentWaypoint;
	m_currentWaypoint = waypoint;
		return true;
	}
	else {
		return false;
	}
}
Waypoint* Car::getLastWaypoint()
{
	return m_lastWayPoint;
}

Waypoint* Car::getCurrentWaypoint()
{
	//if (m_currentWaypoint!=NULL)
	return m_currentWaypoint;
}


void Car::incrementLap() {
	m_currentLap++;
}

int Car::getLap() {
	return m_currentLap;
}

int Car::getPositionInRace()
{
	return m_positionInRace;
}

void Car::setPositionInRace(int position)
{
	m_positionInRace = position;
}

void Car::setSoundChassis(Sound theSound)
{
	soundChassis = theSound;
}

void Car::playSoundChassis()
{

	m_audioable->getAudioHandle().queAudioSource(&this->getActor(), soundChassis);
}

void Car::setStartingCollisionVolumeFlag(bool isHit)
{
	m_isAtStartingCollisionVolume = isHit;
	if (m_isAtStartingCollisionVolume && !m_newLap)
	{
		incrementLap();
		m_newLap = true;
	}
		
	
		
}
void Car::setMidCollisionVolumeFlag(bool isHit)
{
	m_isAtMidCollisionVolume = isHit;
	if (m_isAtMidCollisionVolume)
	{
		m_newLap = false;
	}
	
	
}

bool Car::isAtStartingCollisionVolume()
{
	return m_isAtStartingCollisionVolume;
}
bool Car::isAtMidCollisionVolume()
{
	return m_isAtMidCollisionVolume;
}

void Car::addWaypointHit(Waypoint* waypoint)
{
	m_waypointHitList.push_back(waypoint);
}

void Car::setLastHitCollisionVolume(CollisionVolume* collisionVolume)
{
	m_lastCollisionVolume = collisionVolume;
}

CollisionVolume* Car::getLastHitCollisionVolume()
{
	return m_lastCollisionVolume;
}