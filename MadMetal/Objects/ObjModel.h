#pragma once

#include <vector>
#include "../Libraries/glm/vec3.hpp"
#include "../Libraries/glm/vec2.hpp"
#include "../Global/Log.h"
#include "../Libraries/glew/glew.h"

class ObjModel
{
private:
	void clearInfo();
	void parseObjFile(const char* fileName);
	void setupVBO();
public:
	std::vector<glm::vec3> vertices, normals, colours;
	std::vector<glm::vec2> uvs;
	GLuint vbo;

	ObjModel();
	~ObjModel();
	void loadFromFile(const char* fileName);
	void setColour(float r, float g, float b);
	void setColour(glm::vec3 colour);
};

