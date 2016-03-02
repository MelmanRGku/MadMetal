#pragma once

#include "Objects\Model.h"
#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtc\matrix_transform.hpp"

class Renderer;

class Renderable {
public:
	Model *m_model;
	glm::mat4x4 initialModelMatrix;
public:
	Renderable(Model *model, bool resize = false, bool reposition = false);
	Renderable();
	virtual ~Renderable() {}
	virtual glm::mat4x4 getInitialModelMatrix() { return initialModelMatrix; }
	Model *getModel() { return m_model; }
	void setModel(Model *model, bool resize = false, bool reposition = false);
};


