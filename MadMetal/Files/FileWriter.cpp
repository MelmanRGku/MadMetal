#include "FileWriter.h"


FileWriter::FileWriter()
{
}


FileWriter::~FileWriter(){

}

/*
	Constructor. Stores the name of the file to write to
*/
FileWriter::FileWriter(const char *fileName) {
	this->fileName = fileName;
}

/*
	Writes a string to the file. This will remove all current
	file contents
*/
void FileWriter::writeToFile(const std::string contents) {
	std::ofstream out(fileName);
	out << contents;
	out.close();
}

/*
	@Overload
*/
void FileWriter::writeToFile(const char* contents) {
	writeToFile(std::string(contents));
}

/*
	Appends a string to the end of the file.
*/
void FileWriter::appendToFile(const std::string contents) {
	std::ofstream out(fileName, std::fstream::out | std::fstream::app);
	out << contents;
	out.close();
}

/*
	@Overload
*/
void FileWriter::appendToFile(const char* contents) {
	appendToFile(std::string(contents));
}

/*
	Deletes file contents
*/
void FileWriter::clearFile() {
	std::ofstream ofs(fileName, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}