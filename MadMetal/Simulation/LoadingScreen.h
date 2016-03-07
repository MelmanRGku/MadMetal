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
	LoadingBar *bar;
	SceneMessage m_toDeliver;
	Audio &m_audio;

	void createProgressBar();
public:
	LoadingScreen(SceneMessage &toDeliver, Audio &audio);
	~LoadingScreen();
	bool simulateScene(double dt, SceneMessage &newMessage);
};

