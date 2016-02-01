#include "GameObject.h"


GameObject::GameObject()
{
}

GameObject::GameObject(VAO *vao, Model *model) {
	setVAO(vao);
	setModel(model);
}

GameObject::~GameObject()
{
	delete vao;
	delete model;
}


void GameObject::updatePosition(glm::vec3 dPos) {
	this->position += dPos;
}


glm::mat4x4 GameObject::getModelMatrix() {
	glm::mat4x4 translate = glm::translate(glm::mat4x4(), position);
	glm::mat4x4 rotateX = glm::rotate(glm::mat4x4(), rotation.x, glm::vec3(1, 0, 0));
	glm::mat4x4 rotateY = glm::rotate(glm::mat4x4(), rotation.y, glm::vec3(0, 1, 0));
	glm::mat4x4 rotateZ = glm::rotate(glm::mat4x4(), rotation.z, glm::vec3(0, 0, 1));
	return translate * rotateX * rotateY * rotateZ;
}


void GameObject::updateRotation(glm::vec3 angles) {
	this->rotation += angles;
}