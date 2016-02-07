#pragma once

#include "..\Libraries\glm\mat4x4.hpp"
#include "..\Libraries\glm\gtc\matrix_transform.hpp"
#include "..\Global\Settings.h"
#include "..\Objects\RenderableObject.h"
#include "Renderable.h"
#include "ShaderProgram.h"

class RenderableObject;

class Renderer
{
private:
	glm::mat4x4 projectionMatrix, viewMatrix, modelMatrix;
	ShaderProgram *shader;
public:
	Renderer();
	~Renderer();
	void setShader(ShaderProgram *sp) { shader = sp; }
	void draw(Renderable *object);
	void draw(std::vector<Object *> *objects);
	void startDrawing();
	void stopDrawing();
	ShaderProgram *getShaderProgram() { return shader; }
};

