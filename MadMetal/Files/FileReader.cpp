#include "FileReader.h"

FileReader::FileReader(const char *fileName) {
	this->fileName = fileName;
	readFile();
}

FileReader::~FileReader(){
	delete[] fileName;
}

void FileReader::readFile() {
	std::ifstream ifs(fileName);

	if (ifs.fail()) {
		Debug::writeLine(std::string("Could not open file ") + fileName);
		return;
	}

	fileContents = std::string((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
}


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