#include "Bullet.h"


Bullet::Bullet(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio, Car *owner) : TestObject(id, aable, pable, anable, rable, audio), m_owner(owner)
{
	maxLifeTime = -1;
}


Bullet::~Bullet()
{
}
