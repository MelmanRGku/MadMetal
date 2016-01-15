#include "Settings.h"


Settings::Settings()
{
}


Settings::Settings(char *fileName) {
	loadSettingsFromFile(fileName);
}


Settings::~Settings()
{
}


void Settings::loadSettingsFromFile(char *fileName) {
	FileReader *fr = new FileReader(fileName);
	std::vector<std::string> fileLines = fr->getFileContentsSeparatedByLines();
	std::string delimiter = ":";
	for (unsigned int i = 0; i < fileLines.size(); i++) {
		std::string line = fileLines.at(i);
		if (line.length() < 3)
			continue;
		std::string settingName = line.substr(0, line.find(delimiter));
		std::string settingValue = line.substr(line.find(delimiter) + 1);
		settings.insert(std::pair<std::string, std::string>(settingName, settingValue));
	}
	delete fr;
}


std::string Settings::getSetting(char *name) {
	std::map<std::string, std::string>::iterator iter = settings.find(std::string(name));
	if (iter != settings.end())
		return iter->second;
	else
		return NULL;
}


void Settings::setSetting(char *name, char *value) {
	std::map<std::string, std::string>::iterator iter = settings.find(std::string(name));
	if (iter == settings.end())
		settings.insert(std::pair<std::string, std::string>(std::string(name), std::string(value)));
	else {
		settings.erase(iter);
		settings.insert(std::pair<std::string, std::string>(std::string(name), std::string(value)));
	}
}


void Settings::storeToFile(char *name) {
	std::string fileContents;
	for (std::map<std::string, std::string>::iterator iter = settings.begin(); iter != settings.end(); ++iter)
	{
		std::string key = iter->first;
		std::string value = iter->second;
		fileContents.append(key);
		fileContents.append(":");
		fileContents.append(value);
		fileContents.append("\n");
	}
	FileWriter *fw = new FileWriter(name);
	fw->writeToFile(fileContents);
	delete fw;
}
