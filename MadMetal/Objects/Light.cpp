#include "Light.h"
#include "TestObject.h"
#include "Object3D.h"

Light::Light(TestObject * myObject, float maximumLife, float totallife)
{ 
	m_object = myObject; 
}

TestObject * Light::getObject()
{
	return m_object;
}

glm::vec3 Light::getPosition()
{
	return static_cast<Object3D *>(m_object)->getPosition();
}