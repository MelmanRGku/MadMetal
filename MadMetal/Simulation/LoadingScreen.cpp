#include "LoadingScreen.h"
#include "Factory\GameFactory.h"

LoadingScreen::LoadingScreen(SceneMessage& toDeliver, Audio &audio) : m_audio(audio)
{

	
	m_defaultSceneCamera->setLookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -3), glm::vec3(0, 1, 0));
	m_toDeliver = toDeliver;

	createProgressBar();

	status = new LoadingStatus();
	Assets::status = status;
	t = std::thread(Assets::loadObjsFromDirectory, "Assets/Models", false );
	
}


LoadingScreen::~LoadingScreen()
{
}


bool LoadingScreen::simulateScene(double dt, SceneMessage &newMessage) {
	bar->setProgress(status->getPercentage());
	if (status->getPercentage() >= 1){
		t.join();

		Assets::initializeVAOs();

		newMessage.setTag(SceneMessage::eGameSimulation);
		newMessage.setPlayerTemplates(m_toDeliver.getPlayerTemplates());
		return true;
	}
	return false;
}


void LoadingScreen::createProgressBar() {
	ObjModelLoader *loader = new ObjModelLoader();
	Model *barModel = loader->loadFromFile("Assets/Models/loadingBox.obj");
	barModel->setupVAOs();

	Animatable *animatable = new Animatable();
	Renderable *renderable = new Renderable(NULL);
	renderable->setModel(barModel, true, true);
	Audioable *audioable = new Audioable(m_audio);
	Physicable *physicable = new Physicable(NULL);
	bar = new LoadingBar(1, *audioable, *physicable, *animatable, *renderable);

	m_world->addGameObject(bar);
	delete loader;
}