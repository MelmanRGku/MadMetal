#pragma once

#include "Mesh.h"
#include <vector>

class Model
{
private:
	std::vector<Mesh *> meshes;
public:
	Model();
	~Model();
	void addMesh(Mesh *mesh) { meshes.push_back(mesh); }
	std::vector<Mesh *> *getMeshes() { return &meshes; }
};

