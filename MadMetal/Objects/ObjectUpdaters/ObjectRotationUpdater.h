#pragma once

#include <vector>
#include "../TestObject.h"
#include "ObjectUpdater.h"
#include "Libraries/glm/vec3.hpp"

class ObjectRotationUpdater : public ObjectUpdater
{
private:
	TestObject *object;
	glm::vec3 angles;								//in degrees

public:
	static const int ANGLE_TYPE_DEGREES = 0,
		ANGLE_TYPE_RADIANS = 1;

	ObjectRotationUpdater(TestObject *obj, glm::vec3 angles, float duration, int angleType);
	~ObjectRotationUpdater();
	void update(float dt);
};

