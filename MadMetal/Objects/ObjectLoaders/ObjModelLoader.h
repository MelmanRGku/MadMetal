#pragma once

#include "Libraries\assimp\scene.h"
#include "Libraries\assimp\Importer.hpp"
#include "Libraries\assimp\postprocess.h"
#include "Libraries\assimp\vector3.h"
#include "Libraries\assimp\vector2.h"
#include "Libraries\assimp\material.h"
#include "Libraries\glew\glew.h"
#include "Libraries\glm\vec3.hpp"
#include "Libraries\glm\vec2.hpp"
#include "..\Object.h"
#include "..\Texture.h"
#include "..\Model3D.h"
#include <iostream>
#include <string>

class ObjModelLoader
{
public:
	ObjModelLoader();
	~ObjModelLoader();
	Model3D *loadFromFile(const char* fileName);
	Model3D *loadFromFile(std::string fileName);

private:
	std::string directory;

	Model3D *processScene(const aiScene *scene);
};

