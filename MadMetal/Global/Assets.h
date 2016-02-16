#pragma once


#include <map>
#include <string>
#include <mutex>

#include "Objects\Model.h"
#include "Files\FilesFinder.h"
#include "Objects\ObjectLoaders\ObjModelLoader.h"

class LoadingStatus {

private:
	std::mutex m;
public:
	float percentageDone;
	std::string message;

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
};

class Assets
{
private:
	static std::map<std::string, Model *> *models;
	const static std::string list[];
	const static int NUMBER_OF_ELEMENTS_IN_LIST = 4;

public:
	static LoadingStatus *status;

	Assets() = delete;
	~Assets();
	static void init();
	static void loadObjsFromDirectory(std::string path, bool fromList = false);
	static void initializeVAOs();
	static Model *getModel(std::string name) { return models->find(name)->second; }
};

