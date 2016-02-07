#pragma once

#include "Model.h"
#include "Object.h"
#include "Renderer\Renderer.h"
#include "Renderer\Renderable.h"
class Renderer;

class RenderableObject : public Object, public Renderable{
public:
	RenderableObject();
	~RenderableObject();

	virtual void draw(Renderer *renderer);
};