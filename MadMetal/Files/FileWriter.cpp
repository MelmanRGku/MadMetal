#include "FileWriter.h"


FileWriter::FileWriter()
{
}


FileWriter::~FileWriter(){
	delete[] fileName;
}


FileWriter::FileWriter(const char *fileName) {
	this->fileName = fileName;
}


void FileWriter::writeToFile(const std::string contents) {
	std::ofstream out(fileName);
	out << contents;
	out.close();
}

void FileWriter::writeToFile(const char* contents) {
	writeToFile(std::string(contents));
}

void FileWriter::appendToFile(const std::string contents) {
	std::ofstream out(fileName, std::fstream::out | std::fstream::app);
	out << contents;
	out.close();
}

void FileWriter::appendToFile(const char* contents) {
	appendToFile(std::string(contents));
}

void FileWriter::clearFile() {
	std::ofstream ofs(fileName, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}