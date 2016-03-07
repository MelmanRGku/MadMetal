#include "Car.h"
#include "../DrivingStyleFast.h"
#include "Factory\GameFactory.h"
#include <sstream>
#include "Objects\Waypoint.h"

Car::Car(long id, DrivingStyle& style, PxVehicleDrive4W &car, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable) : TestObject(id, aable, pable, anable, rable), m_car(car), m_drivingStyle(style)
{
	m_currentWaypoint = NULL;
}


Car::~Car()
{
}

DrivingStyle& Car::getDrivingStyle()
{
	return m_drivingStyle;
}

void Car::respawn()
{
	std::cout << "Respawned? \n";
	m_currentHealth = m_maxHealth;
	
	if (m_currentWaypoint != NULL)
	{
		std::cout << "Valid Waypoint Respawn" << std::endl;
		glm::vec3 waypointPos = m_currentWaypoint->getGlobalPose();
		
		
		m_car.getRigidDynamicActor()->setGlobalPose(PxTransform(PxVec3(waypointPos.x, waypointPos.y, waypointPos.z)));
		
	}
	else {
		std::cout << "Invalid Waypoint Respawn" << std::endl;
		PxTransform currentPosition = m_car.getRigidDynamicActor()->getGlobalPose();
		m_car.getRigidDynamicActor()->setGlobalPose(PxTransform(PxVec3(currentPosition.p.x, currentPosition.p.y+10, currentPosition.p.z)));
	}
	m_car.getRigidDynamicActor()->setLinearVelocity(PxVec3(0, 0, 0));
	m_car.getRigidDynamicActor()->setAngularVelocity(PxVec3(0, 0, 0));
	
	
}

/*
void Car::usePowerUp()
{
	//if not holding a power up do nothing
	if (m_heldPowerUp.getType() == NONE)
		return;

	//set active power up to power up being held. Set held power up to NONE
	m_activePowerUp.setPowerUp(m_heldPowerUp.getType());
	m_heldPowerUp.setPowerUp(NONE);
	//start duration of power up to specific power up time
	m_powerUpDurationRemaining = m_activePowerUp.getPowerUpDuration();

}

void Controllable::pickUpPowerUp(PowerUpType type)
{
	m_heldPowerUp.setPowerUp(type);
}
*/

void Car::takeDamage(float damage)
{
	//car set to dead will be dealt with in the update function
	m_currentHealth -= damage;
}

void Car::increaseDamageDealt(float damage)
{
	m_damageDealt += damage;
}

void Car::updateReload(float dt)
{
	if (m_reloadRemainingSeconds > 0)
		m_reloadRemainingSeconds -= dt;
}

void Car::updatePowerUp(float dt)
{
	/*if (m_powerUpDurationRemaining > 0)
	{

		if ((m_powerUpDurationRemaining -= dt) <= 0)
		{
			m_activePowerUp.setPowerUp(NONE);
		}
	}*/
}

void Car::updateSuper(float dt)
{
	if (m_superDurationRemainingSeconds > 0)
	{
		if ((m_superDurationRemainingSeconds -= dt) <= 0)
		{
			//m_currentModel = &m_normalModel;
		}

	}
}

void Car::update(float dt) {
	m_reloadRemainingSeconds -= dt;
	if (m_superDurationRemainingSeconds > 0) m_superDurationRemainingSeconds -= dt;
	if (ui != NULL) {
		ui->healthBar->setHealthPercentage(m_currentHealth / m_maxHealth);
		ui->gaugeBar->setGaugePercentage(getSuperGauge());

		{
			std::stringstream s;
			s << "Score: " << getScore();
			ui->score->setString(s.str());
		}

		{
			std::stringstream s;
			s << "Lap: " << getLap();
			ui->lap->setString(s.str());
		}
	}

	if (m_currentHealth < 0) {
		hasToBeDeleted = true;
	}
}

void Car::addDamageDealt(float damage) {
	m_damageDealt += damage;
	if (m_superDurationRemainingSeconds == 0)
		m_superGauge += damage / 100;
}

int Car::getScore() {
	return m_damageDealt;
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