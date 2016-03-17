#include "MainMenu.h"
#include "Objects\Text3D.h"

MainMenu::MainMenu(Input * input, Audio *audio)
{
	m_gamePad = input->getGamePadHandle();
	menuSystem = new MainMenuSystem(audio, m_world);
	m_defaultSceneCamera->setLookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -3), glm::vec3(0, 1, 0));

	{
		Renderable3D *renderable = new Renderable3D(NULL);
		Audioable *audioable = new Audioable(*audio);
		Animatable *animatable = new Animatable();
		Physicable *physicable = new Physicable(NULL);

		Text3D *loadingInfoString = new Text3D(4, audioable, physicable, animatable, renderable, 3);
		loadingInfoString->setPosition(glm::vec3(0, 5, -20));
		loadingInfoString->setString("Mad Metal");
		m_world->addGameObject(loadingInfoString);
	}
}

MainMenu::~MainMenu() {
}

bool MainMenu::simulateScene(double dt, SceneMessage &message)
{
	m_sceneGameTimeSeconds += dt;
	m_world->update(dt);
	if (menuSystem->getMessage() != SceneMessage::eNone) {
		message.setTag(menuSystem->getMessage());
		menuSystem->resetMessage();
		return true;
	}
	//check gamepad stuff
	if (m_gamePad->checkConnection() && m_sceneGameTimeSeconds > 1)
	{
		
		if (m_gamePad->isPressed(GamePad::DPadUp)) {
			menuSystem->upPressed();
		}

		if (m_gamePad->isPressed(GamePad::DPadDown)) {
			menuSystem->downPressed();
		}

		if (m_gamePad->isPressed(GamePad::AButton)) {
			menuSystem->aPressed();
		}

	}
	return false;
}