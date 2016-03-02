#include "MeowMix.h"
#include "Factory\GameFactory.h"

MeowMix::MeowMix(long id, PxVehicleDrive4W &car, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio) : Car(id, car, aable, pable, anable, rable, audio)
{
	m_lastWeaponShot = LAST_WEAPON_SHOT_LEFT;
}


MeowMix::~MeowMix()
{
}

void MeowMix::shoot() {
	if (m_lastWeaponShot == LAST_WEAPON_SHOT_LEFT) {
		m_lastWeaponShot = LAST_WEAPON_SHOT_RIGHT;
	}
	else if (m_lastWeaponShot == LAST_WEAPON_SHOT_RIGHT) {
		m_lastWeaponShot = LAST_WEAPON_SHOT_LEFT;
	}
	else {
		exit(5);										//hopefully will never happen
	}

	GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET, NULL, NULL, this);
}