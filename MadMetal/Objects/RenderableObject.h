#pragma once

#include "Model.h"
#include "Object.h"
#include "Renderer\Renderer.h"
class Renderer;

class RenderableObject : public Object{
public:
	Model *model;

	RenderableObject();
	~RenderableObject();
	virtual void draw(Renderer *renderer);
};