#pragma once

#include "MenuSystem.h"

class MainMenuSystem : public MenuSystem
{
public:
	MainMenuSystem(Audio *audio, World *world);
	~MainMenuSystem();
	void upPressed();
	void downPressed();
	void leftPressed();
	void rightPressed();
	void aPressed();
};

