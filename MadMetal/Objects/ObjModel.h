#pragma once

#include <vector>
#include <string>
#include "../Libraries/glm/vec3.hpp"
#include "../Libraries/glm/vec2.hpp"
#include "../Global/Log.h"
#include "Renderer\ShaderProgram.h"
#include "Model.h"
#include "Libraries\assimp\scene.h"
#include "Libraries\assimp\Importer.hpp"
#include "Libraries\assimp\postprocess.h"
#include "Libraries\assimp\vector3.h"
#include "Libraries\assimp\vector2.h"
#include "Libraries\assimp\material.h"
#include "Libraries\assimp\texture.h"
#include "Libraries\glew\glew.h"
#include "Renderer\Texture.h"

class ObjModel : public Model
{
private:
	void parseObjFile(const char* fileName);
public:
	ObjModel();
	ObjModel(const char* fileName);
	~ObjModel();
	void loadFromFile(const char* fileName);
};

class Mesh
{
public:
	Mesh(){}

	~Mesh(){}

	bool loadFromFile(const std::string& Filename);

	void Render();

private:
	bool InitFromScene(const aiScene* pScene, const std::string& Filename);
	void InitMesh(const aiMesh* paiMesh,
		std::vector<glm::vec3>& Positions,
		std::vector<glm::vec3>& Normals,
		std::vector<glm::vec2>& TexCoords,
		std::vector<unsigned int>& Indices);

	bool InitMaterials(const aiScene* pScene, const std::string& Filename);

#define INVALID_MATERIAL 0xFFFFFFFF

	GLuint vao;
	GLuint vbo[ShaderProgram::TOTAL_NUMBER_OF_ATTRIBUTES+1];

	struct MeshEntry {
		MeshEntry()
		{
			NumIndices = 0;
			BaseVertex = 0;
			BaseIndex = 0;
			MaterialIndex = INVALID_MATERIAL;
		}

		unsigned int BaseVertex;
		unsigned int BaseIndex;
		unsigned int NumIndices;
		unsigned int MaterialIndex;
	};

	std::vector<MeshEntry> entries;
	std::vector<Texture *> textures;
};