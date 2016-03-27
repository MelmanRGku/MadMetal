#include "TexturedObject2D.h"


TexturedObject2D::TexturedObject2D(long id, Audioable *aable, Animatable *anable, Renderable2D *rable) : Object2D(id, aable, anable, rable)
{
}


TexturedObject2D::~TexturedObject2D()
{
}

bool TexturedObject2D::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	if (passNumber < 2)
		return true;

	if (passNumber > 2)
		return false;

	if (type != Renderer::ShaderType::SHADER_TYPE_NONE)
		return false;

	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glm::vec3 pos = m_animatable->getPosition();
	glm::vec3 size = m_animatable->getScale();
	glColor4f(1.f, 1.f, 1.f, 1.f);
	Model2D *model = static_cast<Model2D*>(m_renderable->getModel());
	model->getTexture()->Bind(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex2f(pos.x - size.x / 2, pos.y - size.y / 2);
	glTexCoord2f(1, 1);
	glVertex2f(pos.x + size.x / 2, pos.y - size.y / 2);
	glTexCoord2f(1, 0);
	glVertex2f(pos.x + size.x / 2, pos.y + size.y / 2);
	glTexCoord2f(0, 0);
	glVertex2f(pos.x - size.x / 2, pos.y + size.y / 2);
	glEnd();
	model->getTexture()->unBind(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	return false;
}

void TexturedObject2D::update(float dt) {
	Object2D::update(dt);
}