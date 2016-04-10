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
	m_currentCollisionVolume = NULL;
	
	m_newLap = true;
	m_powerUpRemaining = 0;
	Car::positionGlobalID++;
	m_positionInRace = positionGlobalID;
	
	m_invincibilityTimeRemaining = 0;
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
	//if the car is alive and it respawned recently
	//if (m_timeSinceRespawn <= 3 && m_currentHealth > 0)
	//	return;

	//if player is not alive
	if (m_currentHealth <= 0) {
	m_currentHealth = m_maxHealth;
		m_invincibilityTimeRemaining = 3;
	}
	m_timeSinceRespawn = 0;
	
	if (m_currentCollisionVolume != NULL)
	{
		m_car.getRigidDynamicActor()->setGlobalPose(m_currentCollisionVolume->getRespawnLocation());
		
	}
	else {
		
		m_car.getRigidDynamicActor()->setGlobalPose(PxTransform(PxVec3(0, 5, 0)));
	}

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

PowerUpType Car::getHeldPowerUp() {
	return m_heldPowerUp;
}

void Car::pickUpPowerUp(PowerUpType type)
{
	if (m_heldPowerUp == PowerUpType::NONE)
	{
		m_heldPowerUp = type;
		if (ui != NULL)
		{
			ui->setPowerup(type);
		}
		m_audioable->getAudioHandle().queAudioSource(&getActor(), PowerupPickupSound());
	}
	
}

void Car::usePowerUp()
{
	if (m_heldPowerUp != PowerUpType::NONE && m_activePowerUp == PowerUpType::NONE)
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
			m_audioable->getAudioHandle().queAudioSource(&getActor(), RegenSound());
			break;
		case (PowerUpType::DEFENSE) :
			
			geom[0] = new PxBoxGeometry(dim.x, dim.y / 2, dim.z);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_SHIELD_POWERUP, &PxTransform(PxVec3(pos.x,pos.y,pos.x)), geom, this);
			delete geom[0];
			m_audioable->getAudioHandle().queAudioSource(&getActor(), ShieldPowerupSound());
			break;
		case (PowerUpType::SPEED) :
			//add particle system
			
			geom[0] = new PxBoxGeometry(dim.x, dim.y / 2, dim.z);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_SPEED_POWERUP, &PxTransform(PxVec3(getGlobalPose().p)), geom, this);
			PxRigidDynamic* actor = static_cast<PxRigidDynamic*>(&getActor());
			glm::vec3 direction = glm::normalize(getForwardVector());
			direction.y = 0;
			float currentSpeed = getCar().computeForwardSpeed();
#undef max
			direction *= std::max(getDrivingStyle().getMaxSpeed() - currentSpeed, 30.f) / getDrivingStyle().getMaxSpeed() * PowerUp::getSpeedImpulse() * 20;
			actor->setAngularVelocity(PxVec3(0, 0, 0));
			actor->addForce(PxVec3(direction.x, direction.y, direction.z), PxForceMode::eIMPULSE);
			delete geom[0];
			m_audioable->getAudioHandle().queAudioSource(&getActor(), CarAccelerationSound());
			break;

		}
		

	}
	

}

bool Car::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	if (m_invincibilityTimeRemaining <= 0 || std::fmod(m_invincibilityTimeRemaining, (INVINICIBILITY_FLASH_PERIOD * 2)) < INVINICIBILITY_FLASH_PERIOD) {
		return Object3D::draw(renderer, type, passNumber);
	}
	else return false;
}

bool Car::takeDamage(float damage, bool applyAnyway)
{
	if (m_invincibilityTimeRemaining <= 0 || applyAnyway) {
	m_currentHealth -= damage;
	if (m_currentHealth > m_maxHealth)
		m_currentHealth = m_maxHealth;
		m_timeSinceLastTimeHit = 0;
		return true;
	}

	return false;
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
				//std::cout << "Speed: " << getCar().computeForwardSpeed() << std::endl;
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
			m_audioable->getAudioHandle().queAudioSource(getCar().getRigidDynamicActor(), CarExplodeSound(), 2);
		}
		m_superDurationRemainingSeconds = 0.1;
	}
	
}

