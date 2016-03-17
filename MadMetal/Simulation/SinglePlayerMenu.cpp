#include "SinglePlayerMenu.h"
#include "Objects\Text3D.h"

SinglePlayerMenu::SinglePlayerMenu(Input * input, Audio *audio)
{
	m_gamePad = input->getGamePadHandle();
	menuSystem = new SinglePlayerMenuSystem(audio, m_world);
	m_defaultSceneCamera->setLookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -3), glm::vec3(0, 1, 0));
}

SinglePlayerMenu::~SinglePlayerMenu() {
}

bool SinglePlayerMenu::simulateScene(double dt, SceneMessage &message)
{
	m_sceneGameTimeSeconds += dt;
	m_world->update(dt);
	if (menuSystem->getMessage() != SceneMessage::eNone) {
		message.setTag(menuSystem->getMessage());
		menuSystem->resetMessage();
		return true;
	}
	//check gamepad stuff
	if (m_gamePad->checkConnection() && m_sceneGameTimeSeconds>1)
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