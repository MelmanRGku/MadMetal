#pragma once

#include "Object2D.h"
#include <string>
#define DEFAULT_FONT_SIZE 72
class Text2D : public Object2D
{
private:
	std::string stringToRender;
	float m_fontSize = DEFAULT_FONT_SIZE;
	bool m_centerize;
public:
	Text2D(long id, Audioable *aable, Animatable *anable, Renderable2D *rable);
	~Text2D();
	void setString(std::string toRender) { stringToRender = toRender; }
	void setString(const char *toRender) { stringToRender = std::string(toRender); }
	void centerize(bool centerize) { m_centerize = centerize; }
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void setFontSize(float size){ m_fontSize = size; }
	void resetFontSize() { m_fontSize = DEFAULT_FONT_SIZE; }
};