void Car::updateOrientation(float dt)
{


	
	float angle;
	PxVec3 axis;
	m_car.getRigidDynamicActor()->getGlobalPose().q.toRadiansAndUnitAxis(angle, axis);
	//m_car.getRigidDynamicActor()->setAngularDamping(5);
	//m_car.getRigidDynamicActor()->setGlobalPose(PxTransform(m_car.getRigidDynamicActor()->getGlobalPose().p, PxQuat(0, axis)));
	if (axis.y != 0)
		m_car.getRigidDynamicActor()->setGlobalPose(PxTransform(m_car.getRigidDynamicActor()->getGlobalPose().p, PxQuat(angle, PxVec3(0, abs(axis.y) / axis.y, 0))));
	PxVec3 angVel = m_car.getRigidDynamicActor()->getAngularVelocity();
	if (m_isInAir)
		m_car.getRigidDynamicActor()->setAngularVelocity(PxVec3(0, 0, 0), true);
	else
	m_car.getRigidDynamicActor()->setAngularVelocity(PxVec3(0, angVel.y, 0), true);
	
	
	m_shadow->getActor().setGlobalPose(PxTransform(getActor().getGlobalPose().p + PxVec3(0, lastKnownDistanceBetweenCarAndShadow, 0), getActor().getGlobalPose().q));
	
	PxVec3 extraOffset = PxVec3(0, 0, 0);
	bool groundFound = false;
	PxRaycastBuffer hit;
	PxQueryFilterData fd = PxQueryFilterData(PxQueryFlag::eSTATIC);
	do {
		GameFactory::instance()->sceneRayCast(m_car.getRigidDynamicActor()->getGlobalPose().p + extraOffset, PxVec3(0, -1, 0), 500, hit, PxHitFlag::eDEFAULT, fd);
	if (hit.hasBlock)
	{
			PxShape * shapes[1];
			hit.block.actor->getShapes(shapes, 1);
			if (shapes[0]->getSimulationFilterData().word0 == COLLISION_FLAG_GROUND)
			{
				lastKnownDistanceBetweenCarAndShadow = extraOffset.y - hit.block.distance + 1.f;
				groundFound = true;
			}
			else {
				extraOffset += PxVec3(0, -hit.block.distance - 0.1f, 0);
			}
		}
		else {
			if (extraOffset.y != 0)
				lastKnownDistanceBetweenCarAndShadow = extraOffset.y;
			groundFound = true;
	}
	} while (!groundFound);
	
}

void Car::update(float dt) {
	
	m_invincibilityTimeRemaining -= dt;
	updateHealth(dt);
	if (m_currentHealth > 0)
		updateOrientation(dt);
	m_reloadRemainingSeconds -= dt;
	m_timeSinceLastTimeHit += dt;
	m_timeSinceRespawn += dt;
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

void Car::addDamageDealt(float damage, bool addToSuper) {
	m_damageDealt += damage;
	m_score += damage;
	
	if (m_activePowerUp == PowerUpType::ATTACK)
	{

		m_currentHealth += PowerUp::getLifeStealPercentage() * damage;
		if (m_currentHealth > m_maxHealth) m_currentHealth = m_maxHealth;
	}
	
	if (m_superDurationRemainingSeconds <= 0 && addToSuper) {
		m_superGauge += damage / 100;
	}
}


void Car::setCurrentCollisionVolume(CollisionVolume* toSet)
{
	//if (m_currentCollisionVolume != NULL) {
	//	if (toSet == m_currentCollisionVolume->getNextCollisionVolume())
	//	{
	//		m_currentCollisionVolume = toSet;
	//	}
	//}
	//else {
		m_currentCollisionVolume = toSet;
	//}
}

CollisionVolume * Car::getCurrentCollisionVolume()
{
	return m_currentCollisionVolume;
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


bool Car::isInvincible() {
	return m_invincibilityTimeRemaining > 0;
}

float Car::getInvinsibilityTimeRemaining() {
	return m_invincibilityTimeRemaining;
}

void Car::setInvincibility(float time) {
	m_invincibilityTimeRemaining = time;
}

float Car::getTimeSinceLastTimeHit() {
	return m_timeSinceLastTimeHit;
}

void Car::setShadow(Object3D *shadow) {
	m_shadow = shadow;
}