#include "LoadingBar.h"


LoadingBar::LoadingBar(glm::vec3 size, glm::vec3 position, Model *completeBarModel)
{
	updateRotation(glm::vec3(0, 3.14/2, 0));
	updatePosition(position);
	setScale(glm::vec3(size.z, size.y, size.x));

	completeBar = new RenderableObject();
	completeBar->setModel(completeBarModel, true, true);
}


LoadingBar::~LoadingBar()
{
}

void LoadingBar::draw(Renderer *renderer) {
	RenderableObject::draw(renderer);
	completeBar->draw(renderer);
}

void LoadingBar::setProgress(float percentage) {
	completeBar->setScale(glm::vec3(percentage * (scale.z - 2 * LOADING_BAR_BORDER_SIZE), 1 - 2 * LOADING_BAR_BORDER_SIZE, 1));
	completeBar->setPosition(glm::vec3(position.x - scale.z / 2 + completeBar->getScale().x / 2 + LOADING_BAR_BORDER_SIZE, position.y, position.z));
}