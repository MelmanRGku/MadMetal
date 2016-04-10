#pragma once

#include <iostream>
#include <vector>
#include "../Objects/Object3D.h"
#include "../Objects/Object2D.h"
#include "Objects\ObjectUpdaters\ObjectUpdater.h"
#include "Objects\Light.h"



class World
{
private:
	std::vector<TestObject*> *gameObjects;
	std::vector<Light*> *lightObjects;

	PxScene *scene;
	std::vector<ObjectUpdater *> updaters;
public:
	
	World();
	~World();
	
	//TODO::Build a more robust system for accessing and altering game objects, such that programs aren't forced to calculate the indicies of objects and then find them in the gameObjects vector
	std::vector<TestObject*> * getGameObjects()	{ return gameObjects; }
	std::vector<Light *> * getLights() {return lightObjects;}
	void addGameObject(TestObject *obj) { gameObjects->push_back(obj); }
	void addLightObject(Light *light) { lightObjects->push_back(light); }
	TestObject *findObject(long id);
	void deleteObjectById(long id);
	void deleteObjectByIndex(int index);
	void deleteLightByIndex(int index);
	void update(float dt);
	void setScene(PxScene *scene) { this->scene = scene; }
	void addObjectUpdater(ObjectUpdater *updater) { updaters.push_back(updater); }
};

