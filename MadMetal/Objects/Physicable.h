#pragma once

#include "Simulation\PhysicsManager.h"
#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtc\matrix_transform.hpp"

class Physicable {
protected:
	PxRigidActor *physicsActor;
	glm::vec3 forward, up;

public:
	Physicable() {};
	virtual ~Physicable();

	glm::mat4x4 getPhysicsModelMatrix() {
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

	glm::vec3 getForwardVector() {
		glm::vec4 toReturn = glm::normalize(getPhysicsModelMatrix() * glm::vec4(forward, 0.0f)); 
		return glm::vec3(toReturn.x, toReturn.y, toReturn.z);
	}
	void setActor(PxRigidActor *actor) { physicsActor = actor; }
	PxRigidActor& getActor(){ return *physicsActor; }
};