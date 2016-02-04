#include "Renderer.h"

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
		100.f
		);

	viewMatrix = glm::lookAt(
		glm::vec3(30, 30, 30),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
		);

	modelMatrix = glm::mat4x4();
}


Renderer::~Renderer()
{
}

/*
	Draws a obj model
*/
void Renderer::draw(GameObject *object) {
	glm::mat4x4 m = glm::mat4x4(1.0f);
	glUniformMatrix4fv(shader->modelMatrixUniform, 1, false, &m[0][0]);
	glUniform1i(shader->textureValidUniform, true);
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

	object->mesh->Render();

}


void Renderer::draw(std::vector<GameObject *> *objects) {
	startDrawing();
	for (unsigned int i = 0; i < objects->size(); i++) {
		draw(objects->at(i));
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