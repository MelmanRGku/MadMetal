#include "LoadingScreen.h"
#include "Factory\GameFactory.h"

LoadingScreen::LoadingScreen(SceneMessage& toDeliver, Audio &audio, LoadingStatus *status, std::thread *t) : m_audio(audio)
{

	
	m_defaultSceneCamera->setLookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -3), glm::vec3(0, 1, 0));
	m_toDeliver = toDeliver;

	createProgressBar();
	createLoadingString();
	createLoadingInfoString();
	this->status = status;
	this->t = t;	
}


LoadingScreen::~LoadingScreen()
{
}


bool LoadingScreen::simulateScene(double dt, SceneMessage &newMessage) {
	bar->setProgress(status->getPercentage());
	loadingInfoString->setString(status->getMessage());
	if (status->done){
		status->done = false;
		if (t != NULL) {
			t->join();
			Assets::initializeVAOs();
		}

		newMessage.setTag(m_toDeliver.getTag());
		newMessage.setPlayerTemplates(m_toDeliver.getPlayerTemplates());
		return true;
	}
	return false;
}


void LoadingScreen::createProgressBar() {
	Model3D *barModel = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/loadingBox.obj"));
	barModel->setupVAOs();

	Animatable *animatable = new Animatable();
	Renderable3D *renderable = new Renderable3D(barModel, true, true);
	Audioable *audioable = new Audioable(m_audio);
	Physicable *physicable = new Physicable(NULL);
	bar = new LoadingBar(1, audioable, physicable, animatable, renderable);

	m_world->addGameObject(bar);
}

void LoadingScreen::createLoadingString() {
	Renderable3D *renderable = new Renderable3D(NULL);
	Audioable *audioable = new Audioable(m_audio);
	Animatable *animatable = new Animatable();
	Physicable *physicable = new Physicable(NULL);

	loadingString = new Text3D(3, audioable, physicable, animatable, renderable, 1);
	loadingString->setString("Loading");
	loadingString->setPosition(glm::vec3(0, .7, -10));
	m_world->addGameObject(loadingString);
}

void LoadingScreen::createLoadingInfoString() {
	Renderable3D *renderable = new Renderable3D(NULL);
	Audioable *audioable = new Audioable(m_audio);
	Animatable *animatable = new Animatable();
	Physicable *physicable = new Physicable(NULL);

	loadingInfoString = new Text3D(4, audioable, physicable, animatable, renderable, 1);
	loadingInfoString->setPosition(glm::vec3(0, -4.5, -20));
	m_world->addGameObject(loadingInfoString);
}