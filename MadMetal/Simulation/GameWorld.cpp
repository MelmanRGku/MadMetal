#include "GameWorld.h"


GameWorld::GameWorld() {
	gameObjects = new std::vector<GameObject*>;
}


GameWorld::~GameWorld() {
	delete gameObjects;
}