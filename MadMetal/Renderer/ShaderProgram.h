#pragma once

#include "ShaderLoader.h"
#include "../Libraries/glew/glew.h"
#include "../Global/Debug.h"

class ShaderProgram
{
private:
	GLuint programID;
public:
	ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	~ShaderProgram();
};

