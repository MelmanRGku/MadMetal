#include "Gargantulous.h"
#include "Factory\GameFactory.h"

Gargantulous::Gargantulous(long id, DrivingStyle* style, PxVehicleDrive4W &car, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Car(id, style, car, aable, pable, anable, rable)
{
	
	m_reloadRateSeconds = .8;						//in s
	
	m_currentHealth = m_maxHealth = 100;


	m_superMaxDurationSeconds = 5;
	m_superDurationRemainingSeconds = 0;


}


Gargantulous::~Gargantulous()
{
}

void Gargantulous::fire()
{
	if (m_reloadRemainingSeconds > 0)
		return;




	PxTransform *pos;
	if (m_superDurationRemainingSeconds > 0)
	{


	}
	else {
		
		m_reloadRemainingSeconds = m_reloadRateSeconds;
		PxVec3 spawnPosition = m_car.getRigidDynamicActor()->getGlobalPose().p;
		spawnPosition.y += m_car.getRigidDynamicActor()->getWorldBounds().getDimensions().y / 2;
		GameFactory::instance()->makeObject(GameFactory::OBJECT_GARGANTULOUS_BULLET, &PxTransform(spawnPosition), NULL, this);
		
	}


}

void Gargantulous::update(float dt) {
	Car::update(dt);

}

void Gargantulous::useSuper() {
	Car::useSuper();
	m_reloadRemainingSeconds = 0;
	m_superGauge = 0;
	//m_renderable->setModel(Assets::getModel("Gargantulous"));
	PxGeometry * geom[1];
	geom[0] = new PxSphereGeometry(50);
	GameFactory::instance()->makeObject(GameFactory::OBJECT_GARGANTULOUS_SUPER_VOLUME, &m_car.getRigidDynamicActor()->getGlobalPose(), geom, this);
}

void Gargantulous::unuseSuper() {
	//m_renderable->setModel(Assets::getModel("Gargantulous"));
	//static_cast<Renderable3D *>(m_renderable)->adjustModel(true, true);
	//m_animatable->updateScale(glm::vec3(0, -2, 0));
}