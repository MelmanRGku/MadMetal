#include "Assets.h"
#include <fstream>

std::map<std::string, Model*> *Assets::models;
const std::vector<std::string> Assets::list = { "Ugly_Car", "bullet", "plane", "finishLine" };
LoadingStatus *Assets::status;

Assets::~Assets()
{
}


void Assets::init() {
	models = new std::map<std::string, Model*>();
}

void Assets::loadObjsFromDirectory(std::string path, bool fromList) {
	std::vector<std::string> files;
	double totalFilesSize = FilesFinder::findFilesWithExtension(path, "obj", files);

	double loadedFilesSize = 0;

	ObjModelLoader *loader = new ObjModelLoader();

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

		Model *model = loader->loadFromFile(files.at(i));
		models->insert(std::pair<std::string, Model *>(objectName, model));
		loader = new ObjModelLoader();

		loadedFilesSize += (std::ifstream((files.at(i)), std::ifstream::ate | std::ifstream::binary)).tellg();
		status->setStatus(loadedFilesSize / totalFilesSize, "Loading file " + objectName);
	}
}

void Assets::initializeVAOs() {
	for (std::map<std::string, Model *>::iterator iterator = models->begin(); iterator != models->end(); iterator++) {
		iterator->second->setupVAOs();
	}
}