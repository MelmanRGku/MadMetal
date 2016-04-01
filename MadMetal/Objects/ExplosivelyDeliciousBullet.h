#pragma once

#include "Bullet.h"

class ExplosivelyDeliciousBullet : public Bullet
{
private:

public:
	ExplosivelyDeliciousBullet(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car *owner);

	virtual ~ExplosivelyDeliciousBullet();

	virtual void update(float dt);
	void spawnExplosion();
};

