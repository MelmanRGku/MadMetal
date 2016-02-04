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
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

			if (matches != 9){
				Log::writeLine("Unexpected OBJ face format.");
				return;
			}

			//push the vertices, normals and uvs in the right order
			for (int i = 0; i < 3; i++) {
				vertices.push_back(listOfVertices.at(vertexIndex[i] - 1));
				normals.push_back(listOfNormals.at(normalIndex[i] - 1));
				uvs.push_back(listOfUVs.at(uvIndex[i] - 1));
			}
		//something useless - skip it
		} else {
			char dummy[1024];
			fgets(dummy, 1024, file);
		}

		res = fscanf_s(file, "%s", lineIndentifier, 128);
	}
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

bool Mesh::loadFromFile(const std::string& Filename)
{
	// Create the VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create the buffers for the vertices atttributes
	glGenBuffers(ShaderProgram::TOTAL_NUMBER_OF_ATTRIBUTES+1, &vbo[0]);

	bool Ret = false;
	Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate |
		aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (pScene) {
		Ret = InitFromScene(pScene, Filename);
		std::cout << Ret << std::endl;
	}
	else {
		printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
	}

	// Make sure the VAO is not changed from outside code
	glBindVertexArray(0);

	return Ret;
}


bool Mesh::InitFromScene(const aiScene* pScene, const std::string& Filename)
{
	entries.resize(pScene->mNumMeshes);
	textures.resize(pScene->mNumMaterials);

	// Prepare vectors for vertex attributes and indices
	std::vector<glm::vec3> Positions;
	std::vector<glm::vec3> Normals;
	std::vector<glm::vec2> TexCoords;
	std::vector<unsigned int> Indices;
	std::vector<glm::vec3> Colours;

	unsigned int NumVertices = 0;
	unsigned int NumIndices = 0;

	// Count the number of vertices and indices
	for (unsigned int i = 0; i < entries.size(); i++) {
		entries.at(i).MaterialIndex = pScene->mMeshes[i]->mMaterialIndex;
		entries[i].NumIndices = pScene->mMeshes[i]->mNumFaces * 3;
		entries[i].BaseVertex = NumVertices;
		entries[i].BaseIndex = NumIndices;

		NumVertices += pScene->mMeshes[i]->mNumVertices;
		NumIndices += entries[i].NumIndices;
	}

	// Reserve space in the vectors for the vertex attributes and indices
	Positions.reserve(NumVertices);
	Normals.reserve(NumVertices);
	TexCoords.reserve(NumVertices);
	Indices.reserve(NumIndices);
	Colours.reserve(NumVertices);

	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0; i < entries.size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		InitMesh(paiMesh, Positions, Normals, TexCoords, Indices);
	}

	if (!InitMaterials(pScene, Filename)) {
		//return false;
	}

	for (int i = 0; i < Positions.size(); i++) {
		Colours.push_back(glm::vec3(0, 0, 1));
	}
	// Generate and populate the buffers with vertex attributes and the indices
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0],
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(ShaderProgram::POSITION_ATTRIBUTE_LOCATION);
	glVertexAttribPointer(ShaderProgram::POSITION_ATTRIBUTE_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * TexCoords.size(), &TexCoords[0],
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(ShaderProgram::UV_ATTRIBUTE_LOCATION);
	glVertexAttribPointer(ShaderProgram::UV_ATTRIBUTE_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * Normals.size(), &Normals[0],
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(ShaderProgram::NORMAL_ATTRIBUTE_LOCATION);
	glVertexAttribPointer(ShaderProgram::NORMAL_ATTRIBUTE_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colours[0]) * Colours.size(), &Colours[0],
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(ShaderProgram::COLOUR_ATTRIBUTE_LOCATION);
	glVertexAttribPointer(ShaderProgram::COLOUR_ATTRIBUTE_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[4]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0],
		GL_STATIC_DRAW);

	return true;
}

void Mesh::InitMesh(const aiMesh* paiMesh,
	std::vector<glm::vec3>& Positions,
	std::vector<glm::vec3>& Normals,
	std::vector<glm::vec2>& TexCoords,
	std::vector<unsigned int>& Indices)
{
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	// Populate the vertex attribute vectors
	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ?
			&(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		Positions.push_back(glm::vec3(pPos->x, pPos->y, pPos->z));
		Normals.push_back(glm::vec3(pNormal->x, pNormal->y, pNormal->z));
		TexCoords.push_back(glm::vec2(pTexCoord->x, pTexCoord->y));
	}

	// Populate the index buffer
	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);
	}
}


bool Mesh::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
	// Extract the directory part from the file name
	std::string::size_type SlashIndex = Filename.find_last_of("/");
	std::string Dir;

	if (SlashIndex == std::string::npos) {
		Dir = ".";
	}
	else if (SlashIndex == 0) {
		Dir = "/";
	}
	else {
		Dir = Filename.substr(0, SlashIndex);
	}

	bool Ret = true;

	// Initialize the materials
	for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
		const aiMaterial* pMaterial = pScene->mMaterials[i];

		textures[i] = NULL;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			aiString Path;

			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				std::string p(Path.data);

				if (p.substr(0, 2) == ".\\") {
					p = p.substr(2, p.size() - 2);
				}

				std::string FullPath = Dir + "/" + p;

				textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());

				if (!textures[i]->Load()) {
					printf("Error loading texture '%s'\n", FullPath.c_str());
					delete textures[i];
					textures[i] = NULL;
					Ret = false;
				}
				else {
					printf("Loaded texture '%s'\n", FullPath.c_str());
				}
			}
		}
	}

	return Ret;
}

void Mesh::Render()
{
	glBindVertexArray(vao);

	for (unsigned int i = 0; i < entries.size(); i++) {
		const unsigned int MaterialIndex = entries[i].MaterialIndex;

		if (textures[MaterialIndex]) {
			textures[MaterialIndex]->Bind(GL_TEXTURE0);
		}

		glDrawElementsBaseVertex(GL_TRIANGLES,
			entries[i].NumIndices,
			GL_UNSIGNED_INT,
			(void*)(sizeof(unsigned int)* entries[i].BaseIndex),
			entries[i].BaseVertex);
	}

	// Make sure the VAO is not changed from the outside
	glBindVertexArray(0);
}