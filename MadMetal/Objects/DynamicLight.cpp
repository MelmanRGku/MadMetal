#include "DynamicLight.h"
#include "Object3D.h"


DynamicLight::DynamicLight(long id, Animatable *anable, Object3D *parent) : Light(id, anable), m_parent(parent)
{
	m_initialPosition = glm::vec4(0, 0, 0, 1);
}


DynamicLight::~DynamicLight()
{
}

bool DynamicLight::getParentHasToBeDeleted() {
	return m_parent->getHasToBeDeleted();
}

void DynamicLight::update(float dt){
	Light::update(dt);

	m_animatable->setPosition(glm::vec3(m_parent->getModelMatrix() * m_initialPosition));
}

void DynamicLight::setInitialPosition(glm::vec3 pos) {
	m_initialPosition = glm::vec4(pos, 1);
}