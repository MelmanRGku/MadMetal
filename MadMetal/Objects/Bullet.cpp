#include "Bullet.h"


Bullet::Bullet(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car *owner) : Object3D(id, aable, pable, anable, rable), m_owner(owner)
{
	maxLifeTime = -1;
}


Bullet::~Bullet()
{
}
