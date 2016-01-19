#include "FileReader.h"

/*
	Constructor. Stores the file name and read the file
*/
FileReader::FileReader(const char *fileName) {
	this->fileName = fileName;
	readFile();
}

FileReader::~FileReader(){
	
}

/*
	Reads the file and stores its contents
*/
void FileReader::readFile() {
	std::ifstream ifs(fileName);

	if (ifs.fail()) {
		Log::writeLine(std::string("Could not open file ") + fileName);
		return;
	}

	fileContents = std::string((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
}

/*
	Returns file contents separated by new lines
*/
std::vector<std::string> FileReader::getFileContentsSeparatedByLines() {
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