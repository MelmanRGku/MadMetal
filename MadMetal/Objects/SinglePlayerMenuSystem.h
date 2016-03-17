#pragma once

#include "MenuSystem.h"

class SinglePlayerMenuSystem : public MenuSystem
{
private:

public:
	SinglePlayerMenuSystem(Audio *audio, World *world);
	~SinglePlayerMenuSystem();
	void upPressed();
	void downPressed();
	void leftPressed();
	void rightPressed();
	void aPressed();
};

