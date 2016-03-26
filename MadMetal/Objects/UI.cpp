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


void UI::adjustStringsForViewport(int thisViewportNumber, int totalNumberOfViewports) {
	if (totalNumberOfViewports == 1)
		return;

	if (totalNumberOfViewports == 2) {
		score->setFontSize(36);
		lap->setFontSize(36);
		lap->setPosition(glm::vec3(10, 35, 0));
	}

	if (totalNumberOfViewports == 3) {
		//top two
		if (thisViewportNumber == 1 || thisViewportNumber == 2) {
			score->setFontSize(18);
			lap->setFontSize(18);
			lap->setPosition(glm::vec3(10, 18, 0));
		}
		//bottom one
		else if (thisViewportNumber == 3) {
			score->setFontSize(36);
			lap->setFontSize(36);
			lap->setPosition(glm::vec3(10, 35, 0));
		}
	}

	if (totalNumberOfViewports == 4) {
		score->setFontSize(18);
		lap->setFontSize(18);
		lap->setPosition(glm::vec3(10, 18, 0));
	}
}