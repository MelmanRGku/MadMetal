#pragma once

#include "Light.h"

class Object3D;

class DynamicLight : public Light
{
private:
	Object3D *m_parent;
public:
	DynamicLight(long id, Animatable *anable, Object3D *parent);
	~DynamicLight();
	bool getParentHasToBeDeleted();
	void update(float dt);
};

