#pragma once

#include "Scene Manager\Scene.h"
#include "Objects\TexturedObject2D.h"
#include "Global\Assets.h"
#include <thread>

class MadMetalPresentsScreen : public Scene
{
private:
	std::thread *t;
	LoadingStatus *status;
	Audio &m_audio;

	Object3D *background;
	TexturedObject2D *loadingPic;
public:
	MadMetalPresentsScreen(Audio &audio, LoadingStatus *status, std::thread *t);
	~MadMetalPresentsScreen();
	bool simulateScene(double dt, SceneMessage &newMessage);
	void setupSceneLights();
};

