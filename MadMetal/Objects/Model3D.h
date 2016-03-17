#pragma once

#include "Model.h"
#include "Mesh.h"
#include "BoundingBox.h"
#include <vector>
#include "Simulation\PhysicsManager.h"

class Model3D : public Model
{
private:
	std::vector<Mesh *> meshes;
	bool vaoSetup = false;
public:
	BoundingBox *boundingBox;

	Model3D();
	~Model3D();
	void addMesh(Mesh *mesh) { meshes.push_back(mesh); }
	std::vector<Mesh *> *getMeshes() { return &meshes; }
	void setupVAOs();
	PxTriangleMesh **getPhysicsTriangleMesh();
	void setAlpha(float alpha);
};

