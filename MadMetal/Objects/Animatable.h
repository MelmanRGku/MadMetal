#pragma once

#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtc\matrix_transform.hpp"

class Animatable
{
public:
	Animatable();
	virtual ~Animatable();

	glm::mat4x4 getModelMatrix() {
		glm::mat4x4 translate = glm::translate(glm::mat4x4(), position);
		glm::mat4x4 rotateX = glm::rotate(glm::mat4x4(), rotation.x, glm::vec3(1, 0, 0));
		glm::mat4x4 rotateY = glm::rotate(glm::mat4x4(), rotation.y, glm::vec3(0, 1, 0));
		glm::mat4x4 rotateZ = glm::rotate(glm::mat4x4(), rotation.z, glm::vec3(0, 0, 1));
		glm::mat4x4 scaleMat = glm::scale(glm::mat4x4(), this->scale);
		glm::mat4x4 res = translate * rotateX * rotateY * rotateZ * scaleMat;
		return res;
	}

	glm::vec3 getScale() { return scale; }
	void setPosition(glm::vec3 pos) { position = pos; }
	void setScale(glm::vec3 sc) { scale = sc; }
	void setRotation(glm::vec3 rot) { rotation = rot; }
	void updateRotation(glm::vec3 dr) { rotation += dr; }
	void updatePosition(glm::vec3 dp) { position += dp; }
	void updateScale(glm::vec3 ds) { scale += ds; }
	glm::vec3  getPosition(){ return position; }

protected:
	glm::vec3 position, rotation, scale;
	
};