#pragma once

#include "Renderable.h"
#include "Objects\Model3D.h"

class Renderer;

class Renderable3D : public Renderable{
public:
	glm::mat4x4 initialModelMatrix;
public:
	Renderable3D(Model3D *model, bool resize = false, bool reposition = false);
	virtual ~Renderable3D();
	virtual glm::mat4x4 getInitialModelMatrix() { return initialModelMatrix; }
	void adjustModel(bool resize = false, bool reposition = false);
	void setAlpha(float alpha);
};


