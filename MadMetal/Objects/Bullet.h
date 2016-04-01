#pragma once

#include "Objects\Cars\Car.h"

class Bullet : public Object3D
{
protected:
	Car *m_owner;
	int m_damage;
	Sound m_collisionSound;
	Sound m_explosivelyBulletSound;


public:
	bool explosivelyBullet = false;
	Bullet(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car *owner);
	virtual ~Bullet();
	void setOwner(Car *car) { m_owner = car; }
	Car *getOwner() { return m_owner; }
	int getDamage() { return m_damage; }
	void playCollisionSound();
	virtual void update(float dt) { Object3D::update(dt); }
};

