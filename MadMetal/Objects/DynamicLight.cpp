#include "DynamicLight.h"
#include "Object3D.h"


DynamicLight::DynamicLight(long id, Animatable *anable, Object3D *parent) : Light(id, anable), m_parent(parent)
{
}


DynamicLight::~DynamicLight()
{
}

bool DynamicLight::getParentHasToBeDeleted() {
	return m_parent->getHasToBeDeleted();
}

void DynamicLight::update(float dt){
	m_animatable->setPosition(m_parent->getPosition());
}