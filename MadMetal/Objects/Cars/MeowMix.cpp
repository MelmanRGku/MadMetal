#include "MeowMix.h"
#include "Factory\GameFactory.h"


MeowMix::MeowMix(long id, DrivingStyle* style, PxVehicleDrive4W &car, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Car(id, style, car, aable, pable, anable, rable)
{
	m_lastWeaponShot = LAST_WEAPON_SHOT_LEFT;
	m_reloadRateSeconds = 0.15;						//in s
	m_superReloadRateSeconds = 0;
	m_currentHealth = m_maxHealth = 100;
	
	m_superMaxDurationSeconds = 5;
	m_superDurationRemainingSeconds = 0;

	
}


MeowMix::~MeowMix()
{
}

void MeowMix::fire()
{
	if (m_reloadRemainingSeconds > 0)
		return;
	
	PxTransform * pos;
	
	if (m_superDurationRemainingSeconds > 0)
	{
		//beam is firing right now
	}
	else {
		m_reloadRemainingSeconds = m_reloadRateSeconds;
		glm::vec4 up = glm::normalize(getModelMatrix() * glm::vec4(0, 1, 0, 0));
		glm::vec4 left = glm::normalize(getModelMatrix() * glm::vec4(-1, 0, 0, 0));
		if (m_lastWeaponShot == LAST_WEAPON_SHOT_LEFT)
		{
			m_lastWeaponShot = LAST_WEAPON_SHOT_RIGHT;
			glm::vec4 weaponPos = glm::vec4(getFullPosition(), 1.0) + up * (getScale().y / 3) + left * (getScale().x / 2);
			pos = new PxTransform(weaponPos.x, weaponPos.y, weaponPos.z);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET_MEOW_MIX, pos, NULL, this);
			delete pos;
		}
		else
		{
			m_lastWeaponShot = LAST_WEAPON_SHOT_LEFT;
			glm::vec4 weaponPos = glm::vec4(getFullPosition(), 1.0) + up * (getScale().y / 3) - left * (getScale().x / 2);
			pos = new PxTransform(weaponPos.x, weaponPos.y, weaponPos.z);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET_MEOW_MIX, pos, NULL, this);
			delete pos;
		}
	}
	
	
}

void MeowMix::update(float dt) {
	Car::update(dt);
	
}

void MeowMix::useSuper() {
	m_superDurationRemainingSeconds = m_superMaxDurationSeconds;
	m_reloadRemainingSeconds = 0;
	m_superGauge = 0;

	//m_renderable->setModel(Assets::getModel("UglyCarWithGuns"));

	PxGeometry * geom[1];
	/*geom[0] = new PxSphereGeometry(1);
	GameFactory::instance()->makeObject(GameFactory::OBJECT_MEOW_MIX_SUPER, &m_car.getRigidDynamicActor()->getGlobalPose(), geom, this);
	delete geom[0];*/

	geom[0] = new PxSphereGeometry(50);
	GameFactory::instance()->makeObject(GameFactory::OBJECT_GARGANTULOUS_SUPER_VOLUME, &m_car.getRigidDynamicActor()->getGlobalPose(), geom, this);
	delete geom[0];
	
}

void MeowMix::unuseSuper() {
	//m_renderable->setModel(Assets::getModel("UglyCarWithGuns"));
}