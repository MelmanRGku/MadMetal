#pragma once

#include "Object3D.h"

class Button : public Object3D
{
public:
	Button(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);
	~Button();
};

