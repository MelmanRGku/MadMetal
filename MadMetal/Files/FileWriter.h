#pragma once

#include <string>
#include <fstream>
#include <iostream>

class FileWriter
{
private:
	const char *fileName;
public:
	FileWriter();
	FileWriter(const char *fileName);
	~FileWriter();
	void writeToFile(const std::string contents);
	void writeToFile(const char* contents);
	void appendToFile(const std::string contents);
	void appendToFile(const char* contents);
	void clearFile();
};

