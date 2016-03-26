#include "MeowMixBullet.h"
#include "Factory\GameFactory.h"


MeowMixBullet::MeowMixBullet(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable,  Car *owner) : Bullet(id, aable, pable, anable, rable, owner)
{
	m_damage = 20;
}


MeowMixBullet::~MeowMixBullet()
{
	
}
