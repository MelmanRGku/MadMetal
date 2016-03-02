#pragma once

#include <iostream>
#include <vector>
#include "../Objects/TestObject.h"




class World
{
private:
	std::vector<TestObject*> *gameObjects;
public:
	
	World();
	~World();
	
	//TODO::Build a more robust system for accessing and altering game objects, such that programs aren't forced to calculate the indicies of objects and then find them in the gameObjects vector
	std::vector<TestObject*> * getGameObjects()	{ return gameObjects; }
	void addGameObject(TestObject *obj) { gameObjects->push_back(obj); }
	TestObject *findObject(long id);
};

