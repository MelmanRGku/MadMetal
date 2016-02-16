#pragma once

#include "Mesh.h"
#include "BoundingBox.h"
#include <vector>

class Model
{
private:
	std::vector<Mesh *> meshes;
public:
	BoundingBox *boundingBox;

	Model();
	~Model();
	void addMesh(Mesh *mesh) { meshes.push_back(mesh); }
	std::vector<Mesh *> *getMeshes() { return &meshes; }
	void setupVAOs();
};

