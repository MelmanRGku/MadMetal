#include "HealthBar2D.h"


HealthBar2D::HealthBar2D(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio) : TestObject(id, aable, pable, anable, rable, audio)
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
	glVertex2f(-.98f, .98f);
	glVertex2f(-.98f, .95f);
	glVertex2f(healthPercentage * .3f - .98f, .95f);
	glVertex2f(healthPercentage * .3f - .98f, .98f);
	glEnd();

	glColor3f(1.f, 0.f, 0);
	glBegin(GL_QUADS);
	glVertex2f(healthPercentage * .3f - .98f, .98f);
	glVertex2f(healthPercentage * .3f - .98f, .95f);
	glVertex2f(.3f - .98f, .95f);
	glVertex2f(.3f - .98f, .98f);
	glEnd();


	return false;
}
