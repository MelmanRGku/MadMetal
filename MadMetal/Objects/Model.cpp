#include "Model.h"


Model::Model()
{
	meshes = std::vector<Mesh *>();
}


Model::~Model()
{
	delete boundingBox;
}


void Model::setupVAOs() {

	if (!meshes.empty())
		for (unsigned int i = 0; i < meshes.size(); i++) {
			meshes.at(i)->setupVAO();
		}

}
