#pragma once

#include <iostream>
#include <vector>
#include "../Objects/Object3D.h"
#include "../Objects/Object2D.h"
#include "Objects\ObjectUpdaters\ObjectUpdater.h"
#include "Objects\Light.h"

#define MAX_NUM_OF_LIGHTS 100

class World
{
private:
	std::vector<TestObject*> *gameObjects;
	std::vector<Light*> *lights;

	PxScene *scene;
	std::vector<ObjectUpdater *> updaters;
	std::vector<std::pair<PxActor *, float>> actorsToDelete;
	float worldTime;
public:
	
	World();
	~World();
	
	//TODO::Build a more robust system for accessing and altering game objects, such that programs aren't forced to calculate the indicies of objects and then find them in the gameObjects vector
	std::vector<TestObject*> * getGameObjects()	{ return gameObjects; }
	std::vector<Light *> * getLights() { return lights; }
	void addGameObject(TestObject *obj) { gameObjects->push_back(obj); }
	void addLightObject(Light *light) { if (lights->size() == MAX_NUM_OF_LIGHTS) return; lights->push_back(light); }
	TestObject *findObject(long id);
	void deleteObjectById(long id);
	void deleteObjectByIndex(int index);
	void deleteLightByIndex(int index);
	void update(float dt);
	void setScene(PxScene *scene) { this->scene = scene; }
	void addObjectUpdater(ObjectUpdater *updater) { updaters.push_back(updater); }
};

