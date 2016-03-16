#pragma once

#include "Scene Manager\Scene.h"
#include "Objects\MainMenuSystem.h"

class MainMenu : public Scene
{
private:
	GamePad * m_gamePad;
	MainMenuSystem *menuSystem;

public:
	MainMenu(Input * input, Audio *audio);
	~MainMenu();
	bool simulateScene(double dt, SceneMessage &newMessage);
};