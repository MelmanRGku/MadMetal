#pragma once

#include "TestObject.h"
#include <string>

class Text2D : public TestObject
{
private:
	std::string stringToRender;
public:
	Text2D(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio);
	~Text2D();
	void setString(std::string toRender) { stringToRender = toRender; }
	void setString(const char *toRender) { stringToRender = std::string(toRender); }

	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
};

