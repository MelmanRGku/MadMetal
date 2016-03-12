#pragma once

#include "TestObject.h"
#include <string>

class Text3D : public TestObject
{
private:
	std::string stringToRender;
	glm::vec3 pos;
	float fontSize;
public:
	Text3D(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable *rable, float fontSize);
	~Text3D(); 
	void setString(std::string toRender) { stringToRender = toRender; }
	void setString(const char *toRender) { stringToRender = std::string(toRender); }
	void setPos(glm::vec3 pos) { this->pos = pos; }

	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
};

