#include "ObjectRotationUpdater.h"


ObjectRotationUpdater::ObjectRotationUpdater(GameObject *obj, glm::vec3 angles, long duration, int angleType)
{

	object = obj;
	this->totalDuration = duration;
	currentDuration = 0;

	switch (angleType) {
	case ANGLE_TYPE_RADIANS:
		this->angles = angles;
		break;
	case ANGLE_TYPE_DEGREES:
		this->angles = glm::vec3(glm::radians(angles.x), glm::radians(angles.y), glm::radians(angles.z));
		break;
	}
}


ObjectRotationUpdater::~ObjectRotationUpdater()
{
}


void ObjectRotationUpdater::update(long dt) {

	if (ended())
		return;

	object->updateRotation(angles * ((float)dt / totalDuration));

	currentDuration += dt;
}