#pragma once

#include "..\Global\Log.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class FileReader
{
private:
	const char *fileName;
	std::string fileContents;

	void readFile();
public:
	FileReader(const char *fileName);
	~FileReader();
	std::string getFileContents() { return fileContents; }
	std::vector<std::string> getFileContentsSeparatedByLines();
	int getFileLength() { return fileContents.length(); }
};

