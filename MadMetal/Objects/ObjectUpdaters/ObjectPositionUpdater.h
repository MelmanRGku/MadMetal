#pragma once

#include <vector>
#include "../Object.h"
#include "ObjectUpdater.h"
#include "Libraries/glm/vec3.hpp"


class ObjectPositionUpdater : public ObjectUpdater
{
private:
	Object *object;
	glm::vec3 offset;

public:
	ObjectPositionUpdater(Object *obj, glm::vec3 offset, float duration);
	~ObjectPositionUpdater();
	void update(float dt);
};

