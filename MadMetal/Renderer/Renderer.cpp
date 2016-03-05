#include "Renderer.h"
#include <FTGL/ftgl.h>
#include "Global\Fonts.h"
#include "Objects\Camera.h"
#include "Objects\TestObject.h"

/*
	Constructor. 
	TODO: definitely change this. This was done for testing purposes
*/
Renderer::Renderer()
{
	projectionMatrix = glm::perspective(
		glm::radians(std::stof(Settings::getSetting("fovy"))),
		std::stof(Settings::getSetting("screenWidth")) / std::stof(Settings::getSetting("screenHeight")),
		0.5f,
		10000.f
		);

	viewMatrix = glm::lookAt(
		glm::vec3(50, 3, 50),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
		);

	modelMatrix = glm::mat4x4();
}


Renderer::~Renderer()
{
}

void Renderer::setShader(ShaderType type, ShaderProgram *sp) {
	shader[type] = sp;
}

void Renderer::setViewMatrixLookAt(glm::vec3 pos, glm::vec3 up, glm::vec3 lookAt)
{
	viewMatrix = glm::lookAt(
		pos,
		lookAt,
		up
		);
}

//todo: split screen
void Renderer::setViewMatrixLookAt(std::vector<Camera *> cameras)
{
	//currently will just get the first camera in the list and set view matrix to that
	viewMatrix = glm::lookAt(
		cameras[0]->getPosition(),
		cameras[0]->getLookAt(),
		cameras[0]->getUpVector()
	);
}

/*void Renderer::draw(ParticleSystem * sys)
{
	startDrawing();
	//set model matrix uniform
	glUniformMatrix4fv(shader->modelMatrixUniform, 1, false, &modelMatrix[0][0]);

	glUniformMatrix4fv(shader->viewMatrixUniform, 1, false, &viewMatrix[0][0]);

	//we want to use color for now. Textures not supported yet
	glUniform1i(shader->textureValidUniform, false);

	// Bind to the correct context
	glBindVertexArray(sys->m_vao);

	// Draw the triangles
	glPointSize(2);
	glDrawArrays(GL_POINTS, 0, sys->p->m_countAlive);

	glBindVertexArray(0);
	stopDrawing();
}*/


void Renderer::draw(std::vector<TestObject *> *objects) {
	for (int i = 0; i < NUMBER_OF_SHADER_TYPES; i++) {
		if (shader[i] != NULL) {
			shader[i]->start(&viewMatrix, &projectionMatrix);
			int passNumber = 1; bool keepGoing;
			do {
				keepGoing = false;
				for (unsigned int j = 0; j < objects->size(); j++) {
					TestObject *obj = objects->at(j);
					keepGoing = keepGoing || obj->draw(this, (ShaderType)i, passNumber);
				}
				passNumber++;
			} while (keepGoing);
			shader[i]->end();
		}
	}
}