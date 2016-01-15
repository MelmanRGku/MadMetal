#include "Debug.h"

FileWriter *Debug::fw;
bool Debug::debugMode;

Debug::Debug()
{
}


Debug::~Debug(){
	delete fw;
}

void Debug::init(const char* fileToWrite) {
	fw = new FileWriter(fileToWrite);
	fw->clearFile();
	debugMode = false;
}

void Debug::writeLine(const std::string line) {
	if (debugMode) {
		fw->appendToFile(line + "\n");
	}
}


void Debug::writeLine(const char* line) {
	if (debugMode) {
		writeLine(std::string(line));
	}
}