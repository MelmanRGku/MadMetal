#pragma once

#include <vector>
#include "../Libraries/glm/vec3.hpp"
#include "../Libraries/glm/vec2.hpp"
#include "../Global/Log.h"
#include "Model.h"

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

