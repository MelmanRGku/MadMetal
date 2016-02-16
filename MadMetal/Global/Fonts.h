#pragma once

#include <FTGL\ftgl.h>
#include <string>
#include <map>
#include "Files\FIleHandlingHelpers.h"

class Fonts
{
private:
	static std::map<std::string, FTFont *> *fonts;
public:
	Fonts() = delete;
	~Fonts();
	static void init();
	static void loadTTFFontsFromDirectory(std::string path);
	static FTFont *getFont(std::string name) { return fonts->find(name)->second; }
};

