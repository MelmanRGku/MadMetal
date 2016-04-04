#pragma once

#include "ShaderProgram.h"

class CellShaderProgram : public ShaderProgram
{
private:
public:
	
	GLuint programID,					//ID of the program
		projectionMatrixUniform,		//projection matrix uniform
		viewMatrixUniform,				//view matrix uniform
		modelMatrixUniform,				//model matrix uniform
		textureUniform,					//texture uniform
		textureValidUniform,			//uniform that specifies if there is any texture loaded or if color should be used instead
		cameraPosUniform,

		bitmaskUniform,		//pos of the camera
		lightPosUniform,
		constUniform,
		linearUniform,
		quadUniform,
		lightUniform;

	CellShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	~CellShaderProgram();
	void start(glm::mat4x4 *viewMatrix, glm::mat4x4 *projMatrix, glm::vec3 *cameraPos);
	void end();
};

