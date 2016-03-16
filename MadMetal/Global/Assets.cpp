#include "Assets.h"
#include <fstream>
#include "Files\FileHandlingHelpers.h"

std::map<std::string, Model*> *Assets::models;
std::map<std::string, Texture *> *Assets::textures;
std::mutex Assets::m;
LoadingStatus *Assets::status;

Assets::~Assets()
{
}


void Assets::init() {
	models = new std::map<std::string, Model*>();
	textures = new std::map<std::string, Texture*>();
}

void Assets::release() {
	delete status;

	typedef std::map<std::string, Model*>::iterator it_type;
	for (it_type iterator = models->begin(); iterator != models->end(); iterator++) {
		delete iterator->second;
	}
	delete models;

	typedef std::map<std::string, Texture*>::iterator it2_type;
	for (it2_type iterator = textures->begin(); iterator != textures->end(); iterator++) {
		delete iterator->second;
	}
	delete textures;
}

Model *Assets::loadObjFromDirectory(std::string path) {
	int lastSlashPos = path.rfind("/") + 1;
	std::string objectName = path.substr(lastSlashPos, path.rfind(".") - lastSlashPos);
	m.lock();
	if (getModel(objectName) != NULL) {
		m.unlock();
		return getModel(objectName);
	}
	ObjModelLoader *loader = new ObjModelLoader();
	Model *model = loader->loadFromFile(path);
	models->insert(std::pair<std::string, Model *>(objectName, model));
	delete loader;
	m.unlock();
	return model;
}

Texture *Assets::loadTextureFromDirectory(std::string path) {
	int lastSlashPos = path.rfind("/") + 1;
	std::string objectName = path.substr(lastSlashPos, path.rfind(".") - lastSlashPos);
	m.lock();
	Texture *tex = new Texture(GL_TEXTURE_2D, path);
	textures->insert(std::pair<std::string, Texture *>(objectName, tex));
	m.unlock();
	return tex;
}

void Assets::loadObjsFromDirectory(std::string path) {
	std::vector<std::string> files;
	double totalFilesSize = FileHandlingHelpers::findFilesWithExtension(path, "obj", files);

	double loadedFilesSize = 0;

	for (unsigned int i = 0; i < files.size(); i++) {
		int lastSlashPos = files.at(i).rfind("/") + 1;
		std::string objectName = files.at(i).substr(lastSlashPos, files.at(i).rfind(".") - lastSlashPos);

		status->setStatus(loadedFilesSize / totalFilesSize, "Loading file " + objectName);

		if (getModel(objectName) == NULL)
			loadObjFromDirectory(files.at(i));

		loadedFilesSize += (std::ifstream((files.at(i)), std::ifstream::ate | std::ifstream::binary)).tellg();
		status->setStatus(loadedFilesSize / totalFilesSize, "Loading file " + objectName);
	}
}

void Assets::loadPNGsFromDirectory(std::string path) {
	std::vector<std::string> files;
	double totalFilesSize = FileHandlingHelpers::findFilesWithExtension(path, "png", files);

	double loadedFilesSize = 0;

	for (unsigned int i = 0; i < files.size(); i++) {
		int lastSlashPos = files.at(i).rfind("/") + 1;
		std::string objectName = files.at(i).substr(lastSlashPos, files.at(i).rfind(".") - lastSlashPos);

		status->setStatus(loadedFilesSize / totalFilesSize, "Loading texture " + objectName);

		if (getTexture(objectName) == NULL)
			loadTextureFromDirectory(files.at(i));

		loadedFilesSize += (std::ifstream((files.at(i)), std::ifstream::ate | std::ifstream::binary)).tellg();
		status->setStatus(loadedFilesSize / totalFilesSize, "Loading texture " + objectName);
	}
}

void Assets::load(std::string objPath, std::string pngPath) {
	loadObjsFromDirectory(objPath);
	loadPNGsFromDirectory(pngPath);
	status->done = true;
}

void Assets::initializeVAOs() {
	for (std::map<std::string, Model *>::iterator iterator = models->begin(); iterator != models->end(); iterator++) {
		Model3D *model = static_cast<Model3D*> (iterator->second);
		model->setupVAOs();
	}

	for (std::map<std::string, Texture *>::iterator iterator = textures->begin(); iterator != textures->end(); iterator++) {
		iterator->second->Load();
	}
}