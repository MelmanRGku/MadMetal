#include "Light.h"
#include "Object3D.h"

Light::Light(long id, Animatable *anable) : TestObject(id, NULL, anable, NULL)
{ 
}

bool Light::getParentHasToBeDeleted() {
	return false;
}

void Light::update(float dt) { TestObject::update(dt); }