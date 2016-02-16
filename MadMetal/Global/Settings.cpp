#include "Settings.h"
#include "Files\FileHandlingHelpers.h"
std::map<std::string, std::string> Settings::settings;		//map with all the settings

Settings::Settings()
{
}


Settings::~Settings()
{
}

/*
	Loads settings from a file. Settings are placed in a file
	with a format of setting_name:setting_value
*/
void Settings::loadSettingsFromFile(char *fileName) {
	//create the file reader and get all lines from the file
	std::string fileContent = FileHandlingHelpers::readFile(fileName);
	std::vector<std::string> fileLines = FileHandlingHelpers::getFileContentsSeparatedByLines(fileContent);

	//delimiter for separating name from its value is ":"
	std::string delimiter = ":";

	//parse lines 1 by 1
	for (unsigned int i = 0; i < fileLines.size(); i++) {
		std::string line = fileLines.at(i);
		//skip empty or useless lines
		if (line.length() < 3)
			continue;
		//store the setting in the map
		std::string settingName = line.substr(0, line.find(delimiter));
		std::string settingValue = line.substr(line.find(delimiter) + 1);
		settings.insert(std::pair<std::string, std::string>(settingName, settingValue));
	}
}

/*
	Returns value for a setting based on its name
*/
std::string Settings::getSetting(char *name) {
	//find the setting
	std::map<std::string, std::string>::iterator iter = settings.find(std::string(name));
	//if element exists in the map - return the value
	if (iter != settings.end())
		return iter->second;
	//otherwise nothing
	else {
		return NULL;
	}
}

/*
	Adds or replaces a setting in the map
*/
void Settings::setSetting(char *name, char *value) {
	//check if the setting is already in the map
	std::map<std::string, std::string>::iterator iter = settings.find(std::string(name));
	//if not, just add a new one
	if (iter == settings.end())
		settings.insert(std::pair<std::string, std::string>(std::string(name), std::string(value)));
	//otherwise, remove it and then add a new one
	else {
		settings.erase(iter);
		settings.insert(std::pair<std::string, std::string>(std::string(name), std::string(value)));
	}
}

/*
	Stores all the settings that are currently in the map
	to a file
*/
void Settings::storeToFile(char *name) {
	std::string fileContents;

	//compose each line for the file from 
	//setting name, colon, setting value and a new line
	for (std::map<std::string, std::string>::iterator iter = settings.begin(); iter != settings.end(); ++iter)
	{
		std::string key = iter->first;
		std::string value = iter->second;
		fileContents.append(key);
		fileContents.append(":");
		fileContents.append(value);
		fileContents.append("\n");
	}

	//write the whole string to the file
	FileHandlingHelpers::writeToFile(name, fileContents);
}
