#pragma once

#include <iostream>
#include <vector>
#include "../Objects/Object3D.h"
#include "../Objects/Object2D.h"




class World
{
private:
	std::vector<TestObject*> *gameObjects;
	PxScene *scene;
public:
	
	World();
	~World();
	
	//TODO::Build a more robust system for accessing and altering game objects, such that programs aren't forced to calculate the indicies of objects and then find them in the gameObjects vector
	std::vector<TestObject*> * getGameObjects()	{ return gameObjects; }
	void addGameObject(TestObject *obj) { gameObjects->push_back(obj); }
	TestObject *findObject(long id);
	void deleteObjectById(long id);
	void deleteObjectByIndex(int index);
	void update(float dt);
	void setScene(PxScene *scene) { this->scene = scene; }
};

