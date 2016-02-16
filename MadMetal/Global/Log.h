#pragma once
#include <string>

class Log
{
private:
	static bool logEnabled;
public:
	Log();
	~Log();
	void init();
	static void enableLogging(bool enable = true) { logEnabled = enable; }
	static void writeLine(const std::string line);
	static void writeLine(const char* line);

private: //members
	const static char* m_fileToWrite;
};

