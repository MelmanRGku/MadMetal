#include "GaugeBar.h"


GaugeBar::GaugeBar(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio*audio) : TestObject(id, aable, pable, anable, rable, audio)
{
	gaugePercentage = 0.f;
}


GaugeBar::~GaugeBar()
{
}

bool GaugeBar::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	if (type != Renderer::ShaderType::SHADER_TYPE_NONE || passNumber > 1)
		return false;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0.f, 0.f, 1.f);
	glBegin(GL_QUADS);
	glVertex2f(.98f, -.98f);
	glVertex2f(.98f, -.95f);
	glVertex2f(.98f - gaugePercentage * .3f, -.95f);
	glVertex2f(.98f - gaugePercentage * .3f, -.98f);
	glEnd();

	glColor3f(.3f, .4f, .7f);
	glBegin(GL_QUADS);
	glVertex2f(.98f - .3f, -.98f);
	glVertex2f(.98f - .3f, -.95f);
	glVertex2f(.98f - gaugePercentage * .3f, -.95f);
	glVertex2f(.98f - gaugePercentage * .3f, -.98f);
	glEnd();


	return false;
}