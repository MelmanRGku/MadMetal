#include "Assets.h"
#include <fstream>
#include "Files\FileHandlingHelpers.h"
#include <windows.h>
#include "winbase.h"
#include "wingdi.h"
#include "winerror.h"
#include "winternl.h"
#include "winnt.h"

std::map<std::string, Model*> *Assets::models;
std::map<std::string, Texture *> *Assets::textures;
std::vector<std::string> *Assets::modelsToBeLoadedBeforeTheGameStarts;
std::mutex Assets::m;
LoadingStatus *Assets::status;

Assets::~Assets()
{
}


void Assets::init() {
	models = new std::map<std::string, Model*>();
	textures = new std::map<std::string, Texture*>();
	modelsToBeLoadedBeforeTheGameStarts = new std::vector<std::string>();
	modelsToBeLoadedBeforeTheGameStarts->push_back("Assets/Models/UglyCarWithCannon.obj");
	modelsToBeLoadedBeforeTheGameStarts->push_back("Assets/Models/UglyCarWithGuns.obj");
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
	if (status != NULL && objectName.compare(status->getCurrentLoadingFile()) == 0) {
		m.lock();
		m.unlock();
		return getModel(objectName);
	}
	m.lock();
	if (getModel(objectName) != NULL) {
		m.unlock();
		return getModel(objectName);
	}
	if (status != NULL)
		status->setCurrentLoadingFile(objectName);
	ObjModelLoader *loader = new ObjModelLoader();
	Model *model = loader->loadFromFile(path); 
	static_cast<Model3D *>(model)->setupVBOs();
	models->insert(std::pair<std::string, Model *>(objectName, model));
	m.unlock();
	delete loader;
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

void Assets::load(std::string objPath, std::string pngPath, HDC dc, HGLRC sharedOpenglContext) {
	//share the device and opengl contexts with this new thread
	wglMakeCurrent(dc, sharedOpenglContext);
	loadObjsFromDirectory(objPath);
	loadPNGsFromDirectory(pngPath);	
	status->done = true;

	//remove the newly created opengl context and unbind everything from this thread (by everything I mean DC and opengl context)
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(sharedOpenglContext);
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

void Assets::loadBeforeGameStarts() {
	for (unsigned int i = 0; i < modelsToBeLoadedBeforeTheGameStarts->size(); i++) {
		Model3D *model = static_cast<Model3D *>(loadObjFromDirectory(modelsToBeLoadedBeforeTheGameStarts->at(i)));
		model->setupVAOs();
	}
}