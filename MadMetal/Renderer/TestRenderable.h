#pragma once

#define ZERO_TO_ONE(x) (x == 0 ? 1 : x)

#include "Objects\Model.h"
#include "Renderer.h"
#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtc\matrix_transform.hpp"

class Renderer;

class TestRenderable {
private:
	Model *m_model;
	glm::mat4x4 initialModelMatrix;
public:
	TestRenderable();
	virtual ~TestRenderable();
	virtual glm::mat4x4 getInitialModelMatrix() { return initialModelMatrix; }
	void setModel(Model *model, bool resize = false, bool reposition = false);
	Model *getModel() { return m_model; }
};