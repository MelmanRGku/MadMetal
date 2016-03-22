#pragma once

#include "Renderable.h"
#include "Objects\Model2D.h"

class Renderer;

class Renderable2D : public Renderable{
public:
	glm::mat4x4 initialModelMatrix;
public:
	Renderable2D(Model2D *model);
	virtual ~Renderable2D();
};
