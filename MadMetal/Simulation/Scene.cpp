#include "Scene.h"


Scene::Scene()
{
	world = new GameWorld();
	audio = new Audio();
}


Scene::~Scene()
{
	delete world;
	delete audio;
}
