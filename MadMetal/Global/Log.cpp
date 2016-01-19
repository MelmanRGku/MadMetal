#include "Log.h"

FileWriter *Log::fw;
bool Log::logEnabled;

Log::Log()
{
}


Log::~Log(){
	delete fw;
}

/*
	Initializes the logger by creating a new file writer, deleting file
	contents and disabling the logging by default
*/
void Log::init(const char* fileToWrite) {
	fw = new FileWriter(fileToWrite);
	fw->clearFile();
	logEnabled = false;
}

/*
	Writes a line to the log
*/
void Log::writeLine(const std::string line) {
	if (logEnabled) {
		fw->appendToFile(line + "\n");
	}
}

/*
	@Overload
*/
void Log::writeLine(const char* line) {
	if (logEnabled) {
		writeLine(std::string(line));
	}
}