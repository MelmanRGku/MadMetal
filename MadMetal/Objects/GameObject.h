#pragma once

#include "Model.h"
#include "Renderer/VAO.h"
#include "Libraries\glm\mat4x4.hpp"
#include "Libraries/glm/gtc/matrix_transform.hpp"
#include "Global/Log.h"
#include "Simulation\PhysicsManager.h"

class GameObject
{
private:

public:
	glm::vec3 position, rotation;
	VAO *vao;
	Model *model;
	GameObject();
	GameObject(VAO *vao, Model *model);
	~GameObject();
	void setVAO(VAO *vao) { this->vao = vao; }
	void setModel(Model *model) { this->model = model; }
	void setPosition(glm::vec3 pos) { this->position = pos; }
	void updatePosition(glm::vec3 dPos);
	void updatePosition(float vecx, float vecy, float vecz);
	void updateRotation(glm::vec3 angles);
	void setPhysxActor(PxRigidDynamic * physxActor);
	glm::mat4x4 getModelMatrix();
	PxRigidDynamic * physxActor;
};

