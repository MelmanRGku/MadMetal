#pragma once

#include "Audio/Audio.h"
#include "GameWorld.h"

class Scene
{
protected:
	GameWorld *world;
	Audio *audio;
public:
	Scene();
	~Scene();
	virtual void simulate(double dt) = 0;
	GameWorld* getGameWorld() { return world; }
	virtual void initialize() {};
};

