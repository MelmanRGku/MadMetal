#pragma once

#include "Car.h"
#include "../Weapons/HasWeapons.h"

class MeowMix : public Car, public HasWeapons
{
public:
	MeowMix();
	~MeowMix();

	glm::vec3 getNextBulletPos();

	void shoot();

private:
	enum LastWeaponShot {
		LAST_WEAPON_SHOT_LEFT,
		LAST_WEAPON_SHOT_RIGHT
	} m_lastWeaponShot;
};

