#pragma once


#include <map>
#include <string>
#include <mutex>
#include <vector>

#include "Objects\Model3D.h"
#include "Objects\Model2D.h"
#include "Objects\ObjectLoaders\ObjModelLoader.h"
#include <Windows.h>

class LoadingStatus {

private:
	std::mutex m;
public:
	float percentageDone;
	std::string message;
	std::string fileName;
	bool done = false;

	LoadingStatus() : percentageDone(0), message("Initiating Load"){}
	void setStatus(float percentageDone, std::string message) {
		m.lock();
		this->percentageDone = percentageDone;
		this->message = message;
		m.unlock();
	}
	float getPercentage() {
		float per;
		m.lock();
		per = percentageDone;
		m.unlock();
		return per;
	}
	std::string getMessage() {
		std::string message;
		m.lock();
		message = this->message;
		m.unlock();
		return message;
	}
	void setCurrentLoadingFile(std::string name) {
		m.lock();
		fileName = name;
		m.unlock();
	}
	std::string getCurrentLoadingFile() {
		std::string name;
		m.lock();
		name = fileName;
		m.unlock();
		return name;
	}
};

class Assets
{
private:
	static std::mutex m;
	static std::map<std::string, Model *> *models;
	static std::map<std::string, Texture *> *textures;
	static std::vector<std::string> *modelsToBeLoadedBeforeTheGameStarts;

public:
	static LoadingStatus *status;

	Assets() = delete;
	~Assets();
	static void init();
	static void loadObjsFromDirectory(std::string path);
	static Model *loadObjFromDirectory(std::string path);
	static void loadPNGsFromDirectory(std::string path);
	static Texture *loadTextureFromDirectory(std::string path);
	static void initializeVAOs();
	static Model *getModel(std::string name) { 
		if (models->find(name) == models->end()){
			return NULL;
		}
		else
		{
			return models->find(name)->second;
		}
	}
	static Texture *getTexture(std::string name) {
		if (textures->find(name) == textures->end()){
			return NULL;
		}
		else 
		{
			return textures->find(name)->second;
		}
	}
	static void release();
	static void load(std::string objPath, std::string pngPath, HDC dc, HGLRC sharedOpenglContext);
	static void loadBeforeGameStarts();
};

