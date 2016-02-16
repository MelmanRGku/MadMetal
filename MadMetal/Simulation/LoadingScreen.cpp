#include "LoadingScreen.h"


LoadingScreen::LoadingScreen(PlayerControllable *pc)
{

	m_mainCamera = new Camera();
	m_mainCamera->setLookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -3), glm::vec3(0, 1, 0));

	createProgressBar();

	status = new LoadingStatus();
	Assets::status = status;
	t = std::thread(Assets::loadObjsFromDirectory, "Assets/Models", false );
	this->pc = pc;
}


LoadingScreen::~LoadingScreen()
{
}


bool LoadingScreen::simulateScene(double dt, SceneMessage &newMessage) {
	bar->setProgress(status->getPercentage());
	if (status->getPercentage() >= 1){
		t.join();

		Assets::initializeVAOs();

		newMessage.setTag(NORMAL_GAME);
		newMessage.addPlayer(pc);
		return true;
	}
	return false;
}


void LoadingScreen::createProgressBar() {
	ObjModelLoader *loader = new ObjModelLoader();
	Model *barModel = loader->loadFromFile("Assets/Models/loadingBox.obj");
	barModel->setupVAOs();

	loader = new ObjModelLoader();
	Model *progressModel = loader->loadFromFile("Assets/Models/GGO.obj");
	progressModel->setupVAOs();

	bar = new LoadingBar(glm::vec3(5, 1, 1), glm::vec3(0, -2, -10), progressModel);
	bar->setModel(barModel, true, true);

	m_world->addGameObject(bar);
	delete loader;
}