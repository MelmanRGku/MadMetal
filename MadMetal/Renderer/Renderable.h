#pragma once

#include "Objects\Model.h"
#include "Renderer.h"

class Renderer;

class Renderable {
public:
	Model *model;
	virtual void draw(Renderer *renderer) = 0;
};