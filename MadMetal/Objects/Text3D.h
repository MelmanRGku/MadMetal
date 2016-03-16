#pragma once

#include "Object3D.h"
#include <string>

class Text3D : public Object3D
{
private:
	std::string stringToRender;
	float fontSize;
public:
	Text3D(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, float fontSize);
	~Text3D(); 
	void setString(std::string toRender) { stringToRender = toRender; }
	void setString(const char *toRender) { stringToRender = std::string(toRender); }

	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
};

