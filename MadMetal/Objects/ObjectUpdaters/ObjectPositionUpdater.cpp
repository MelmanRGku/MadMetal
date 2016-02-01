#include "ObjectPositionUpdater.h"


ObjectPositionUpdater::ObjectPositionUpdater(GameObject *obj, glm::vec3 offset, long duration)
{

	object = obj;
	this->offset = offset;
	this->totalDuration = duration;
	currentDuration = 0;

}


ObjectPositionUpdater::~ObjectPositionUpdater()
{
}


void ObjectPositionUpdater::update(long dt) {

	if (ended())
		return;

	object->updatePosition(offset * ((float)dt / totalDuration));

	currentDuration += dt;
}