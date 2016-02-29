#pragma once

#include "Model.h"
#include "Object.h"
#include "Renderer\Renderer.h"
#include "Renderer\Renderable.h"
#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtc\matrix_transform.hpp"

#define ZERO_TO_ONE(x) (x == 0 ? 1 : x)

class Renderer;

class RenderableObject : public Object, public Renderable{
public:
	RenderableObject();
	~RenderableObject();

	virtual void draw(Renderer *renderer);
	virtual glm::mat4x4 getModelMatrix();
	void setModel(Model *model, bool resize = false, bool reposition = false);

private:
	void drawThis(Renderer *renderer);
};