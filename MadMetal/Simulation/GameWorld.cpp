#include "GameWorld.h"


GameWorld::GameWorld() {
	gameObjects = new std::vector<Object*>;
}


GameWorld::~GameWorld() {
	delete gameObjects;
}