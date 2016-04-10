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
		lightUniform,
		cutoffUniform;

	GLfloat lightPositions[32 * 3];
	GLfloat lightColours[32 * 3];
	GLfloat lightCutoffs[32];

	GLfloat lightConstants[32];
	GLfloat lightLinears[32];
	GLfloat lightQuads[32];

	GLuint lightPosDynamic,
	constDynamic,
	linearDynamic,
	quadDynamic,
	lightDynamic,
	cutoffDynamic;

	CellShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	~CellShaderProgram();
	void start(glm::mat4x4 *viewMatrix, glm::mat4x4 *projMatrix, glm::vec3 *cameraPos, std::vector<Light *> *thelights = NULL);
	void end();
};

