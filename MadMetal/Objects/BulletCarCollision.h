#pragma once

#include "Object3D.h"

class BulletCarCollision : public Object3D
{
public:
	BulletCarCollision(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);
	~BulletCarCollision();
};