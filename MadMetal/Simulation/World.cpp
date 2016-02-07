#include "World.h"


World::World() {
	gameObjects = new std::vector<Object*>;
}


World::~World() {
	delete gameObjects;
}