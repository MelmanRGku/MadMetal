#include "ObjectUpdaterParallel.h"


ObjectUpdaterParallel::ObjectUpdaterParallel(int type) {

	if (type == TYPE_MULTIPLE_TIMES)
		throw 1;

	this->type = type;

	if (type == TYPE_ONCE)
		totalNumberOfTimes = 1;
}


ObjectUpdaterParallel::ObjectUpdaterParallel(int type, int numberOfTimes) {

	if (type != TYPE_MULTIPLE_TIMES)
		throw 2;

	this->type = type;
	this->totalNumberOfTimes = numberOfTimes;

}


ObjectUpdaterParallel::~ObjectUpdaterParallel()
{
}


void ObjectUpdaterParallel::update(long dt) {
	if (ended())
		return;

	std::pair<ObjectUpdater *, int> *up;
	for (unsigned int i = 0; i < updaters.size(); i++) {
		up = &updaters.at(i);

		if (up->first->ended()){
			up->second = up->second+1;
			up->first->restart();
		}

		if (type != TYPE_INFINITE && up->second >= totalNumberOfTimes)
			continue;

		up->first->update(dt);
	}

	currentDuration += dt;
}


bool ObjectUpdaterParallel::ended() {

	if (type == TYPE_INFINITE)
		return false;

	if (completed)
		return true;

	bool completed = true;
	for (unsigned int i = 0; i < updaters.size(); i++) {
		completed = completed && updaters.at(i).second >= totalNumberOfTimes;
	}
	this->completed = completed;

	return completed;

}


void ObjectUpdaterParallel::addObjectUpdater(ObjectUpdater *obj) {
	updaters.push_back(std::make_pair(obj, 0));
}

void ObjectUpdaterParallel::restart() {
	currentDuration = 0;
	completed = false;
	for (unsigned int i = 0; i < updaters.size(); i++) {
		updaters.at(i).first->restart();
		updaters.at(i).second = 0;
	}
}