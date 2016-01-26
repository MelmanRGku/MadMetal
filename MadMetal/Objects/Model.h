#pragma once

#include <vector>
#include "../Libraries/glm/vec3.hpp"
#include "../Libraries/glm/vec2.hpp"

class Model
{
protected:
	void clearInfo();
public:
	std::vector<glm::vec3> vertices, normals, colours;
	std::vector<glm::vec2> uvs;

	Model();
	~Model();
	virtual void loadFromFile(const char* fileName) = 0;
	void setColour(float r, float g, float b);
	void setColour(glm::vec3 colour);
};

