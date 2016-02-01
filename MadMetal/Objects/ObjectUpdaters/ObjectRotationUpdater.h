#pragma once

#include <vector>
#include "../GameObject.h"
#include "ObjectUpdater.h"
#include "Libraries/glm/vec3.hpp"

class ObjectRotationUpdater : public ObjectUpdater
{
private:
	GameObject *object;
	glm::vec3 angles;								//in degrees

public:
	static const int ANGLE_TYPE_DEGREES = 0,
		ANGLE_TYPE_RADIANS = 1;

	ObjectRotationUpdater(GameObject *obj, glm::vec3 angles, long duration, int angleType);
	~ObjectRotationUpdater();
	void update(long dt);
};

