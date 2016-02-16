#define M_PI (3.14159265359)

#include "Object.h"
#include <iostream>
#include "Car.h"

Object::Object()
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	forward = glm::vec3(0, 0, 1);
	up = glm::vec3(0, 1, 0);
}


Object::~Object()
{
}


glm::mat4x4 Object::getPhysicsModelMatrix() {
	if (!physicsActor)
		return glm::mat4x4();
	PxMat44 physModelMat(physicsActor->getGlobalPose());
	glm::mat4x4 pModelMatrix;
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			pModelMatrix[i][j] = physModelMat[i][j];
		}
	}
	return pModelMatrix;
}

glm::mat4x4 Object::getLocalModelMatrix() {
	glm::mat4x4 translate = glm::translate(glm::mat4x4(), position);
	glm::mat4x4 rotateX = glm::rotate(glm::mat4x4(), rotation.x, glm::vec3(1, 0, 0));
	glm::mat4x4 rotateY = glm::rotate(glm::mat4x4(), rotation.y, glm::vec3(0, 1, 0));
	glm::mat4x4 rotateZ = glm::rotate(glm::mat4x4(), rotation.z, glm::vec3(0, 0, 1));
	glm::mat4x4 scaleMat = glm::scale(glm::mat4x4(), this->scale);
	glm::mat4x4 res = translate * rotateX * rotateY * rotateZ * scaleMat;
	return res;
}

glm::mat4x4 Object::getModelMatrix() {	
	return getPhysicsModelMatrix() * getLocalModelMatrix();
}

PxRigidActor& Object::getActor(){ return *physicsActor; }




