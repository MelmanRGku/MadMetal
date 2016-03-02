#include "MeowMix.h"
#include "Factory\GameFactory.h"

MeowMix::MeowMix(long id, PxVehicleDrive4W &car, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio) : Car(id, car, aable, pable, anable, rable, audio)
{
	m_lastWeaponShot = LAST_WEAPON_SHOT_LEFT;
	m_reloadRate = 0.15;						//in s
}


MeowMix::~MeowMix()
{
}

void MeowMix::fire()
{
	if (m_reloadRemaining > 0)
		return;

	m_reloadRemaining = m_reloadRate;

	GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET, new PxTransform(getFullPosition().x, getFullPosition().y, getFullPosition().z), NULL, this);

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