#pragma once

#include "TestObject.h"
#include <string>

class Text2D : public TestObject
{
private:
	std::string stringToRender;
	glm::vec3 pos;
public:
	Text2D(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable);
	~Text2D();
	void setString(std::string toRender) { stringToRender = toRender; }
	void setString(const char *toRender) { stringToRender = std::string(toRender); }
	void setPos(glm::vec3 pos) { this->pos = pos; }

	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
};

