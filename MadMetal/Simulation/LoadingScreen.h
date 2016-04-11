#pragma once

#include "Scene Manager\Scene.h"
#include "Global\Assets.h"
#include "Objects\LoadingBar.h"
#include "Objects\Text3D.h"
#include <thread>

class LoadingScreen :
	public Scene
{
private:
	std::thread *t;
	LoadingStatus *status;
	LoadingBar *bar;
	SceneMessage m_toDeliver;
	Audio &m_audio;

	Object3D *background;
	Model3D *backgroundPic1 = NULL,
		*backgroundPic2 = NULL,
		*backgroundPic3 = NULL,
		*backgroundPic4 = NULL;

	void createProgressBar();
public:
	LoadingScreen(SceneMessage &toDeliver, Audio &audio, LoadingStatus *status, std::thread *t);
	~LoadingScreen();
	bool simulateScene(double dt, SceneMessage &newMessage);
	void setupSceneLights();
};

