#include "Text3D.h"
#include "FTGL\ftgl.h"
#include "Libraries\glm\gtc\type_ptr.hpp"


Text3D::Text3D(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, float fontSize) : Object3D(id, aable, pable, anable, rable, NULL), fontSize(fontSize)
{
}


Text3D::~Text3D()
{
}

bool Text3D::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	if (type != Renderer::ShaderType::SHADER_TYPE_NONE || passNumber > 1)
		return false;

	glMatrixMode(GL_PROJECTION);
	glm::mat4x4 proj = renderer->getProjectionMatrix();
	glLoadMatrixf(glm::value_ptr(proj));
	//glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glm::mat4x4 view = renderer->getViewMatrix();
	glLoadMatrixf(glm::value_ptr(view));
	//glLoadIdentity();
	FTPolygonFont font("Assets/Fonts/OpenSans-Bold.ttf");
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);

	glColor3f(1.0, 1.0, 1.0);
	// Set the font size and render a small text.
	font.FaceSize(fontSize);
	font.Depth(3);
	glm::vec3 pos = m_animatable->getPosition();
	float xOffset = font.BBox(stringToRender.c_str(), -1, FTPoint(pos.x, pos.y, pos.z)).Upper().X() - font.BBox(stringToRender.c_str(), -1, FTPoint(pos.x, pos.y, pos.z)).Lower().X();
	float yOffset = font.BBox(stringToRender.c_str(), -1, FTPoint(pos.x, pos.y, pos.z)).Upper().Y() - font.BBox(stringToRender.c_str(), -1, FTPoint(pos.x, pos.y, pos.z)).Lower().Y();
	font.Render(stringToRender.c_str(), -1, FTPoint(pos.x - xOffset / 2, pos.y - yOffset / 2, pos.z));

	glPopAttrib();
	return false;
}
