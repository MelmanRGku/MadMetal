#include "World.h"


World::World() {
	gameObjects = new std::vector<TestObject*>;
}


World::~World() {
	delete gameObjects;
}


TestObject *World::findObject(long id) {
	long mid, left = 0;
	long right = gameObjects->size();
	while (left < right) {
		mid = left + (right - left) / 2;
		if (id > gameObjects->at(mid)->getId()){
			left = mid + 1;
		}
		else if (id < gameObjects->at(mid)->getId()){
			right = mid;
		}
		else {
			return gameObjects->at(mid);
		}
	}

	return NULL;
}