#include "Bullet.h"


Bullet::Bullet(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car *owner) : Object3D(id, aable, pable, anable, rable, NULL), m_owner(owner)
{
	maxLifeTime = 4;
	m_collisionSound = BulletCarCollisionSound();
}


Bullet::~Bullet()
{
}

void Bullet::playCollisionSound() {
	m_audioable->getAudioHandle().queAudioSource(&this->getActor(), m_collisionSound);
}