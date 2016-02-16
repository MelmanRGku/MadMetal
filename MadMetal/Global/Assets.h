#pragma once


#include <map>
#include <string>
#include <mutex>
#include <vector>

#include "Objects\Model.h"
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
	static const std::vector<std::string> list;

public:
	static LoadingStatus *status;

	Assets() = delete;
	~Assets();
	static void init();
	static void loadObjsFromDirectory(std::string path, bool fromList = false);
	static void initializeVAOs();
	static Model *getModel(std::string name) { return models->find(name)->second; }
};

