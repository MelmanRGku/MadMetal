#pragma once

#include "Objects\Model.h"
#include "Renderer.h"

class Renderer;

class Renderable {
public:
	Model *model;
	glm::mat4x4 initialModelMatrix;
	virtual void draw(Renderer *renderer) = 0;
	Model *getModel() { return model; }
	virtual glm::mat4x4 getInitialModelMatrix() { return initialModelMatrix; }
};


