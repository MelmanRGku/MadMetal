#pragma once

#include <map>
#include <string>
#include <vector>
#include "..\Files\FileReader.h"
#include "..\Files\FileWriter.h"

class Settings
{
private:
	std::map<std::string, std::string> settings;
public:
	Settings();
	Settings(char *fileName);
	~Settings();
	void loadSettingsFromFile(char *fileName);
	std::string getSetting(char *name);
	void setSetting(char *name, char *value);
	void storeToFile(char *name);
};

