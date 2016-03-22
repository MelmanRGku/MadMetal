#pragma once

#include "Objects\Model.h"
#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtc\matrix_transform.hpp"

class Renderer;

class Renderable {
public:
	Model *m_model;
public:
	Renderable(Model *model);
	virtual ~Renderable();
	Model *getModel() { return m_model; }
	void setModel(Model *model);
};


