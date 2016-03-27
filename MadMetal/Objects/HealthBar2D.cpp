#include "HealthBar2D.h"


HealthBar2D::HealthBar2D(long id, Audioable *aable, Animatable *anable, Renderable2D *rable) : Object2D(id, aable, anable, rable)
{
	healthPercentage = 0.f;
}


HealthBar2D::~HealthBar2D()
{
}

bool HealthBar2D::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	if (type != Renderer::ShaderType::SHADER_TYPE_NONE || passNumber > 1)
		return false;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0.f, 1.f, 0);
	glBegin(GL_QUADS);
	glVertex2f(-.98f, -.91f);
	glVertex2f(-.98f, -.88f);
	glVertex2f(healthPercentage * .3f - .98f, -.88f);
	glVertex2f(healthPercentage * .3f - .98f, -.91f);
	glEnd();

	glColor3f(1.f, 0.f, 0);
	glBegin(GL_QUADS);
	glVertex2f(healthPercentage * .3f - .98f, -.91f);
	glVertex2f(healthPercentage * .3f - .98f, -.88f);
	glVertex2f(.3f - .98f, -.88f);
	glVertex2f(.3f - .98f, -.91f);
	glEnd();


	return false;
}
