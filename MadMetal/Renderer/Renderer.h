#pragma once

#include "..\Libraries\glm\mat4x4.hpp"
#include "..\Libraries\glm\gtc\matrix_transform.hpp"
#include "..\Global\Settings.h"
#include "CellShaderProgram.h"
#include "NoShaderProgram.h"

class TestObject;
class Camera;

class Renderer
{
public:
	enum ShaderType {
		SHADER_TYPE_CELL,
		SHADER_TYPE_NONE,
		NUMBER_OF_SHADER_TYPES
	};

private:
	glm::mat4x4 projectionMatrix, viewMatrix, modelMatrix;
	ShaderProgram *shader[NUMBER_OF_SHADER_TYPES];

public:
	Renderer();
	~Renderer();
	void setShader(ShaderType type, ShaderProgram *sp);
	void draw(std::vector<TestObject *> *objects);
	void setViewMatrixLookAt(std::vector<Camera *> cameras);
	void setViewMatrixLookAt(glm::vec3 pos, glm::vec3 up, glm::vec3 lookAt);
	ShaderProgram *getShaderProgram(ShaderType type) { return shader[type]; }
};

