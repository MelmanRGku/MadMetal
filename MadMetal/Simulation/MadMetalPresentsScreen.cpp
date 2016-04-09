#include "MadMetalPresentsScreen.h"


MadMetalPresentsScreen::MadMetalPresentsScreen(Audio &audio, LoadingStatus *status, std::thread *t) : m_audio(audio)
{


	m_defaultSceneCamera->setLookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -3), glm::vec3(0, 1, 0));

	this->status = status;
	this->t = t;

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(0, 0, -30));
		a->setScale(glm::vec3(33, 24.5, 1));
		Audioable *au = new Audioable(audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/MadMetalPresents.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		background = new Object3D(3, au, p, a, r, NULL);
		m_world->addGameObject(background);
	}

	//loading background
	{
		Animatable *a = new Animatable();
		a->setPosition(glm::vec3(0.9f, -0.9f, 0));
		a->setScale(glm::vec3(0.15f, 0.15f, 0));
		Audioable *au = new Audioable(audio);
		Model2D *model;
		model = new Model2D(Assets::loadTextureFromDirectory("Assets/Textures/load_bar_background.png"));
		model->getTexture()->Load();
		Renderable2D *r = new Renderable2D(model);
		m_world->addGameObject(new TexturedObject2D(1, au, a, r));
	}

	{
		Animatable *a = new Animatable();
		a->setPosition(glm::vec3(0.9f, -0.9f, 0));
		a->setScale(glm::vec3(0.15f, 0.15f, 0));
		Audioable *au = new Audioable(audio);
		Model2D *model;
		model = new Model2D(Assets::loadTextureFromDirectory("Assets/Textures/load_bar_front.png"));
		model->getTexture()->Load();
		Renderable2D *r = new Renderable2D(model);
		loadingPic = new TexturedObject2D(1, au, a, r);
		m_world->addGameObject(loadingPic);
	}
}


MadMetalPresentsScreen::~MadMetalPresentsScreen()
{
}

#define DotSwitchDelay 0.5f
bool MadMetalPresentsScreen::simulateScene(double dt, SceneMessage &newMessage) {
	m_sceneGameTimeSeconds += dt;

	loadingPic->updateRotation(glm::vec3(0, 0, -dt * 600));

	if (status->done){
		status->done = false;
		if (t != NULL) {
			t->join();
			Assets::initializeVAOs();
		}

		newMessage.setTag(SceneMessage::eMainMenu);
		return true;
	}

	return false;
}