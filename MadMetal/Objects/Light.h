#pragma once

#include "Libraries\glew\glew.h"
#include "Libraries\glm\vec3.hpp"


class TestObject;


class Light
{
public:
	Light(TestObject * myObject, float maximumLife = -1, float totallife = 0);
	TestObject * m_object;
	bool hasToBeDeleted = false;
	
	glm::vec3 dynamicColour;
	GLfloat dynamicCutoff;

	GLfloat dynamicConstant;
	GLfloat dynamicLinear;
	GLfloat dynamicQuad;
	
	TestObject * getObject();
	glm::vec3 getPosition();
	
};