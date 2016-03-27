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
	glm::mat4x4 projectionMatrix, viewMatrix, modelMatrix;
	ShaderProgram *shader[NUMBER_OF_SHADER_TYPES];
	std::vector<glm::vec4> viewPorts;
	std::vector<PlayerControllable *> *players;

public:
	Renderer();
	~Renderer();
	void setShader(ShaderType type, ShaderProgram *sp);
	void draw(std::vector<TestObject *> *objects);
	void setViewMatrixLookAt(std::vector<Camera *> cameras);
	void setViewMatrixLookAt(glm::vec3 pos, glm::vec3 up, glm::vec3 lookAt);
	void initializeScreens(int numOfPlayers);
	void setPlayers(std::vector<PlayerControllable *> *players) { this->players = players; };
	ShaderProgram *getShaderProgram(ShaderType type) { return shader[type]; }
	glm::mat4x4 getProjectionMatrix() { return projectionMatrix; }
	glm::mat4x4 getViewMatrix() { return viewMatrix; }
};

