#include "ExplosivelyDelicious.h"
#include "Factory\GameFactory.h"


ExplosivelyDelicious::ExplosivelyDelicious(long id, DrivingStyle* style, PxVehicleDrive4W &car, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Car(id, style, car, aable, pable, anable, rable)
{
	m_reloadRateSeconds = 1.5;						//in s
	m_currentHealth = m_maxHealth = 120;


	m_superMaxDurationSeconds = 5;
	m_superDurationRemainingSeconds = 0;


}


ExplosivelyDelicious::~ExplosivelyDelicious()
{
}

void ExplosivelyDelicious::fire()
{
	if (m_reloadRemainingSeconds > 0)
		return;




	PxTransform *pos;

	glm::vec4 up = glm::normalize(getModelMatrix() * glm::vec4(0, 1, 0, 0));
	glm::vec4 forward = glm::normalize(getModelMatrix() * glm::vec4(0, 0, 1, 0));
	glm::vec4 weaponPos = glm::vec4(getFullPosition(), 1.0) + up * (getScale().y / 2) + forward * (getScale().z / 2);
	pos = new PxTransform(weaponPos.x, weaponPos.y, weaponPos.z);
	GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET_EXPLOSIVELY_DELICIOUS, pos, NULL, this);
	delete pos;
	m_reloadRemainingSeconds = m_reloadRateSeconds;

		
	


}

#define LAUNCH_ANGLE 0,0,0
#define CAR_LAUNCH_SPEED 40000
#define BOMB_THROW_INTERVAL .5f
void ExplosivelyDelicious::update(float dt) {
	Car::update(dt);
	if (m_numOfBombs)
	{
		m_explosionTimer += dt;
		if (m_explosionTimer > BOMB_THROW_INTERVAL)
		{
			m_explosionTimer = 0;
			m_numOfBombs--;
			PxTransform *pos;

			glm::vec4 up = glm::normalize(getModelMatrix() * glm::vec4(0, 1, 0, 0));
			glm::vec4 forward = glm::normalize(getModelMatrix() * glm::vec4(0, 0, 1, 0));
			glm::vec4 weaponPos = glm::vec4(getFullPosition(), 1.0) + up * (getScale().y / 2) + forward * (getScale().z / 2);
			pos = new PxTransform(weaponPos.x, weaponPos.y, weaponPos.z);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET_EXPLOSIVELY_DELICIOUS_RANDOM_DIRECTION, pos, NULL, this);
			delete pos;
		}

		//last bomb sent out - explode
		if (m_numOfBombs == 0) {
			//m_currentHealth = 1;
			PxGeometry* geom[1];
			geom[0] = new PxBoxGeometry(PxVec3(20, 15, 20));
			PxTransform * pos = &m_car.getRigidDynamicActor()->getGlobalPose();
			GameFactory::instance()->makeObject(GameFactory::OBJECT_EXPLOSIVELY_DELICIOUS_SUPER, &PxTransform(pos->p), geom, this);
			delete geom[0];

			//getCar().getRigidDynamicActor()->addForce(PxVec3(0, CAR_LAUNCH_SPEED, 0), PxForceMode::eIMPULSE);
			//getCar().getRigidDynamicActor()->setAngularVelocity(PxVec3(LAUNCH_ANGLE));
		}
	}
	
}

void ExplosivelyDelicious::unuseSuper()
{

}
void ExplosivelyDelicious::useSuper() {
	Car::useSuper();
	m_numOfBombs = (int)(m_superMaxDurationSeconds / BOMB_THROW_INTERVAL);
}

