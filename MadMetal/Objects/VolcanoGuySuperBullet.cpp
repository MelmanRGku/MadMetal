#include "VolcanoGuySuperBullet.h"


VolcanoGuySuperBullet::VolcanoGuySuperBullet(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio, Car *owner) : Bullet(id, aable, pable, anable, rable, audio, owner)
{
	m_damage = 100;
}


VolcanoGuySuperBullet::~VolcanoGuySuperBullet()
{
}
