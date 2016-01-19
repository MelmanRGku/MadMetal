#pragma once

#include "..\Libraries\glm\mat4x4.hpp"
#include "..\Libraries\glm\gtc\matrix_transform.hpp"
#include "..\Global\Settings.h"
#include "..\Objects\ObjModel.h"
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
	void draw(ObjModel *model);
	void startDrawing();
	void stopDrawing();
};

