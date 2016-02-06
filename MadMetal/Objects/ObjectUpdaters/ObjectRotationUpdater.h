#pragma once

#include <vector>
#include "../Object.h"
#include "ObjectUpdater.h"
#include "Libraries/glm/vec3.hpp"

class ObjectRotationUpdater : public ObjectUpdater
{
private:
	Object *object;
	glm::vec3 angles;								//in degrees

public:
	static const int ANGLE_TYPE_DEGREES = 0,
		ANGLE_TYPE_RADIANS = 1;

	ObjectRotationUpdater(Object *obj, glm::vec3 angles, float duration, int angleType);
	~ObjectRotationUpdater();
	void update(float dt);
};

