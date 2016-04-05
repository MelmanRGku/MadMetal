#pragma once

#include "Libraries\glew\glew.h"
#include "Libraries\glm\vec3.hpp"
#include "Libraries\glm\vec2.hpp"
#include "Texture.h"
#include "Renderer/ShaderProgram.h"
#include <vector>

class NavigationalGrid
{
private:
	std::vector<glm::vec3> m_vertices;
	std::vector<std::vector<unsigned int>> m_faces;
	int m_numOfQuads;
public:
	NavigationalGrid(std::vector<glm::vec3> vertices, std::vector<std::vector<unsigned int>> faces, int numOfQuads);
	~NavigationalGrid();

	std::vector<glm::vec3> *getVertices();
	std::vector<std::vector<unsigned int>> *getFaces();
	int getNumOfQuads();
};

