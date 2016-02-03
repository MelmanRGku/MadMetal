#pragma once

#include <iostream>
#include <vector>
#include "../Objects/GameObject.h"




class GameWorld
{
private:
	std::vector<GameObject*> *gameObjects;
public:
	
	GameWorld();
	~GameWorld();
	
	//TODO::Build a more robust system for accessing and altering game objects, such that programs aren't forced to calculate the indicies of objects and then find them in the gameObjects vector
	std::vector<GameObject*> * getGameObjects()	{ return gameObjects; }
	void addGameObject(GameObject *obj) { gameObjects->push_back(obj); }
};

