#pragma once

#include "Bullet.h"

class ExplosivelyDeliciousBullet : public Bullet
{
public:
	ExplosivelyDeliciousBullet(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car *owner) : Bullet(id, aable, pable, anable, rable, owner)
	{
		m_damage = 35;
	}

	virtual ~ExplosivelyDeliciousBullet()
	{

	}
	virtual void update(float dt) { Bullet::update(dt); }
};

