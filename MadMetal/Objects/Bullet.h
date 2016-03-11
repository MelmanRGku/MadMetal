#pragma once

#include "Objects\Cars\Car.h"

class Bullet : public TestObject
{
protected:
	Car *m_owner;
	int m_damage;

public:
	Bullet(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable *rable, Car *owner);
	~Bullet();
	void setOwner(Car *car) { m_owner = car; }
	Car *getOwner() { return m_owner; }
	int getDamage() { return m_damage; }

};

