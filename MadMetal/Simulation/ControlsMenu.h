#pragma once

#include "Scene Manager\Scene.h"

class ControlsMenu : public Scene
{
private:
	GamePad * m_gamePad;
	Audio *m_audio;
public:
	ControlsMenu(Input * input, Audio *audio);
	~ControlsMenu();
	bool simulateScene(double dt, SceneMessage &newMessage);
};

