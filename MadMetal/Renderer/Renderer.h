#pragma once

#include "..\Libraries\glm\mat4x4.hpp"
#include "..\Libraries\glm\gtc\matrix_transform.hpp"
#include "..\Global\Settings.h"
#include "CellShaderProgram.h"
#include "NoShaderProgram.h"

class PlayerControllable;
class TestObject;
class Camera;

class Renderer
{
public:
	enum ShaderType {
		SHADER_TYPE_NONE,
		SHADER_TYPE_CELL,
		SHADER_TYPR_CELLTIRE,
		NUMBER_OF_SHADER_TYPES
	};

private:
	glm::mat4x4 projectionMatrix, viewMatrix, defaultProjectionMatrix;
	ShaderProgram *shader[NUMBER_OF_SHADER_TYPES];
	std::vector<std::vector<glm::vec4>> viewPorts;
	float windowWidth, windowHeight;
	glm::vec4 currentViewPort;
	int totalNumberOfViewPorts;

public:
	Renderer();
	~Renderer();
	void setShader(ShaderType type, ShaderProgram *sp);
	void draw(std::vector<TestObject *> *objects, std::vector<PlayerControllable *> *players = NULL);
	void setViewMatrixLookAt(std::vector<Camera *> cameras);
	void setViewMatrixLookAt(glm::vec3 pos, glm::vec3 up, glm::vec3 lookAt);
	ShaderProgram *getShaderProgram(ShaderType type) { return shader[type]; }
	glm::mat4x4 getProjectionMatrix() { return projectionMatrix; }
	glm::mat4x4 getViewMatrix() { return viewMatrix; }
	void recalculateViewPorts(float windowWidth, float windowHeight);
	glm::vec4 getCurrentViewPort() { return currentViewPort; }
	int getTotalNumberOfViewPorts() { return totalNumberOfViewPorts; }
};

