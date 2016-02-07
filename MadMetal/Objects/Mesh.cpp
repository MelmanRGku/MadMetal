#include "Mesh.h"


Mesh::~Mesh()
{
}


void Mesh::setupVAO() {
	long cBufferSize = colours.size() * sizeof(glm::vec3),
		vBufferSize = vertices.size() * sizeof(glm::vec3),
		nBufferSize = normals.size() * sizeof(glm::vec3),
		uvBufferSize = uvs.size() * sizeof(glm::vec2);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//create and bind the VBO
	glGenBuffers(ShaderProgram::TOTAL_NUMBER_OF_ATTRIBUTES, vbo);
	glGenBuffers(1, &ebo);

	// Load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, vbo[ShaderProgram::POSITION_ATTRIBUTE_LOCATION]);
	// Allocate buffer
	glBufferData(GL_ARRAY_BUFFER, vBufferSize, &vertices[0],
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(ShaderProgram::POSITION_ATTRIBUTE_LOCATION);
	glVertexAttribPointer(ShaderProgram::POSITION_ATTRIBUTE_LOCATION, 3, GL_FLOAT, 0, GL_FALSE,
		(const GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[ShaderProgram::COLOUR_ATTRIBUTE_LOCATION]);
	glBufferData(GL_ARRAY_BUFFER, cBufferSize, &colours[0],
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(ShaderProgram::COLOUR_ATTRIBUTE_LOCATION);
	glVertexAttribPointer(ShaderProgram::COLOUR_ATTRIBUTE_LOCATION, 3, GL_FLOAT, 0, GL_FALSE,
		(const GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[ShaderProgram::NORMAL_ATTRIBUTE_LOCATION]);
	glBufferData(GL_ARRAY_BUFFER, nBufferSize, &normals[0],
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(ShaderProgram::NORMAL_ATTRIBUTE_LOCATION);
	glVertexAttribPointer(ShaderProgram::NORMAL_ATTRIBUTE_LOCATION, 3, GL_FLOAT, 0, GL_FALSE,
		(const GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[ShaderProgram::UV_ATTRIBUTE_LOCATION]);
	glBufferData(GL_ARRAY_BUFFER, uvBufferSize, &uvs[0],
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(ShaderProgram::UV_ATTRIBUTE_LOCATION);
	glVertexAttribPointer(ShaderProgram::UV_ATTRIBUTE_LOCATION, 2, GL_FLOAT, 0, GL_FALSE,
		(const GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}