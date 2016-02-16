#include "Model.h"


Model::Model()
{
}


Model::~Model()
{
	delete boundingBox;
}


void Model::setupVAOs() {

	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes.at(i)->setupVAO();
	}

}
