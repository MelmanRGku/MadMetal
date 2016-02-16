#pragma once

#include "Libraries\tinydir\tinydir.h"
#include <string>
#include <vector>

class FilesFinder
{
private:
	static bool fileHasExtension(std::string const &fullString, std::string const &ext);
public:
	FilesFinder() = delete;
	~FilesFinder();
	static double findFilesWithExtension(std::string rootPath, std::string ext, std::vector<std::string> &files);

};

