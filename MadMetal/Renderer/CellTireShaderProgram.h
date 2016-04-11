#pragma once

#include "ShaderProgram.h"

class CellTireShaderProgram : public ShaderProgram
{
private:
public:

	GLuint programID,					//ID of the program
		projectionMatrixUniform,		//projection matrix uniform
		viewMatrixUniform,				//view matrix uniform
		modelMatrixUniform,				//model matrix uniform
		textureUniform,					//texture uniform
		textureValidUniform,			//uniform that specifies if there is any texture loaded or if color should be used instead
		cameraPosUniform,				//pos of the camera
		distanceTraveledUniform,		//uniform that specifies the distance the player has traveled, used to determine rotation of the tires.

		bitmaskUniform,
		lightPosUniform,
		constUniform,
		linearUniform,
		quadUniform,
		lightUniform,
		cutoffUniform;

	CellTireShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	~CellTireShaderProgram();
	void start(glm::mat4x4 *viewMatrix, glm::mat4x4 *projMatrix, glm::vec3 *cameraPos, std::vector<Light *> *thelights = NULL);
	void end();
	void loadLights(std::vector<Light *> *lights);
};

