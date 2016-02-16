#include "Fonts.h"

std::map<std::string, FTFont *> *Fonts::fonts;

Fonts::~Fonts()
{
}

void Fonts::init() {
	fonts = new std::map<std::string, FTFont *>();
}

void Fonts::loadTTFFontsFromDirectory(std::string path) {
	std::vector<std::string> files;
	FilesFinder::findFilesWithExtension(path, "ttf", files);

	FTFont *font;
	char buf[129];
	for (int i = 128; i < 256; i++)
	{
		buf[i-128] = (char)(unsigned char)i;
	}
	buf[128] = '\0';

	for (unsigned int i = 0; i < files.size(); i++) {
		int lastSlashPos = files.at(i).rfind("/") + 1;
		std::string fontName = files.at(i).substr(lastSlashPos, files.at(i).rfind(".") - lastSlashPos);

		font = new FTTextureFont(files.at(i).c_str());
		if (font->Error() != 0)
			exit(5);
		if (!font->FaceSize(18))
			exit(2);
		fonts->insert(std::pair<std::string, FTFont *>(fontName, font));
	}
}