#include "Assets.h"
#include <fstream>
#include "Files\FileHandlingHelpers.h"

std::map<std::string, Model*> *Assets::models;
const std::vector<std::string> Assets::list = { "Ugly_Car", "bullet", "plane", "finishLine" };
LoadingStatus *Assets::status;

Assets::~Assets()
{
}


void Assets::init() {
	models = new std::map<std::string, Model*>();
}

void Assets::release() {
	typedef std::map<std::string, Model*>::iterator it_type;
	for (it_type iterator = models->begin(); iterator != models->end(); iterator++) {
		delete iterator->second;
	}
	delete models;
}

Model *Assets::loadObjFromDirectory(std::string path) {
	int lastSlashPos = path.rfind("/") + 1;
	std::string objectName = path.substr(lastSlashPos, path.rfind(".") - lastSlashPos);
	ObjModelLoader *loader = new ObjModelLoader();
	Model *model = loader->loadFromFile(path);
	models->insert(std::pair<std::string, Model *>(objectName, model));
	delete loader;
	return model;
}

void Assets::loadObjsFromDirectory(std::string path, bool fromList) {
	std::vector<std::string> files;
	double totalFilesSize = FileHandlingHelpers::findFilesWithExtension(path, "obj", files);

	double loadedFilesSize = 0;

	for (unsigned int i = 0; i < files.size(); i++) {
		int lastSlashPos = files.at(i).rfind("/") + 1;
		std::string objectName = files.at(i).substr(lastSlashPos, files.at(i).rfind(".") - lastSlashPos);

		status->setStatus(loadedFilesSize / totalFilesSize, "Loading file " + objectName);

		if (fromList) {
			bool isInList = false;
			for (unsigned int j = 0; j < list.size(); j++) {
				isInList = isInList || objectName.compare(list[j]) == 0;
			}
			if (!isInList)
				continue;
		}

		if (getModel(objectName) == NULL)
			loadObjFromDirectory(files.at(i));

		loadedFilesSize += (std::ifstream((files.at(i)), std::ifstream::ate | std::ifstream::binary)).tellg();
		status->setStatus(loadedFilesSize / totalFilesSize, "Loading file " + objectName);
	}
}

void Assets::initializeVAOs() {
	for (std::map<std::string, Model *>::iterator iterator = models->begin(); iterator != models->end(); iterator++) {
		iterator->second->setupVAOs();
	}
}