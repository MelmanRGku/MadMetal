#pragma once

#include "Object3D.h"

class SinglePlayerButton : public Object3D
{
public:
	SinglePlayerButton(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);
	~SinglePlayerButton();
};

