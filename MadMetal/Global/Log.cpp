#include "Log.h"
#include "Files\FIleHandlingHelpers.h"

bool Log::logEnabled;
const char* Log::m_fileToWrite = "debug.txt";
Log::Log()
{
}


Log::~Log(){
}

/*
	Initializes the logger by creating a new file writer, deleting file
	contents and disabling the logging by default
*/
void Log::init() 
{
	FileHandlingHelpers::clearFileContents(m_fileToWrite);
	logEnabled = false;
}

/*
	Writes a line to the log
*/
void Log::writeLine(const std::string line) 
{
	if (logEnabled) {
		FileHandlingHelpers::appendToFile(m_fileToWrite, (line + "\n"));
	}
}

/*
	@Overload
*/
void Log::writeLine(const char* line) 
{
	if (logEnabled) {
		writeLine(std::string(line));
	}
}