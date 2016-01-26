#include "Model.h"


Model::Model()
{
}

Model::~Model()
{
}

/*
Clears all the information about the model:
vertices, normals, colours and uvs
*/
void Model::clearInfo() {
	vertices.clear();
	uvs.clear();
	normals.clear();
	colours.clear();
}

/*
Sets the colour for all vertices to some value
*/
void Model::setColour(glm::vec3 colour) {
	colours.clear();
	for (int i = 0; i < vertices.size(); i++) {
		colours.push_back(glm::vec3(colour));
	}
}

/*
@Overload
*/
void Model::setColour(float r, float g, float b){
	setColour(glm::vec3(r, g, b));
}