#pragma once

#define ZERO_TO_ONE(x) (x == 0 ? 1 : x)

#include "Objects\Model.h"
#include "Renderer.h"
#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtc\matrix_transform.hpp"

class Renderer;

class Renderable {
private:
	Model *model;
	glm::mat4x4 initialModelMatrix;
public:
	virtual void draw(Renderer *renderer) = 0;
	virtual glm::mat4x4 getInitialModelMatrix() { return initialModelMatrix; }
	void setModel(Model *model, bool resize = false, bool reposition = false) {
		this->model = model;

		if (resize) {
			double scaleX = 1 / ZERO_TO_ONE(model->boundingBox->getSizeX());
			double scaleY = 1 / ZERO_TO_ONE(model->boundingBox->getSizeY());
			double scaleZ = 1 / ZERO_TO_ONE(model->boundingBox->getSizeZ());
			initialModelMatrix = initialModelMatrix * glm::scale(glm::mat4x4(), glm::vec3(scaleX, scaleY, scaleZ));
		}

		if (reposition) {
			glm::mat4x4 translate = glm::translate(glm::mat4x4(), glm::vec3(-model->boundingBox->getCenterX(), -model->boundingBox->getCenterY(), -model->boundingBox->getCenterZ()));
			initialModelMatrix = initialModelMatrix * translate;
		}

	}

	Model *getModel() { return model; }
};