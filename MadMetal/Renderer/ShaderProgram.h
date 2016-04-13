#pragma once

#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtc\type_ptr.hpp"
#include "../Libraries/glew/glew.h"
#include "../Global/Log.h"
#include "ShaderLoader.h"
#include <iostream>

#define MAX_NUM_OF_LIGHTS 70

class Light;

class ShaderProgram
{
public:
	static const GLuint POSITION_ATTRIBUTE_LOCATION = 0,
		COLOUR_ATTRIBUTE_LOCATION = 1,
		NORMAL_ATTRIBUTE_LOCATION = 2,
		UV_ATTRIBUTE_LOCATION = 3,
		TOTAL_NUMBER_OF_ATTRIBUTES = 4;

	ShaderProgram();
	~ShaderProgram();
	virtual void start(glm::mat4x4 *viewMatrix, glm::mat4x4 *projMatrix, glm::vec3 *cameraPos, std::vector<Light *> *lights) {}
	virtual void end() {}

	GLfloat lightPositions[MAX_NUM_OF_LIGHTS * 3];
	GLfloat lightColours[MAX_NUM_OF_LIGHTS * 3];
	GLfloat lightCutoffs[MAX_NUM_OF_LIGHTS];

	GLfloat lightConstants[MAX_NUM_OF_LIGHTS];
	GLfloat lightLinears[MAX_NUM_OF_LIGHTS];
	GLfloat lightQuads[MAX_NUM_OF_LIGHTS];

};

