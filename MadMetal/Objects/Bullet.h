#pragma once

#include "Objects\Cars\Car.h"

class Bullet : public TestObject
{
private:
	Car *m_owner;

public:
	Bullet(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio, Car *owner);
	~Bullet();
	void setOwner(Car *car) { m_owner = car; }
	Car *getOwner() { return m_owner; }
};

