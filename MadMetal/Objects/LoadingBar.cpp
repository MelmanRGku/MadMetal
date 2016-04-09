#include "LoadingBar.h"
#include "ObjectLoaders\ObjModelLoader.h"
#include "Global\Assets.h"

LoadingBar::LoadingBar(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable, NULL)
{
	m_animatable->updatePosition(glm::vec3(completedPosX, -9.3f, -25));
	m_animatable->setScale(glm::vec3(completedScaleX, 0.3f, 0.1f));
}


LoadingBar::~LoadingBar()
{
}

void LoadingBar::setProgress(float percentage) {
	setScale(glm::vec3(percentage * completedScaleX, getScale().y, getScale().z));
	setPosition(glm::vec3(completedPosX - (completedScaleX - getScale().x) / 2, getAnimatablePos().y, getAnimatablePos().z));
}