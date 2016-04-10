#include "ControlsMenu.h"
#include "Global\Assets.h"
#include "Objects\TexturedObject2D.h"

ControlsMenu::ControlsMenu(Input * input, Audio *audio)
{
	m_defaultSceneCamera->setLookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -3), glm::vec3(0, 1, 0));
	m_gamePad = input->getGamePadHandle();
	m_audio = audio;

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(0, 0, -30));
		a->setScale(glm::vec3(33, 24.5, 1));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/BackgroundControls.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		Object3D *background = new Object3D(3, au, p, a, r, NULL);
		m_world->addGameObject(background);
	}

	{
		Animatable *a = new Animatable();
		a->setPosition(glm::vec3(0.7f, -0.9f, 0));
		a->setScale(glm::vec3(0.50f, 0.15f, 0));
		Audioable *au = new Audioable(*audio);
		Model2D *model;
		model = new Model2D(Assets::loadTextureFromDirectory("Assets/Textures/press_b_to_return.png"));
		model->getTexture()->Load();
		Renderable2D *r = new Renderable2D(model);
		m_world->addGameObject(new TexturedObject2D(1, au, a, r));
	}
}


ControlsMenu::~ControlsMenu()
{
}

bool ControlsMenu::simulateScene(double dt, SceneMessage &newMessage) {
	m_sceneGameTimeSeconds += dt;
	m_world->update(dt);
	
	if (m_gamePad->isPressed(GamePad::BButton) && m_sceneGameTimeSeconds > 1) {
		m_audio->queAudioSource(NULL, MenuBackButtonSound());
		newMessage.setTag(SceneMessage::ePop);
		return true;
	}

	//music
	if (m_audio->getMusicFinished()) {
		m_audio->playMusic(CrysisTwoThemeSong(), 1);
	}

	return false;
}