#include "ObjectUpdaterSequence.h"

ObjectUpdaterSequence::ObjectUpdaterSequence(int type) {

	if (type == TYPE_MULTIPLE_TIMES)
		throw 1;

	this->type = type;

	if (type == TYPE_ONCE)
		totalNumberOfTimes = 1;
}


ObjectUpdaterSequence::ObjectUpdaterSequence(int type, int numberOfTimes) {

	if (type != TYPE_MULTIPLE_TIMES)
		throw 2;

	this->type = type;
	this->totalNumberOfTimes = numberOfTimes;

}


ObjectUpdaterSequence::~ObjectUpdaterSequence()
{
}


void ObjectUpdaterSequence::update(float dt) {

	if (updaters.at(currentStep)->ended())
		currentStep++;

	if (currentStep == updaters.size()) {
		currentNumberOfTimes++;
		currentStep = 0;
		for (unsigned int i = 0; i < updaters.size(); i++)
			updaters.at(i)->restart();
	}

	if (ended())
		return;

	updaters.at(currentStep)->update(dt);

	currentDuration += dt;
}


bool ObjectUpdaterSequence::ended() {

	if (type == TYPE_INFINITE)
		return false;
	else if (type == TYPE_MULTIPLE_TIMES || type == TYPE_ONCE)
		return currentNumberOfTimes >= totalNumberOfTimes;
	else return true;
}


void ObjectUpdaterSequence::addObjectUpdater(ObjectUpdater *obj) {
	updaters.push_back(obj);
}

void ObjectUpdaterSequence::restart() { 
	currentDuration = 0;
	currentStep = 0;
	currentNumberOfTimes = 0;
	for (unsigned int i = 0; i < updaters.size(); i++)
		updaters.at(i)->restart();
}