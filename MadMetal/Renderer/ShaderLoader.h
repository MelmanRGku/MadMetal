#pragma once

#include "..\Libraries\glew\glew.h"
#include "..\Files\FileReader.h"
#include "..\Global\Debug.h"
#include <string>
#include <vector>

class ShaderLoader
{
public:
	ShaderLoader();
	~ShaderLoader();
	GLuint loadShaders(const char* vertexShaderPath, const char* fragmentShaderPath);
};

