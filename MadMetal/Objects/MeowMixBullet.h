#pragma once

#include "Bullet.h"

class MeowMixBullet : public Bullet
{
public:
	MeowMixBullet(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car *owner);
	~MeowMixBullet();
	virtual void update(float dt) { Bullet::update(dt); }
};

