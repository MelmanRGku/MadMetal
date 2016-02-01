#pragma once

#include <vector>
#include "../GameObject.h"
#include "ObjectUpdater.h"
#include "Libraries/glm/vec3.hpp"


class ObjectPositionUpdater : public ObjectUpdater
{
private:
	GameObject *object;
	glm::vec3 offset;

public:
	ObjectPositionUpdater(GameObject *obj, glm::vec3 offset, long duration);
	~ObjectPositionUpdater();
	void update(long dt);
};

