#pragma once

#include "ShaderLoader.h"
#include "../Libraries/glew/glew.h"
#include "../Global/Log.h"

class ShaderProgram
{
private:
public:
	static const GLuint POSITION_ATTRIBUTE_LOCATION = 0,
		COLOUR_ATTRIBUTE_LOCATION = 1,
		NORMAL_ATTRIBUTE_LOCATION = 2,
		UV_ATTRIBUTE_LOCATION = 3,
		TOTAL_NUMBER_OF_ATTRIBUTES = 4;
	GLuint programID,					//ID of the program
		projectionMatrixUniform,		//projection matrix uniform
		viewMatrixUniform,				//view matrix uniform
		modelMatrixUniform,				//model matrix uniform
		textureUniform,					//texture uniform
		textureValidUniform;			//uniform that specifies if there is any texture loaded or if color should be used instead

	ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	~ShaderProgram();
};

