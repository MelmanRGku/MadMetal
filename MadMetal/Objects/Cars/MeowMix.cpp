#include "MeowMix.h"


MeowMix::MeowMix()
{

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

	//do smth else here ?
}

glm::vec3 MeowMix::getNextBulletPos() {
	if (m_lastWeaponShot == LAST_WEAPON_SHOT_LEFT) {
		return m_weapons.at(1)->getFullPosition();		//get the right weapon pos
	}
	else if (m_lastWeaponShot == LAST_WEAPON_SHOT_RIGHT) {
		return m_weapons.at(0)->getFullPosition();		//get the left weapon pos
	}
	else {
		exit(5);										//hopefully will never happen
	}
}