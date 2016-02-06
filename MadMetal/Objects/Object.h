#pragma once

#include <vector>
#include "Libraries\glm\vec3.hpp"
#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtc\matrix_transform.hpp"

class Object
{
protected:
	std::vector<Object *> childObjects;
	glm::vec3 position, rotation, scale;
public:
	Object();
	virtual ~Object();

	glm::mat4x4 getModelMatrix();
	void updateRotation(glm::vec3 dr) { rotation += dr; }
	void updatePosition(glm::vec3 dp) { position += dp; }
};

