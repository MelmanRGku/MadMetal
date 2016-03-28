#pragma once

#include "Car.h"



class MeowMix : public Car
{
protected:
	void unuseSuper();
	Renderable *rableWheel;

public:
	MeowMix(long id, DrivingStyle* style, PxVehicleDrive4W &car, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Renderable3D *rableWheel);
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	~MeowMix();

	void fire();
	void update(float dt);
	void useSuper();
private:
	
	enum LastWeaponShot {
		LAST_WEAPON_SHOT_LEFT,
		LAST_WEAPON_SHOT_RIGHT
	} m_lastWeaponShot;
};

