#pragma once

#include "ShaderProgram.h"

class NoShaderProgram : public ShaderProgram
{
public:
	NoShaderProgram();
	~NoShaderProgram();
	void start(glm::mat4x4 *viewMatrix, glm::mat4x4 *projMatrix);
	void end();
};

