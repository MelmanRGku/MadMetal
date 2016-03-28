#pragma once

#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtc\type_ptr.hpp"
#include "../Libraries/glew/glew.h"
#include "../Global/Log.h"
#include "ShaderLoader.h"

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
	virtual void start(glm::mat4x4 *viewMatrix, glm::mat4x4 *projMatrix, glm::vec3 *cameraPos) {}
	virtual void end() {}
};

