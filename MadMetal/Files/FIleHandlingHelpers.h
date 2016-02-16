#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace FileHandlingHelpers
{
	bool fileHasExtension(std::string const &fullString, std::string const &ext);

	double findFilesWithExtension(std::string rootPath, std::string ext, std::vector<std::string> &files);

	/*
	Reads the file and returns its content as a string
	*/
	std::string readFile(const char * filename);

	/*
	Returns file contents separated by new lines as a string
	*/
	std::vector<std::string> getFileContentsSeparatedByLines(std::string &fileContents);

	/*
	Writes a string to the file. This will remove all current
	file contents
	*/
	void writeToFile(const char *fileName, const std::string contents);
	/*
	@Overload
	*/
	void writeToFile(const char *fileName, const char* contents);
	/*
	Appends a string to the end of the file.
	*/
	void appendToFile(const char *fileName, const std::string contents);

	/*
	@Overload
	*/
	void appendToFile(const char *fileName, const char* contents);
	
	/*
	Deletes file contents
	*/
	void clearFileContents(const char *fileName);
}