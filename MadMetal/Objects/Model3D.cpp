#include "Model3D.h"

Model3D::Model3D()
{
}


Model3D::~Model3D()
{
	delete boundingBox;
	for (unsigned int i = 0; i < meshes.size(); i++) {
		delete meshes[i];
	}
}


void Model3D::setupVAOs() {

	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes.at(i)->setupVAO();
	}

}


PxTriangleMesh **Model3D::getPhysicsTriangleMesh() {
	if (meshes.size() == 0)
		return NULL;

	PxTriangleMesh **physicalMeshes = new PxTriangleMesh *[meshes.size()];

	int meshIndex = 0;
	for (unsigned int i = 0; i < meshes.size(); i++) {
		// Create descriptor for convex mesh
		PxTriangleMeshDesc description;
		description.points.count = meshes.at(i)->getVertices()->size();
		description.triangles.count = meshes.at(i)->getIndices()->size() / 3;
		description.points.stride = sizeof(PxVec3);
		description.triangles.stride = 3 * sizeof(PxU32);

		PxVec3 *verts = new PxVec3[meshes.at(i)->getVertices()->size()];
		PxU32 *indices = new PxU32[meshes.at(i)->getIndices()->size()];

		std::vector<glm::vec3> *vertices = meshes.at(i)->getVertices();
		for (unsigned int j = 0; j < vertices->size(); j++) {
			glm::vec3 vertex = vertices->at(j);
			verts[j] = PxVec3(vertex.x, vertex.y, vertex.z);
		}

		for (unsigned int j = 0; j < meshes.at(i)->getIndices()->size(); j++) {
			indices[j] = meshes.at(i)->getIndices()->at(j);
		}

		description.points.data = verts;
		description.triangles.data = indices;

		PxTriangleMesh* triangleMesh = NULL;
		PxDefaultMemoryOutputStream buf;
		if (PhysicsManager::getCookingInstance().cookTriangleMesh(description, buf))
		{
			//std::cout << "created the triangle mesh \n";
			PxDefaultMemoryInputData id(buf.getData(), buf.getSize());
			triangleMesh = PhysicsManager::getPhysicsInstance().createTriangleMesh(id);
			physicalMeshes[meshIndex] = triangleMesh;
			meshIndex++;
		}
		else {
			exit(7);
		}

		delete[] verts;
		delete[] indices;

	}


	return physicalMeshes;
}

void Model3D::setAlpha(float alpha) {
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes.at(i)->setAlpha(alpha);
	}
}