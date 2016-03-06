#include "MeowMix.h"
#include "Factory\GameFactory.h"

MeowMix::MeowMix(long id, DrivingStyle& style, PxVehicleDrive4W &car, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio) : Car(id, style, car, aable, pable, anable, rable, audio)
{
	m_lastWeaponShot = LAST_WEAPON_SHOT_LEFT;
	m_reloadRateSeconds = 0.15;						//in s
	m_currentHealth = m_maxHealth = 2000;
	m_currentHealth -= 500;
}


MeowMix::~MeowMix()
{
}

void MeowMix::fire()
{
	if (m_reloadRemainingSeconds > 0)
		return;

	m_reloadRemainingSeconds = m_reloadRateSeconds;

	GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET_MEOW_MIX, new PxTransform(getFullPosition().x, getFullPosition().y, getFullPosition().z), NULL, this);

	/*if (m_superDurationRemaining > 0)
	{
	if (m_activePowerUp.getType() == ATTACK)
	{
	//spawn a super projectile with vampiric callback
	}

	else {
	//spawn a super projectile
	}
	}
	else {
	if (m_activePowerUp.getType() == ATTACK)
	{
	//spawn a regular projectile with vampiric callback
	}

	else {
	//spawn a regular projectile
	}
	}
	*/

}

void MeowMix::update(float dt) {
	Car::update(dt);
}

void MeowMix::useSuper() {
	m_superGauge = 0;
	GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET_SUPER_VOLCANO, NULL, NULL, this);
}