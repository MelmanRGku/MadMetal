#include "Model.h"
#include <vector>

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


PxTriangleMesh *Model::getPhysicsTriangleMesh() {
	if (meshes.size() == 0)
		return NULL;

	//const PxVec3* verts, const PxU32 numVerts, const PxU32* indices, const PxU32 numTriangles;
	PxU32 totalNumOfVertices = 0;
	PxU32 totalNumOfTriangles = 0;
	for (unsigned int i = 0; i < meshes.size(); i++) {
		totalNumOfVertices += meshes.at(i)->getVertices()->size();
		totalNumOfTriangles += meshes.at(i)->getIndices()->size() / 3;
	}

	PxVec3 *verts = new PxVec3[totalNumOfVertices];
	PxU32 *indices = new PxU32[totalNumOfTriangles * 3];

	int vertIndex = 0;
	int indexOfIndex = 0;
	for (unsigned int i = 0; i < meshes.size(); i++) {
		std::vector<glm::vec3> *vertices = meshes.at(i)->getVertices();
		for (unsigned int j = 0; j < vertices->size(); j++) {
			glm::vec3 vertex = vertices->at(j);
			verts[vertIndex] = PxVec3(vertex.x, vertex.y, vertex.z);
			vertIndex++;
		}

		for (unsigned int j = 0; j < meshes.at(i)->getIndices()->size(); j++) {
			indices[indexOfIndex] = meshes.at(i)->getIndices()->at(j);
			indexOfIndex++;
		}

	}



	// Create descriptor for convex mesh
	PxTriangleMeshDesc description;
	description.points.count = totalNumOfVertices;
	description.triangles.count = totalNumOfTriangles;
	description.points.stride = sizeof(PxVec3);
	description.triangles.stride = 3 * sizeof(PxU32);
	description.points.data = verts;
	description.triangles.data = indices;

	PxTriangleMesh* triangleMesh = NULL;
	PxDefaultMemoryOutputStream buf;
	if (PhysicsManager::getCookingInstance().cookTriangleMesh(description, buf))
	{
		std::cout << "created the triangle mesh \n";
		PxDefaultMemoryInputData id(buf.getData(), buf.getSize());
		triangleMesh = PhysicsManager::getPhysicsInstance().createTriangleMesh(id);
	}

	return triangleMesh;
}
