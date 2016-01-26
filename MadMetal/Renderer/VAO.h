#pragma once

#include "../Libraries/glew/glew.h"
#include "ShaderProgram.h"
#include "../Objects/Model.h"

class VAO
{
private:
	GLuint vao;
	GLuint vbo[ShaderProgram::TOTAL_NUMBER_OF_ATTRIBUTES];

public:
	VAO();
	VAO(Model *model);
	~VAO();
	GLuint getVaoId() { return vao; }
	void setupVao(Model *model);
};

