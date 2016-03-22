#include "LoadingBar.h"
#include "ObjectLoaders\ObjModelLoader.h"
#include "Global\Assets.h"

LoadingBar::LoadingBar(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable, NULL)
{
	m_animatable->updatePosition(glm::vec3(0, -1, -10));
	m_animatable->setScale(glm::vec3(5, 1, 1));

	Model3D *progressModel = static_cast<Model3D*>(Assets::loadObjFromDirectory("Assets/Models/GGO.obj"));
	progressModel->setupVAOs();

	Animatable *animatable = new Animatable();
	Renderable3D *renderable = new Renderable3D(progressModel, true, true);
	Audioable *audioable = new Audioable(m_audioable->getAudioHandle());
	Physicable *physicable = new Physicable(NULL);
	completeBar = new Object3D(id + 1, audioable, physicable, animatable, renderable, NULL);
}


LoadingBar::~LoadingBar()
{
	delete completeBar;
}

bool LoadingBar::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	if (type != Renderer::ShaderType::SHADER_TYPE_CELL || passNumber > 1)
		return false;

	Object3D::draw(renderer, type, passNumber);
	completeBar->draw(renderer, type, passNumber);

	return false;
}

void LoadingBar::setProgress(float percentage) {
	completeBar->setScale(glm::vec3(percentage * (getScale().x - 2 * LOADING_BAR_BORDER_SIZE), 1 - 2 * LOADING_BAR_BORDER_SIZE, 1));
	completeBar->setPosition(glm::vec3(getAnimatablePos().x - getScale().x / 2 + completeBar->getScale().x / 2 + LOADING_BAR_BORDER_SIZE, getAnimatablePos().y, getAnimatablePos().z));
}