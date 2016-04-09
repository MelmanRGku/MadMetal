#include "LoadingScreen.h"
#include "Factory\GameFactory.h"

LoadingScreen::LoadingScreen(SceneMessage& toDeliver, Audio &audio, LoadingStatus *status, std::thread *t) : m_audio(audio)
{

	
	m_defaultSceneCamera->setLookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -3), glm::vec3(0, 1, 0));
	m_toDeliver = toDeliver;

	createProgressBar();
	this->status = status;
	this->t = t;

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(0, 0, -30));
		a->setScale(glm::vec3(33, 24.5, 1));
		Audioable *au = new Audioable(audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/BackgroundControls1.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		background = new Object3D(3, au, p, a, r, NULL);
		m_world->addGameObject(background);
	}

	backgroundPic1 = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/BackgroundControls0.obj"));
	backgroundPic1->setupVAOs();

	backgroundPic2 = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/BackgroundControls1.obj"));
	backgroundPic2->setupVAOs();

	backgroundPic3 = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/BackgroundControls2.obj"));
	backgroundPic3->setupVAOs();

	backgroundPic4 = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/BackgroundControls3.obj"));
	backgroundPic4->setupVAOs();
}


LoadingScreen::~LoadingScreen()
{
}

#define DotSwitchDelay 0.5f
bool LoadingScreen::simulateScene(double dt, SceneMessage &newMessage) {
	m_sceneGameTimeSeconds += dt;

	Renderable3D *renderable = static_cast<Renderable3D*>(background->getRenderable());
	if (std::fmod(m_sceneGameTimeSeconds, (DotSwitchDelay * 4)) <= DotSwitchDelay) {
		renderable->setModel(backgroundPic1);
		renderable->adjustModel(true, true);
	}
	else if (std::fmod(m_sceneGameTimeSeconds, (DotSwitchDelay * 4)) > DotSwitchDelay && std::fmod(m_sceneGameTimeSeconds, (DotSwitchDelay * 4)) <= DotSwitchDelay * 2) {
		renderable->setModel(backgroundPic2);
		renderable->adjustModel(true, true);
	}
	else if (std::fmod(m_sceneGameTimeSeconds, (DotSwitchDelay * 4)) > 2 * DotSwitchDelay && std::fmod(m_sceneGameTimeSeconds, (DotSwitchDelay * 4)) <= DotSwitchDelay * 3) {
		renderable->setModel(backgroundPic3);
		renderable->adjustModel(true, true);
	}
	else {
		renderable->setModel(backgroundPic4);
		renderable->adjustModel(true, true);
	}

	bar->setProgress(status->getPercentage());
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
	Model3D *barModel = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/GGO.obj"));
	barModel->setupVAOs();

	Animatable *animatable = new Animatable();
	Renderable3D *renderable = new Renderable3D(barModel, true, true);
	Audioable *audioable = new Audioable(m_audio);
	Physicable *physicable = new Physicable(NULL);
	bar = new LoadingBar(1, audioable, physicable, animatable, renderable);

	m_world->addGameObject(bar);
}