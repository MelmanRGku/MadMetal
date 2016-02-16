#pragma once

#include "Scene Manager\Scene.h"
#include "Global\Assets.h"
#include <thread>

class LoadingScreen :
	public Scene
{
private:
	std::thread t;
	LoadingStatus *status;
	PlayerControllable *pc;
public:
	LoadingScreen(PlayerControllable *pc);
	~LoadingScreen();
	bool simulateScene(double dt, SceneMessage &newMessage);
};

