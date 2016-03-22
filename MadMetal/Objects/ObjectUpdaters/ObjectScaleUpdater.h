#pragma once

#include <vector>
#include "../TestObject.h"
#include "ObjectUpdater.h"
#include "Libraries/glm/vec3.hpp"


class ObjectScaleUpdater : public ObjectUpdater
{
private:
	TestObject *object;
	glm::vec3 scale;

public:
	ObjectScaleUpdater(TestObject *obj, glm::vec3 scale, float duration);
	~ObjectScaleUpdater();
	void update(float dt);
};

