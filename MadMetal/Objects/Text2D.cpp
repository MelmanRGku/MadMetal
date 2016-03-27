#include "Text2D.h"
#include "Libraries\glm\gtc\type_ptr.hpp"

Text2D::Text2D(long id, Audioable *aable, Animatable *anable, Renderable2D *rable) : Object2D(id, aable, anable, rable)
{
	m_centerize = false;
	font = new FTGLBitmapFont("Assets/Fonts/OpenSans-Bold.ttf");
	font->FaceSize(m_fontSize);
}


Text2D::~Text2D()
{
	delete font;
}

bool Text2D::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	if (type != Renderer::ShaderType::SHADER_TYPE_NONE || passNumber > 1)
		return false;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);

	glColor4f(1.0, 0.0, 0.0, 1.0);
	// Set the font size and render a small text.	
	glm::vec3 pos = m_animatable->getPosition();
	font->Render(stringToRender.c_str(), -1, FTPoint(pos.x - xOffset / 2, pos.y - yOffset / 2, pos.z));
	glPopAttrib();
	return false;
}


void Text2D::setString(std::string toRender) { 
	stringToRender = toRender; 
	if (m_centerize) {
		xOffset = font->BBox(stringToRender.c_str(), -1, FTPoint()).Upper().X() - font->BBox(stringToRender.c_str(), -1, FTPoint()).Lower().X();
		yOffset = font->BBox(stringToRender.c_str(), -1, FTPoint()).Upper().Y() - font->BBox(stringToRender.c_str(), -1, FTPoint()).Lower().Y();
	}
}

void Text2D::setString(const char *toRender) { 
	setString(std::string(toRender)); 
}


void Text2D::centerize(bool centerize) { 
	m_centerize = centerize; 

	if (centerize){
		xOffset = font->BBox(stringToRender.c_str(), -1, FTPoint()).Upper().X() - font->BBox(stringToRender.c_str(), -1, FTPoint()).Lower().X();
		yOffset = font->BBox(stringToRender.c_str(), -1, FTPoint()).Upper().Y() - font->BBox(stringToRender.c_str(), -1, FTPoint()).Lower().Y();
	}
	else {
		xOffset = 0;
		yOffset = 0;
	}
}