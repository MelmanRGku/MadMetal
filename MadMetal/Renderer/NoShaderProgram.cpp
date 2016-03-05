#include "NoShaderProgram.h"


NoShaderProgram::NoShaderProgram()
{
}


NoShaderProgram::~NoShaderProgram()
{
}


void NoShaderProgram::start(glm::mat4x4 *viewMatrix, glm::mat4x4 *projMatrix) {
	glUseProgram(0);
}


void NoShaderProgram::end() {
	glUseProgram(0);
}