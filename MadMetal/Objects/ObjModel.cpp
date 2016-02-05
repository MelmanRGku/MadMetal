#include "ObjModel.h"


ObjModel::ObjModel()
{
}

ObjModel::ObjModel(const char* fileName){
	loadFromFile(fileName);
}

ObjModel::~ObjModel()
{
}


/*
	Parses OBJ file and stores all the info about the model
*/
void ObjModel::parseObjFile(const char* fileName) {
	std::vector<glm::vec2> listOfUVs;
	std::vector<glm::vec3> listOfVertices, listOfNormals;

	//open the file
	FILE * file;
	fopen_s(&file, fileName, "r");

	//check the file
	if (file == NULL){
		Log::writeLine(std::string("Could not open OBJ file ") + fileName);
		return;
	}

	
	char lineIndentifier[128];
	int res = fscanf_s(file, "%s", lineIndentifier, 128);
	while (res != EOF){

		//vertex - add to the list of vertices
		if (strcmp(lineIndentifier, "v") == 0){
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			listOfVertices.push_back(vertex);
		}
		//uv - add to the list of uvs
		else if (strcmp(lineIndentifier, "vt") == 0){
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			listOfUVs.push_back(uv);
		}
		//normal - add to the list of normals
		else if (strcmp(lineIndentifier, "vn") == 0){
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			listOfNormals.push_back(normal);
		}
		//face - contains 3 pairs of 3 numbers: vertex index, uv index and normal index
		else if (strcmp(lineIndentifier, "f") == 0){
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);

			if (matches != 9){
				Log::writeLine("Unexpected OBJ face format.");
				//return;
			}

			//push the vertices, normals and uvs in the right order
			for (int i = 0; i < 3; i++) {
				vertices.push_back(listOfVertices.at(vertexIndex[i] - 1));
				normals.push_back(listOfNormals.at(normalIndex[i] - 1));
				//uvs.push_back(listOfUVs.at(uvIndex[i] - 1));
			}
		//something useless - skip it
		} else {
			char dummy[1024];
			fgets(dummy, 1024, file);
		}

		res = fscanf_s(file, "%s", lineIndentifier, 128);
	}
	
	uvs.resize(vertices.size());
}

/*
	Loads an object from a file
*/
void ObjModel::loadFromFile(const char* fileName) {
	//clear object vectors
	clearInfo();
	//parse the file
	parseObjFile(fileName);
	//set some default colour for all vertices
	setColour(1.f, 0.f, 0.f);
}