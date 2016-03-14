#pragma once

#include "Object2D.h"

class TexturedObject2D : public Object2D
{
public:
	TexturedObject2D(long id, Audioable *aable, Animatable *anable, Renderable2D *rable);
	virtual ~TexturedObject2D();
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
};

