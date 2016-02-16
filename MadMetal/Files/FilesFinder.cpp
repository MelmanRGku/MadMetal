#include "FilesFinder.h"

FilesFinder::~FilesFinder()
{
}


bool FilesFinder::fileHasExtension(std::string const &fullString, std::string const &ext) {
	if (fullString.length() >= ext.length() + 1) {
		return (0 == fullString.compare(fullString.length() - ext.length() - 1, ext.length() + 1, "." + ext));
	}
	else {
		return false;
	}
}

void FilesFinder::findFilesWithExtension(std::string rootPath, std::string ext, std::vector<std::string> &files) {
	tinydir_dir dir;
	tinydir_open(&dir, rootPath.c_str());

	while (dir.has_next)
	{
		tinydir_file file;
		tinydir_readfile(&dir, &file);

		if (file.is_dir)
		{
			if (strcmp(file.name, ".") != 0 && strcmp(file.name, "..") != 0) {
				findFilesWithExtension(rootPath + "/" + file.name, ext, files);
			}
		}
		else if (FilesFinder::fileHasExtension(file.name, ext)){
			files.push_back(rootPath + "/" + file.name);
		}

		tinydir_next(&dir);
	}

	tinydir_close(&dir);
}
