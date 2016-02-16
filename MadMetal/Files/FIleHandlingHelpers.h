#pragma once

#include "Libraries\tinydir\tinydir.h"
#include <string>
#include <vector>
#include <fstream>

bool fileHasExtension(std::string const &fullString, std::string const &ext) 
{
	if (fullString.length() >= ext.length() + 1) {
		return (0 == fullString.compare(fullString.length() - ext.length() - 1, ext.length() + 1, "." + ext));
	}
	else {
		return false;
	}
}

double findFilesWithExtension(std::string rootPath, std::string ext, std::vector<std::string> &files) 
{
	double totalFilesSize = 0;

	tinydir_dir dir;
	tinydir_open(&dir, rootPath.c_str());

	while (dir.has_next)
	{
		tinydir_file file;
		tinydir_readfile(&dir, &file);

		if (file.is_dir)
		{
			if (strcmp(file.name, ".") != 0 && strcmp(file.name, "..") != 0) {
				totalFilesSize += findFilesWithExtension(rootPath + "/" + file.name, ext, files);
			}
		}
		else if (fileHasExtension(file.name, ext)){
			files.push_back(rootPath + "/" + file.name);
			std::ifstream in((rootPath + "/" + file.name), std::ifstream::ate | std::ifstream::binary);
			totalFilesSize += in.tellg();
		}

		tinydir_next(&dir);
	}

	tinydir_close(&dir);

	return totalFilesSize;
}
