#include "VAO.h"


VAO::VAO()
{
}

VAO::VAO(Model *model) {
	setupVao(model);
}


VAO::~VAO()
{
}


void VAO::setupVao(Model *model) {
	long cBufferSize = model->colours.size() * sizeof(glm::vec3),
		vBufferSize = model->vertices.size() * sizeof(glm::vec3),
		nBufferSize = model->normals.size() * sizeof(glm::vec3),
		uvBufferSize = model->uvs.size() * sizeof(glm::vec2);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//create and bind the VBO
	glGenBuffers(ShaderProgram::TOTAL_NUMBER_OF_ATTRIBUTES, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[ShaderProgram::POSITION_ATTRIBUTE_LOCATION]);
	// Allocate buffer
	glBufferData(GL_ARRAY_BUFFER, vBufferSize, &model->vertices[0],
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(ShaderProgram::POSITION_ATTRIBUTE_LOCATION);
	glVertexAttribPointer(ShaderProgram::POSITION_ATTRIBUTE_LOCATION, 3, GL_FLOAT, 0, GL_FALSE,
		(const GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[ShaderProgram::COLOUR_ATTRIBUTE_LOCATION]);
	glBufferData(GL_ARRAY_BUFFER, cBufferSize, &model->colours[0],
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(ShaderProgram::COLOUR_ATTRIBUTE_LOCATION);
	glVertexAttribPointer(ShaderProgram::COLOUR_ATTRIBUTE_LOCATION, 3, GL_FLOAT, 0, GL_FALSE,
		(const GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[ShaderProgram::NORMAL_ATTRIBUTE_LOCATION]);
	glBufferData(GL_ARRAY_BUFFER, nBufferSize, &model->normals[0],
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(ShaderProgram::NORMAL_ATTRIBUTE_LOCATION);
	glVertexAttribPointer(ShaderProgram::NORMAL_ATTRIBUTE_LOCATION, 3, GL_FLOAT, 0, GL_FALSE,
		(const GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[ShaderProgram::UV_ATTRIBUTE_LOCATION]);
	glBufferData(GL_ARRAY_BUFFER, uvBufferSize, &model->uvs[0],
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(ShaderProgram::UV_ATTRIBUTE_LOCATION);
	glVertexAttribPointer(ShaderProgram::UV_ATTRIBUTE_LOCATION, 2, GL_FLOAT, 0, GL_FALSE,
		(const GLvoid*)0);

	glBindVertexArray(0);
}