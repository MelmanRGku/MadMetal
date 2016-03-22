#pragma once

#include <vector>
#include "../TestObject.h"
#include "ObjectUpdater.h"
#include "Libraries/glm/vec3.hpp"


class ObjectPositionUpdater : public ObjectUpdater
{
private:
	TestObject *object;
	glm::vec3 offset;

public:
	ObjectPositionUpdater(TestObject *obj, glm::vec3 offset, float duration);
	~ObjectPositionUpdater();
	void update(float dt);
};

