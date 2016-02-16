#pragma once

#include "..\Global\Log.h"
#include "Libraries\tinydir\tinydir.h"
#include "FileHandlingHelpers.h"


bool FileHandlingHelpers::fileHasExtension(std::string const &fullString, std::string const &ext)
{
	if (fullString.length() >= ext.length() + 1) {
		return (0 == fullString.compare(fullString.length() - ext.length() - 1, ext.length() + 1, "." + ext));
	}
	else {
		return false;
	}
}

double FileHandlingHelpers::findFilesWithExtension(std::string rootPath, std::string ext, std::vector<std::string> &files)
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


/*
	Reads the file and returns its content as a string
*/
std::string FileHandlingHelpers::readFile(const char * filename) {
	std::ifstream ifs(filename);

	if (ifs.fail()) {
		Log::writeLine(std::string("Could not open file ") + filename);
		return "";
	}

	std::string fileContents = std::string((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	return fileContents;
}

/*
	Returns file contents separated by new lines as a string
*/
std::vector<std::string> FileHandlingHelpers::getFileContentsSeparatedByLines(std::string &fileContents) {
	std::vector<std::string> lines;
	std::istringstream stream(fileContents);
	while (!stream.eof())
	{
		std::string s1;
		getline(stream, s1);
		lines.push_back(s1);
	}
	return lines;
}