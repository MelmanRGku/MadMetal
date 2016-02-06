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
	

	std::vector<Object*> * getGameObjects()	{ return gameObjects; }
	void addGameObject(Object *obj) { gameObjects->push_back(obj); }
};

