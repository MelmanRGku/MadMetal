#include "Renderer.h"
#include <FTGL/ftgl.h>
#include "Global\Fonts.h"

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
	//std::cout << cameras[0]->getLookAt().x << "," << cameras[0]->getLookAt().z << std::endl;
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

/*
	Draws a obj model
*/
void Renderer::draw(Renderable *object) {
	/*if (!object->isRenderable())
		return;

	long cBufferSize = object->model->colours.size() * sizeof(glm::vec3),
		vBufferSize = object->model->vertices.size() * sizeof(glm::vec3),
		nBufferSize = object->model->normals.size() * sizeof(glm::vec3);

	//set model matrix uniform
	glUniformMatrix4fv(shader->modelMatrixUniform, 1, false, &object->getModelMatrix()[0][0]);
	
	//we want to use color for now. Textures not supported yet
	glUniform1i(shader->textureValidUniform, false);

	// Bind to the correct context
	glBindVertexArray(object->vao->getVaoId());

	// Draw the triangles
	glDrawArrays(GL_TRIANGLES, 0, object->model->vertices.size());

	glBindVertexArray(0);*/

	object->draw(this);

}


void Renderer::draw(std::vector<Object *> *objects) {
	startDrawing();
	for (unsigned int i = 0; i < objects->size(); i++) {
		Object *obj = objects->at(i);
		Renderable *robj = dynamic_cast<Renderable *>(obj);
		if (robj) {
			draw(robj);
		}
	}
	stopDrawing();
}

/*
	Performs the setup for drawing. 
	Has to be called before the draw() method
*/
void Renderer::startDrawing() {
	//tether the program
	glUseProgram(shader->programID);

	//set view and projection matrices
	glUniformMatrix4fv(shader->viewMatrixUniform, 1, false, &viewMatrix[0][0]);
	glUniformMatrix4fv(shader->projectionMatrixUniform, 1, false, &projectionMatrix[0][0]);
}

/*
	Performs the cleanup after drawing
	Has to be called after drawing process is done
*/
void Renderer::stopDrawing() {
	glUseProgram(0);
}