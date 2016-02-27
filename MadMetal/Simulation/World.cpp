#include "World.h"


World::World() {
	gameObjects = new std::vector<TestObject*>;
}


World::~World() {
	delete gameObjects;
}