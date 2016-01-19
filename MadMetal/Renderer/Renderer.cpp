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
		glm::vec3(15, 0, 15),
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
void Renderer::draw(ObjModel *model) {
	long cBufferSize = model->colours.size() * sizeof(glm::vec3),
		vBufferSize = model->vertices.size() * sizeof(glm::vec3),
		nBufferSize = model->normals.size() * sizeof(glm::vec3);

	//set model matrix uniform
	glUniformMatrix4fv(shader->modelMatrixUniform, 1, false, &modelMatrix[0][0]);
	
	//we want to use color for now. Textures not supported yet
	glUniform1i(shader->textureValidUniform, false);

	// Bind to the correct context
	glBindBuffer(GL_ARRAY_BUFFER, model->vbo);

	// Enable the attribute arrays
	glEnableVertexAttribArray(shader->positionAttribute);
	glEnableVertexAttribArray(shader->colourAttribute);
	glEnableVertexAttribArray(shader->normalAttribute);
	glEnableVertexAttribArray(shader->uvAttribute);

	// Specifiy where these are in the VBO
	glVertexAttribPointer(shader->positionAttribute, 3, GL_FLOAT, 0, GL_FALSE,
		(const GLvoid*)0);

	glVertexAttribPointer(shader->colourAttribute, 3, GL_FLOAT, 0, GL_FALSE,
		(const GLvoid*)(vBufferSize));

	glVertexAttribPointer(shader->normalAttribute, 3, GL_FLOAT, 0, GL_FALSE,
		(const GLvoid*)(vBufferSize + cBufferSize));

	glVertexAttribPointer(shader->uvAttribute, 2, GL_FLOAT, 0, GL_FALSE,
		(const GLvoid*)(vBufferSize + cBufferSize + nBufferSize));

	// Draw the triangles
	glDrawArrays(GL_TRIANGLES, 0, model->vertices.size());

	// Disable attribute arrays
	glDisableVertexAttribArray(shader->positionAttribute);
	glDisableVertexAttribArray(shader->colourAttribute);
	glDisableVertexAttribArray(shader->normalAttribute);
	glDisableVertexAttribArray(shader->uvAttribute);
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