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
#define EXPLOSION_INTERVAL .5
void ExplosivelyDelicious::update(float dt) {
	Car::update(dt);
	if (m_numExplosions)
	{
		m_explosionTimer += dt;
		if (m_explosionTimer > EXPLOSION_INTERVAL)
		{
			m_explosionTimer = 0;
			m_numExplosions--;
			PxGeometry **explosionGeom = new PxGeometry*[1];
			explosionGeom[0] = new PxSphereGeometry(7);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_EXPLOSION_1, &getCar().getRigidDynamicActor()->getGlobalPose(), explosionGeom, this);
			delete explosionGeom[0];
		}
	}
	
}

void ExplosivelyDelicious::unuseSuper()
{

}
#define LAUNCH_ANGLE 0,0,0
#define CAR_LAUNCH_SPEED 40000
void ExplosivelyDelicious::useSuper() {
	m_superDurationRemainingSeconds = m_superMaxDurationSeconds;
	m_superGauge = 0;
	m_currentHealth = 1;
	m_numExplosions = 3;
	PxGeometry* geom[1];
	geom[0] = new PxBoxGeometry(PxVec3(20, 15, 20));
	PxTransform * pos = &m_car.getRigidDynamicActor()->getGlobalPose();
	//pos->p.y += 10;
	GameFactory::instance()->makeObject(GameFactory::OBJECT_EXPLOSIVELY_DELICIOUS_SUPER, pos, geom, this);
	delete geom[0];

	getCar().getRigidDynamicActor()->addForce(PxVec3(0, CAR_LAUNCH_SPEED, 0), PxForceMode::eIMPULSE);
	getCar().getRigidDynamicActor()->setAngularVelocity(PxVec3(LAUNCH_ANGLE));
	

	
	//m_renderable->setModel(Assets::getModel("UglyCarWithCannon"));
	//static_cast<Renderable3D *>(m_renderable)->adjustModel(true, true);
	//m_animatable->updateScale(glm::vec3(0, 2, 0));
}

