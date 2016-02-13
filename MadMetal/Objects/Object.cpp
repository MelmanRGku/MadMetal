#include "Object.h"
#include <iostream>

Object::Object()
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
}


Object::~Object()
{
}

glm::mat4x4 Object::getModelMatrix() {
	PxTransform tmp = physicsActor->getGlobalPose();
	//std::cout << tmp.p.x << " - " << tmp.p.y << " - " << tmp.p.z << std::endl;
	glm::vec3 physPos = (physicsActor) ? glm::vec3(tmp.p.x, tmp.p.y, tmp.p.z) : glm::vec3(0, 0, 0);
	glm::mat4x4 translate = glm::translate(glm::mat4x4(), position + physPos);
	glm::mat4x4 rotateX = glm::rotate(glm::mat4x4(), rotation.x, glm::vec3(1, 0, 0));
	glm::mat4x4 rotateY = glm::rotate(glm::mat4x4(), rotation.y, glm::vec3(0, 1, 0));
	glm::mat4x4 rotateZ = glm::rotate(glm::mat4x4(), rotation.z, glm::vec3(0, 0, 1));
	glm::mat4x4 res = translate * rotateX * rotateY * rotateZ;
	return res;
}

PxRigidActor& Object::getActor(){ return *physicsActor; }




