#pragma once

#include "..\Libraries\glm\mat4x4.hpp"
#include "..\Libraries\glm\gtc\matrix_transform.hpp"
#include "..\Global\Settings.h"
#include "..\Objects\GameObject.h"
#include "..\ParticleSystem\ParticleSystem.h"
#include "ShaderProgram.h"

class Renderer
{
private:
	glm::mat4x4 projectionMatrix, viewMatrix, modelMatrix;
	ShaderProgram *shader;
public:
	Renderer();
	~Renderer();
	void setShader(ShaderProgram *sp) { shader = sp; }
	void draw(GameObject *object);
	void draw(ParticleSystem * sys);
	void draw(std::vector<GameObject *> *objects);
	void startDrawing();
	void stopDrawing();
};

