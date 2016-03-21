#include "Text2D.h"
#include "FTGL\ftgl.h"
#include "Libraries\glm\gtc\type_ptr.hpp"

Text2D::Text2D(long id, Audioable *aable, Animatable *anable, Renderable2D *rable) : Object2D(id, aable, anable, rable)
{
	m_centerize = false;
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
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);

	glColor4f(1.0, 0.0, 0.0, 1.0);
	// Set the font size and render a small text.
	font.FaceSize(m_fontSize);
	
	float xOffset = 0;
	float yOffset = 0;
	glm::vec3 pos = m_animatable->getPosition();
	if (m_centerize) {
		xOffset = font.BBox(stringToRender.c_str(), -1, FTPoint(pos.x, pos.y, pos.z)).Upper().X() - font.BBox(stringToRender.c_str(), -1, FTPoint(pos.x, pos.y, pos.z)).Lower().X();
		yOffset = font.BBox(stringToRender.c_str(), -1, FTPoint(pos.x, pos.y, pos.z)).Upper().Y() - font.BBox(stringToRender.c_str(), -1, FTPoint(pos.x, pos.y, pos.z)).Lower().Y();
	}
	font.Render(stringToRender.c_str(), -1, FTPoint(pos.x - xOffset/2, pos.y - yOffset / 2, pos.z));
	glPopAttrib();
	return false;
}
