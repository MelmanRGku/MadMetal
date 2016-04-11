#pragma once

#include "Scene Manager\Scene.h"
#include "Game Logic\PlayerControllable.h"
#include "Objects\Text3D.h"

class PauseMenu : public Scene
{
private:
	Audio *m_audio;
	GamePad * m_gamePad; 
	std::vector<ControllableTemplate *> m_playerTemplates;
	Object3D *resumeButton,
		*restartButton,
		*exitToMainMenuButton,
		*exitToWindowsButton,
		*selectedButton,
		*background;
	SceneMessage::SceneEnum messageToReturn = SceneMessage::eNone;
	bool stopMusic = false;

public:
	PauseMenu(std::vector<ControllableTemplate *> players, Audio *audio);
	~PauseMenu();
	bool simulateScene(double dt, SceneMessage &newMessage);
	void upPressed();
	void downPressed();
	void aPressed();
	void selectMenuItem(Object3D *menuItem);
	void unselectMenuItem(Object3D *menuItem);
	void setupSceneLights();
};

