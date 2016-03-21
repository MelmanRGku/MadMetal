#include "World.h"


World::World() {
	gameObjects = new std::vector<TestObject*>;
}


World::~World() {
	for (unsigned int i = 0; i < gameObjects->size(); i++){
		delete gameObjects->at(i);
	}
	delete gameObjects;

	for (unsigned int i = 0; i < updaters.size(); i++) {
		delete updaters.at(i);
	}
}


TestObject *World::findObject(long id) {
	long mid, left = 0;
	long right = gameObjects->size();
	while (left < right) {
		mid = left + (right - left) / 2;
		if (id > gameObjects->at(mid)->getIndex()){
			left = mid + 1;
		}
		else if (id < gameObjects->at(mid)->getIndex()){
			right = mid;
		}
		else {
			return gameObjects->at(mid);
		}
	}

	return NULL;
}


void World::deleteObjectById(long id) {
	long mid, left = 0;
	long right = gameObjects->size();
	while (left < right) {
		mid = left + (right - left) / 2;
		if (id > gameObjects->at(mid)->getIndex()){
			left = mid + 1;
		}
		else if (id < gameObjects->at(mid)->getIndex()){
			right = mid;
		}
		else {
			TestObject *obj = gameObjects->at(mid);
			gameObjects->erase(gameObjects->begin()+mid);
			Object3D *object3D = dynamic_cast<Object3D *>(obj);
			if (object3D != NULL)
				scene->removeActor(object3D->getActor());
			delete obj;
			break;
		}
	}
}

void World::deleteObjectByIndex(int index) {
	TestObject *obj = gameObjects->at(index);
	gameObjects->erase(gameObjects->begin() + index);
	Object3D *object3D = dynamic_cast<Object3D *>(obj);
	if (object3D != NULL)
		scene->removeActor(object3D->getActor());
	delete obj;
}

void World::update(float dt) {
	for (int i = 0; i < gameObjects->size(); i++) {
		TestObject *obj = gameObjects->at(i);

		if (obj->getHasToBeDeleted()) {
			deleteObjectByIndex(i);
			continue;
		}

		obj->update(dt);
	}

	for (unsigned int i = 0; i < updaters.size(); i++) {
		updaters.at(i)->update(dt);
	}
}