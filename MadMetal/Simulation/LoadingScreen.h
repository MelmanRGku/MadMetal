#pragma once

#include "Scene Manager\Scene.h"
#include "Global\Assets.h"
#include "Objects\LoadingBar.h"
#include <thread>

class LoadingScreen :
	public Scene
{
private:
	std::thread t;
	LoadingStatus *status;
	PlayerControllable *pc;
	LoadingBar *bar;

	void createProgressBar();
public:
	LoadingScreen(PlayerControllable *pc);
	~LoadingScreen();
	bool simulateScene(double dt, SceneMessage &newMessage);
};

