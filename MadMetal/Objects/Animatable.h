#pragma once

#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtc\matrix_transform.hpp"

class Animatable
{
public:
	Animatable() {
		scale = glm::vec3(1, 1, 1);
		modelMatrix = glm::mat4x4(1.0f);
	}
	virtual ~Animatable() {}

	glm::mat4x4 getModelMatrix() { return modelMatrix; }
	glm::vec3 getScale() { return scale; }
	void setPosition(glm::vec3 pos) { position = pos; recalculateModelMatrix(); }
	void setScale(glm::vec3 sc) { scale = sc; recalculateModelMatrix(); }
	void setRotation(glm::vec3 rot) { rotation = rot; recalculateModelMatrix(); }
	void updateRotation(glm::vec3 dr) { rotation += dr; recalculateModelMatrix(); }
	void updatePosition(glm::vec3 dp) { position += dp; recalculateModelMatrix(); }
	void updateScale(glm::vec3 ds) { scale += ds; recalculateModelMatrix(); }
	glm::vec3 getRotation() { return rotation; }
	glm::vec3  getPosition(){ return position; }
	void recalculateModelMatrix() {
		glm::mat4x4 translate = glm::translate(glm::mat4x4(), position);
		glm::mat4x4 rotateX = glm::rotate(glm::mat4x4(), rotation.x, glm::vec3(1, 0, 0));
		glm::mat4x4 rotateY = glm::rotate(glm::mat4x4(), rotation.y, glm::vec3(0, 1, 0));
		glm::mat4x4 rotateZ = glm::rotate(glm::mat4x4(), rotation.z, glm::vec3(0, 0, 1));
		glm::mat4x4 scaleMat = glm::scale(glm::mat4x4(), this->scale);
		modelMatrix = translate * rotateX * rotateY * rotateZ * scaleMat;
	}

protected:
	glm::vec3 position, rotation, scale;
	glm::mat4x4 modelMatrix;
	
};