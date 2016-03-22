#include "ObjectScaleUpdater.h"


ObjectScaleUpdater::ObjectScaleUpdater(TestObject *obj, glm::vec3 scale, float duration)
{

	object = obj;
	this->scale = scale;
	this->totalDuration = duration;
	currentDuration = 0;

}


ObjectScaleUpdater::~ObjectScaleUpdater()
{
}


void ObjectScaleUpdater::update(float dt) {

	if (ended())
		return;

	object->updateScale(scale * (float)(dt / totalDuration));

	currentDuration += dt;
}