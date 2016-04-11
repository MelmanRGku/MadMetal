#pragma once

#include "Scene Manager\Scene.h"

class MainMenu : public Scene
{
private:
	GamePad * m_gamePad;
	Object3D *singlePlayerButton,
		*multiPlayerButton,
		*exitButton,
		*background,
		*selectedButton;
	SceneMessage::SceneEnum messageToReturn = SceneMessage::eNone;

public:
	MainMenu(Input * input, Audio *audio);
	~MainMenu();
	bool simulateScene(double dt, SceneMessage &newMessage);
	void upPressed();
	void downPressed();
	void aPressed();
	void selectMenuItem(Object3D *menuItem);
	void unselectMenuItem(Object3D *menuItem);
	void setupSceneLights();
};