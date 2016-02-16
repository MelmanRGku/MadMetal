#include "Assets.h"

std::map<std::string, Model*> *Assets::models;
const std::string Assets::list[] = { "Ugly_Car", "bullet", "plane", "finishLine" };

Assets::~Assets()
{
}


void Assets::init() {
	models = new std::map<std::string, Model*>();
}

void Assets::loadObjsFromDirectory(std::string path, bool fromList) {
	std::vector<std::string> files;
	FilesFinder::findFilesWithExtension(path, "obj", files);

	ObjModelLoader *loader = new ObjModelLoader();

	for (unsigned int i = 0; i < files.size(); i++) {
		int lastSlashPos = files.at(i).rfind("/") + 1;
		std::string objectName = files.at(i).substr(lastSlashPos, files.at(i).rfind(".") - lastSlashPos);

		if (fromList) {
			bool isInList = false;
			for (unsigned int j = 0; j < NUMBER_OF_ELEMENTS_IN_LIST; j++) {
				isInList = isInList || objectName.compare(list[j]) == 0;
			}
			if (!isInList)
				continue;
		}

		Model *model = loader->loadFromFile(files.at(i));
		models->insert(std::pair<std::string, Model *>(objectName, model));
		loader = new ObjModelLoader();
	}
}