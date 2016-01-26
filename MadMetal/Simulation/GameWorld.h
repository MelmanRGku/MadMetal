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
	

	std::vector<GameObject*> * getGameObjects()	{ return gameObjects; }
	void addGameObject(GameObject *obj) { gameObjects->push_back(obj); }
};

