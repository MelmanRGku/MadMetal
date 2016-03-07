#pragma once

#include "TestObject.h"

class BulletCarCollision : public TestObject
{
public:
	BulletCarCollision(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable);
	~BulletCarCollision();
};