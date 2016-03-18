#include "Car.h"
#include "../DrivingStyleFast.h"
#include "Factory\GameFactory.h"
#include <sstream>
#include "Objects\Waypoint.h"

Car::Car(long id, DrivingStyle* style, PxVehicleDrive4W &car, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable), m_car(car), m_drivingStyle(style)
{
	m_currentWaypoint = NULL;
	m_isAtMidCollisionVolume = false;
	m_isAtStartingCollisionVolume = false;
	m_newLap = true;
	m_powerUpRemaining = 0;
}


Car::~Car()
{
	//TODO: revive later ?
	//delete ui;
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
	
	if (m_currentWaypoint != NULL)
	{
		//std::cout << "Valid Waypoint Respawn" << std::endl;
		glm::vec3 waypointPos = m_currentWaypoint->getGlobalPose();
		
		
		m_car.getRigidDynamicActor()->setGlobalPose(PxTransform(PxVec3(waypointPos.x, waypointPos.y, waypointPos.z)));
		
	}
	else {
		//std::cout << "Invalid Waypoint Respawn" << std::endl;
		PxTransform currentPosition = m_car.getRigidDynamicActor()->getGlobalPose();
		m_car.getRigidDynamicActor()->setGlobalPose(PxTransform(PxVec3(currentPosition.p.x, currentPosition.p.y+10, currentPosition.p.z)));
	}
	m_car.getRigidDynamicActor()->setLinearVelocity(PxVec3(0, 0, 0));
	m_car.getRigidDynamicActor()->setAngularVelocity(PxVec3(0, 0, 0));
	
	
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
	}
	
}

void Car::usePowerUp()
{
	//if (m_heldPowerUp != PowerUpType::NONE)
	//{
		
		//m_activePowerUp = m_heldPowerUp;
		m_activePowerUp = PowerUpType::SPEED; //remove
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
			break;
		case (PowerUpType::DEFENSE) :
			
			geom[0] = new PxBoxGeometry(dim.x, dim.y, dim.z);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_SHIELD_POWERUP, &PxTransform(PxVec3(pos.x,pos.y,pos.x)), geom, this);
			
			break;
		case (PowerUpType::SPEED) :
			//add particle system
			geom[0] = new PxSphereGeometry(dim.x > dim.z ? dim.z : dim.x);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_SPEED_POWERUP, &PxTransform(PxVec3(getGlobalPose().p)), geom, this);
			PxRigidDynamic* actor = static_cast<PxRigidDynamic*>(&getActor());
			glm::vec3 direction = glm::normalize(getForwardVector());
			direction.y = 0;
			float currentSpeed = getCar().computeForwardSpeed();

			direction *= (getDrivingStyle().getMaxSpeed() - currentSpeed) / getDrivingStyle().getMaxSpeed() * PowerUp::getSpeedImpulse() * 20;
			actor->setAngularVelocity(PxVec3(0, 0, 0));
			actor->addForce(PxVec3(direction.x, direction.y, direction.z), PxForceMode::eIMPULSE);
			break;

		}
		delete geom[0];

	//}
	

}


void Car::takeDamage(float damage)
{
	//car set to dead will be dealt with in the update function
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
		if ((m_superDurationRemainingSeconds -= dt) <= 0)
		{
			unuseSuper();
		}

	}
}

void Car::update(float dt) {
	//std::cout << m_currentLap << std::endl;
	m_reloadRemainingSeconds -= dt;
	updateSuper(dt);
	updatePowerUp(dt);
	if (ui != NULL) {
		ui->healthBar->setHealthPercentage(m_currentHealth / m_maxHealth);
		ui->gaugeBar->setGaugePercentage(getSuperGauge());

		{
	std::stringstream s;
	s << "Score: " << tallyScore();
			ui->score->setString(s.str());
		}

		{
			std::stringstream s;
			s << "Lap: " << getLap();
			ui->lap->setString(s.str());
		}
	}
}

void Car::addDamageDealt(float damage) {
	m_damageDealt += damage;
	
	if (m_activePowerUp == PowerUpType::ATTACK)
	{

		m_currentHealth += PowerUp::getLifeStealPercentage() * damage;
	}
	
	if (m_superDurationRemainingSeconds <= 0) {
		m_superGauge += damage / 100;
	}
}


bool Car::setCurrentWaypoint(Waypoint* waypoint)
{
	//std::cout << "current waypoint is " << waypoint->getId() << "\n";
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