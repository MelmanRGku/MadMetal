#include "ObjectPositionUpdater.h"


ObjectPositionUpdater::ObjectPositionUpdater(Object *obj, glm::vec3 offset, float duration)
{

	object = obj;
	this->offset = offset;
	this->totalDuration = duration;
	currentDuration = 0;

}


ObjectPositionUpdater::~ObjectPositionUpdater()
{
}


void ObjectPositionUpdater::update(float dt) {

	if (ended())
		return;

	object->updatePosition(offset * (dt / totalDuration));

	currentDuration += dt;
}