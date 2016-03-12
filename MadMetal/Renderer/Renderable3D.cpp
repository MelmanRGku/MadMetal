#include "Renderable3D.h"

#define ZERO_TO_ONE(x) (x == 0 ? 1 : x)

Renderable3D::~Renderable3D() {}

Renderable3D::Renderable3D(Model3D* Model, bool resize, bool reposition) : Renderable(Model)
{
	adjustModel(resize, reposition);
}

void Renderable3D::adjustModel(bool resize, bool reposition)
{
	initialModelMatrix = glm::mat4x4();
	Model3D *model = static_cast<Model3D *>(m_model);
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


void Renderable3D::setAlpha(float alpha) {
	static_cast<Model3D *>(m_model)->setAlpha(alpha);
}