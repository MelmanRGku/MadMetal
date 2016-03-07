#include "MeowMix.h"
#include "Factory\GameFactory.h"

MeowMix::MeowMix(long id, DrivingStyle& style, PxVehicleDrive4W &car, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable) : Car(id, style, car, aable, pable, anable, rable)
{
	m_lastWeaponShot = LAST_WEAPON_SHOT_LEFT;
	m_reloadRateSeconds = 0.15;						//in s
	m_superReloadRateSeconds = 1;
	m_currentHealth = m_maxHealth = 2000;
	m_currentHealth -= 500;

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
	

	

	if (m_superDurationRemainingSeconds > 0)
	{
		m_reloadRemainingSeconds = m_superReloadRateSeconds;
		GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET_SUPER_VOLCANO, NULL, NULL, this);

	}
	else {
		m_reloadRemainingSeconds = m_reloadRateSeconds;
		GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET_MEOW_MIX, new PxTransform(getFullPosition().x, getFullPosition().y, getFullPosition().z), NULL, this);
	}
	

}

void MeowMix::update(float dt) {
	Car::update(dt);
	
}

void MeowMix::useSuper() {
	m_superDurationRemainingSeconds = m_superMaxDurationSeconds;
	m_reloadRemainingSeconds = 0;
	m_superGauge = 0;
	
}