#include "VolcanoGuySuperBullet.h"


VolcanoGuySuperBullet::VolcanoGuySuperBullet(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Car *owner) : Bullet(id, aable, pable, anable, rable, owner)
{
	m_damage = 100;
}


VolcanoGuySuperBullet::~VolcanoGuySuperBullet()
{
}
