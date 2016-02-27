#include "Renderable.h"


Renderable::Renderable(Model* Model)
{
	m_model = Model;
}

void Renderable::setModel(Model *model, bool resize = false, bool reposition = false)
{
	this->model = model;

	if (model != NULL) {
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
	else {
		initialModelMatrix = glm::mat4x4();
	}
}