#pragma once

#include "..\Files\FileWriter.h"

class Log
{
private:
	static FileWriter *fw;
	static bool logEnabled;
public:
	Log();
	~Log();
	static void init(const char* fileToWrite);
	static void enableLogging(bool enable = true) { logEnabled = enable; }
	static void writeLine(const std::string line);
	static void writeLine(const char* line);
};

