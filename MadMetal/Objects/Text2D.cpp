#include "Text2D.h"
#include "FTGL\ftgl.h"
#include "Libraries\glm\gtc\type_ptr.hpp"

Text2D::Text2D(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable) : TestObject(id, aable, pable, anable, rable)
{
}


Text2D::~Text2D()
{
}

bool Text2D::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	if (type != Renderer::ShaderType::SHADER_TYPE_NONE || passNumber > 1)
		return false;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	FTGLPixmapFont font("Assets/Fonts/OpenSans-Bold.ttf");

	// Set the font size and render a small text.
	font.FaceSize(72);
	font.Render(stringToRender.c_str(), -1, FTPoint(pos.x, pos.y, pos.z));
	return false;
}
