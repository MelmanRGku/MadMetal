#pragma once

#include "TestObject.h"
#include <string>
#define DEFAULT_FONT_SIZE 72
class Text2D : public TestObject
{
private:
	std::string stringToRender;
	glm::vec3 pos;
	float m_fontSize = DEFAULT_FONT_SIZE;
	bool m_centerize;
public:
	Text2D(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable *rable);
	~Text2D();
	void setString(std::string toRender) { stringToRender = toRender; }
	void setString(const char *toRender) { stringToRender = std::string(toRender); }
	void setPos(glm::vec3 pos) { this->pos = pos; }
	void centerize(bool centerize) { m_centerize = centerize; }
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void setFontSize(float size){ m_fontSize = size; }
	void resetFontSize() { m_fontSize = DEFAULT_FONT_SIZE; }
};

