#pragma once

#include "Light.h"

class Object3D;

class DynamicLight : public Light
{
private:
	Object3D *m_parent;
	glm::vec4 m_initialPosition;
public:
	DynamicLight(long id, Animatable *anable, Object3D *parent);
	~DynamicLight();
	bool getParentHasToBeDeleted();
	void update(float dt);
	void setInitialPosition(glm::vec3 pos);
};

