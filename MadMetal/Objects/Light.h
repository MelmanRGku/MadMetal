#pragma once

#include "Libraries\glew\glew.h"
#include "Libraries\glm\vec3.hpp"
#include "TestObject.h"

class Light : public TestObject
{
public:
	Light(long id, Animatable *anable);

	virtual void update(float dt);
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) { return false; }
	glm::mat4x4 getModelMatrix(){ return glm::mat4x4(); }
	void playSound(){}
	
	glm::vec3 colour;
	GLfloat cutoff;

	GLfloat constant;
	GLfloat linear;
	GLfloat quad;
	
	virtual bool getParentHasToBeDeleted();
	
};