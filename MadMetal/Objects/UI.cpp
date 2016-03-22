#include "UI.h"


UI::UI(long id, Audioable *aable, Animatable *anable, Renderable2D *rable) : Object2D(id, aable, anable, rable)
{
}


UI::~UI()
{
}

bool UI::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	return healthBar->draw(renderer, type, passNumber) ||
		gaugeBar->draw(renderer, type, passNumber) ||
		score->draw(renderer, type, passNumber) ||
		lap->draw(renderer, type, passNumber) ||
		map->draw(renderer, type, passNumber);
}