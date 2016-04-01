#include "Bullet.h"


Bullet::Bullet(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car *owner) : Object3D(id, aable, pable, anable, rable, NULL), m_owner(owner)
{
	maxLifeTime = 4;
	m_collisionSound = BulletCarCollisionSound();
	m_explosivelyBulletSound = BoomSound();
}


Bullet::~Bullet()
{
}

void Bullet::playCollisionSound() {
	if (explosivelyBullet) 	m_audioable->getAudioHandle().queAudioSource(&this->getActor(), m_explosivelyBulletSound);
	else m_audioable->getAudioHandle().queAudioSource(&this->getActor(), m_collisionSound);
}