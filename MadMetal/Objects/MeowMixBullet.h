#pragma once

#include "Bullet.h"

class MeowMixBullet : public Bullet
{
public:
	MeowMixBullet(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Car *owner);
	~MeowMixBullet();
};

