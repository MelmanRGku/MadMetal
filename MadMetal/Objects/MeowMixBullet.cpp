#include "MeowMixBullet.h"


MeowMixBullet::MeowMixBullet(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable,  Car *owner) : Bullet(id, aable, pable, anable, rable, owner)
{
	m_damage = 5;
}


MeowMixBullet::~MeowMixBullet()
{
}
