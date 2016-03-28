#pragma once
#include "Car.h"



class ExplosivelyDelicious : public Car
{
protected:
	void unuseSuper();
public:
	ExplosivelyDelicious(long id, DrivingStyle* style, PxVehicleDrive4W &car, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);

	~ExplosivelyDelicious();

	void fire();
	void update(float dt);
	void useSuper();
	
private:
	float m_explosionTimer;
	int m_numExplosions;
	
};

