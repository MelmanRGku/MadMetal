#pragma once

#include "Libraries\glew\glew.h"
#include "Libraries\glm\vec3.hpp"
#include "Libraries\glm\vec2.hpp"
#include "Texture.h"
#include "Renderer/ShaderProgram.h"
#include <vector>

class Mesh
{
private:
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec4> colours;
	std::vector<glm::vec3> normals;
	std::vector<GLuint> indices;
	std::vector<glm::vec3> vertices;
	GLuint vao, vbo[ShaderProgram::TOTAL_NUMBER_OF_ATTRIBUTES], ebo;
	Texture *texture;
public:
	Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec4> colours, std::vector<glm::vec3> normals, std::vector<GLuint> indices, Texture *texture) : vertices(vertices), uvs(uvs), colours(colours), normals(normals), texture(texture), indices(indices) {}
	~Mesh();
	bool hasTexture() { return texture != NULL; }
	Texture *getTexture() { return texture; }
	std::vector<GLuint> *getIndices() { return &indices; }
	std::vector<glm::vec3> *getVertices() { return &vertices; }
	void setupVAO();
	GLuint getVAO() { return vao; }
};

