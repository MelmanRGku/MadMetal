#pragma once

#include "ShaderLoader.h"
#include "../Libraries/glew/glew.h"
#include "../Global/Log.h"

class ShaderProgram
{
private:
public:
	GLuint programID,					//ID of the program
		positionAttribute,				//vertex position attribute
		normalAttribute,				//vertex normal attribute
		colourAttribute,				//vertex colour attribute
		uvAttribute,					//vertex uv attribute
		projectionMatrixUniform,		//projection matrix uniform
		viewMatrixUniform,				//view matrix uniform
		modelMatrixUniform,				//model matrix uniform
		textureUniform,					//texture uniform
		textureValidUniform;			//uniform that specifies if there is any texture loaded or if color should be used instead

	ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	~ShaderProgram();
};

