#include "SinglePlayerMenuSystem.h"
#include "Global\Assets.h"
#include "Button.h"
#include "Objects\ObjectUpdaters\ObjectPositionUpdater.h"
#include "Objects\ObjectUpdaters\ObjectRotationUpdater.h"
#include "Objects\ObjectUpdaters\ObjectScaleUpdater.h"
#include "Objects\ObjectUpdaters\ObjectUpdaterSequence.h"
#include "Objects\ObjectUpdaters\ObjectUpdaterParallel.h"


SinglePlayerMenuSystem::SinglePlayerMenuSystem(Audio *audio, World *world) : MenuSystem(audio, world)
{
	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(-2.2, 1.55, -5));
		a->setScale(glm::vec3(1, 1, 0.00001));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/s-play.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		Button *spButton = new Button(1, au, p, a, r);
		addMenuObject(spButton);
		m_world->addGameObject(spButton);
		m_selectedObject = spButton;
		m_selectedObjectIndex = 0;
	}

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(0, 0, -25));
		a->setScale(glm::vec3(5, 1, 1));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/loadingBox.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		Button *spButton = new Button(2, au, p, a, r);
		addMenuObject(spButton);
		m_world->addGameObject(spButton);
	}

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(0, -2, -25));
		a->setScale(glm::vec3(5, 1, 1));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/loadingBox.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		Button *spButton = new Button(3, au, p, a, r);
		addMenuObject(spButton);
		m_world->addGameObject(spButton);
	}
}


SinglePlayerMenuSystem::~SinglePlayerMenuSystem()
{
}

void SinglePlayerMenuSystem::upPressed() {
	m_selectedObjectIndex--;
	if (m_selectedObjectIndex < 0)
		m_selectedObjectIndex = m_objects.size() - 1;
	{
		ObjectPositionUpdater *upd = new ObjectPositionUpdater(m_selectedObject, glm::vec3(0, 0, -10), .5);
		m_world->addObjectUpdater(upd);
	}

	m_selectedObject = m_objects.at(m_selectedObjectIndex);

	{
		ObjectPositionUpdater *upd = new ObjectPositionUpdater(m_selectedObject, glm::vec3(0, 0, 10), .5);
		m_world->addObjectUpdater(upd);
	}
}

void SinglePlayerMenuSystem::downPressed() {
	m_selectedObjectIndex++;
	if (m_selectedObjectIndex >= m_objects.size())
		m_selectedObjectIndex = 0;
	{
		ObjectPositionUpdater *upd = new ObjectPositionUpdater(m_selectedObject, glm::vec3(0, 0, -10), .5);
		m_world->addObjectUpdater(upd);
	}

	m_selectedObject = m_objects.at(m_selectedObjectIndex);

	{
		ObjectPositionUpdater *upd = new ObjectPositionUpdater(m_selectedObject, glm::vec3(0, 0, 10), .5);
		m_world->addObjectUpdater(upd);
	}
}

void SinglePlayerMenuSystem::leftPressed() {

}

void SinglePlayerMenuSystem::rightPressed() {

}

void SinglePlayerMenuSystem::aPressed() {
	if (m_selectedObject->getId() == 1)
		messageToReturn = SceneMessage::ePop;
}