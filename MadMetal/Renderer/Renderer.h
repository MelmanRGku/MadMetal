#pragma once

#include "..\Libraries\glm\mat4x4.hpp"
#include "..\Libraries\glm\gtc\matrix_transform.hpp"
#include "..\Global\Settings.h"
//#include "..\Objects\RenderableObject.h"
#include "Objects\TestObject.h"
#include "ShaderProgram.h"

class TestObject;
class Camera;

class Renderer
{
private:
	glm::mat4x4 projectionMatrix, viewMatrix, modelMatrix;
	ShaderProgram *shader;
public:
	Renderer();
	~Renderer();
	void setShader(ShaderProgram *sp) { shader = sp; }
	void draw(TestObject *object);
	void draw(std::vector<TestObject *> *objects);
	void setViewMatrixLookAt(std::vector<Camera *> cameras);
	void setViewMatrixLookAt(glm::vec3 pos, glm::vec3 up, glm::vec3 lookAt);
	void startDrawing();
	void stopDrawing();
	ShaderProgram *getShaderProgram() { return shader; }
};

