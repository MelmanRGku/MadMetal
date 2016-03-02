#pragma once

#include "Car.h"

class MeowMix : public Car
{
public:
	MeowMix(long id, PxVehicleDrive4W &car, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio);
	~MeowMix();

	void fire();
	void update(float dt);
private:
	enum LastWeaponShot {
		LAST_WEAPON_SHOT_LEFT,
		LAST_WEAPON_SHOT_RIGHT
	} m_lastWeaponShot;
};

