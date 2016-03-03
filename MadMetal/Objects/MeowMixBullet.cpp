#include "MeowMixBullet.h"


MeowMixBullet::MeowMixBullet(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio, Car *owner) : Bullet(id, aable, pable, anable, rable, audio, owner)
{
	m_damage = 3;
}


MeowMixBullet::~MeowMixBullet()
{
}
