#include "Text2D.h"
#include "FTGL\ftgl.h"

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
	glLoadIdentity();

	FTGLPixmapFont font("Assets/Fonts/asman.ttf");

	// If something went wrong, bail out.
	if (font.Error())
		return -1;

	// Set the font size and render a small text.
	font.FaceSize(72);
	font.Render(stringToRender.c_str());


	return false;
}
