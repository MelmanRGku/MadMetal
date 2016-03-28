#pragma once

#include "Bullet.h"

class GargantulousBullet : public Bullet
{
public:
	GargantulousBullet(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car *owner) : Bullet(id, aable, pable, anable, rable, owner)
	{
		m_damage = 25;
	}
	~GargantulousBullet()
	{

	}
	virtual void update(float dt) { Bullet::update(dt); }
};

