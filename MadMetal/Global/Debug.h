#pragma once

#include "..\Files\FileWriter.h"

class Debug
{
private:
	static FileWriter *fw;
	static bool debugMode;
public:
	Debug();
	~Debug();
	static void init(const char* fileToWrite);
	static void enableDebug() { debugMode = true; }
	static void disableDebug() { debugMode = false; }
	static void writeLine(const std::string line);
	static void writeLine(const char* line);
};

