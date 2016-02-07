#pragma once

#include <iostream>
#include <vector>
#include "../Objects/Object.h"




class GameWorld
{
private:
	std::vector<Object*> *gameObjects;
public:
	
	GameWorld();
	~GameWorld();
	
	//TODO::Build a more robust system for accessing and altering game objects, such that programs aren't forced to calculate the indicies of objects and then find them in the gameObjects vector
	std::vector<Object*> * getGameObjects()	{ return gameObjects; }
	void addGameObject(Object *obj) { gameObjects->push_back(obj); }
};

