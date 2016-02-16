#pragma once


#include <map>
#include <string>

#include "Objects\Model.h"
#include "Files\FilesFinder.h"
#include "Objects\ObjectLoaders\ObjModelLoader.h"

class Assets
{
private:
	static std::map<std::string, Model *> *models;
	const static std::string list[];
	const static int NUMBER_OF_ELEMENTS_IN_LIST = 4;
public:
	Assets() = delete;
	~Assets();
	static void init();
	static void loadObjsFromDirectory(std::string path, bool fromList = false);
	static Model *getModel(std::string name) { return models->find(name)->second; }
};

