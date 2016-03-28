#include "UI.h"
#include "Factory\GameFactory.h"
#include "UIScoreTable.h"

UI::UI(long id, Audioable *aable, Animatable *anable, Renderable2D *rable) : Object2D(id, aable, anable, rable)
{
}


UI::~UI()
{
	delete healthBar;
	delete gaugeBar;
	delete lap;
	delete map;
	delete powerupBorder;
	delete scoreTable;
	if (powerupIcon != NULL)
		delete powerupIcon;
}

bool UI::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	bool toReturn = false;
	toReturn = healthBar->draw(renderer, type, passNumber) || toReturn;
	toReturn = gaugeBar->draw(renderer, type, passNumber) || toReturn;
	toReturn = lap->draw(renderer, type, passNumber) || toReturn;
	toReturn = map->draw(renderer, type, passNumber) || toReturn;
	toReturn = powerupBorder->draw(renderer, type, passNumber) || toReturn;
	toReturn = scoreTable->draw(renderer, type, passNumber) || toReturn;
	if (powerupIcon != NULL)
		toReturn = powerupIcon->draw(renderer, type, passNumber) || toReturn;
	return  toReturn;

}

void UI::setPowerup(PowerUpType type) {
	if (type == PowerUpType::ATTACK) {
		powerupIcon = static_cast<TexturedObject2D *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_UI_ATTACK_POWERUP_ICON, NULL, NULL, NULL));
	}
	else if (type == PowerUpType::DEFENSE) {
		powerupIcon = static_cast<TexturedObject2D *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_UI_SHIELD_POWERUP_ICON, NULL, NULL, NULL));
	}
	else if (type == PowerUpType::SPEED) {
		powerupIcon = static_cast<TexturedObject2D *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_UI_SPEED_POWERUP_ICON, NULL, NULL, NULL));
	}
}

void UI::unsetPowerup() {
	delete powerupIcon;
	powerupIcon = NULL;
}

void UI::adjustStringsForViewport(int thisViewportNumber, int totalNumberOfViewports) {
	if (totalNumberOfViewports == 1)
		return;

	if (totalNumberOfViewports == 2) {
		if (thisViewportNumber == 1) {
			lap->setFontSize(36);
			lap->setPosition(glm::vec3(glutGet(GLUT_WINDOW_WIDTH) - 75, glutGet(GLUT_WINDOW_HEIGHT) - 18, 0));
			float newFontSize = scoreTable->getFontSize() / 1.5;
			scoreTable->setFontSize(newFontSize);
			scoreTable->setPosition(glm::vec3(0, glutGet(GLUT_WINDOW_HEIGHT) - newFontSize, 0));
		}

		if (thisViewportNumber == 2) {
			lap->setFontSize(36);
			lap->setPosition(glm::vec3(glutGet(GLUT_WINDOW_WIDTH) - 75, glutGet(GLUT_WINDOW_HEIGHT) / 2 - 18, 0));
			float newFontSize = scoreTable->getFontSize() / 1.5;
			scoreTable->setFontSize(newFontSize);
			scoreTable->setPosition(glm::vec3(0, glutGet(GLUT_WINDOW_HEIGHT) / 2 - newFontSize, 0));
		}
	}

	if (totalNumberOfViewports == 3) {
		//top left
		if (thisViewportNumber == 1) {
			lap->setFontSize(18);
			lap->setPosition(glm::vec3(glutGet(GLUT_WINDOW_WIDTH) / 2 - 50, glutGet(GLUT_WINDOW_HEIGHT) - 18, 0));
			float newFontSize = scoreTable->getFontSize() / 3;
			scoreTable->setFontSize(newFontSize);
			scoreTable->setPosition(glm::vec3(0, glutGet(GLUT_WINDOW_HEIGHT) - newFontSize, 0));
		}
		//top right
		else if (thisViewportNumber == 2) {
			lap->setFontSize(18);
			lap->setPosition(glm::vec3(glutGet(GLUT_WINDOW_WIDTH) - 50, glutGet(GLUT_WINDOW_HEIGHT) - 18, 0));
			float newFontSize = scoreTable->getFontSize() / 3;
			scoreTable->setFontSize(newFontSize);
			scoreTable->setPosition(glm::vec3(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) - newFontSize, 0));
		}
		//bottom one
		else if (thisViewportNumber == 3) {
			lap->setFontSize(36);
			lap->setPosition(glm::vec3(glutGet(GLUT_WINDOW_WIDTH) - 75, glutGet(GLUT_WINDOW_HEIGHT) / 2 - 36, 0));
			float newFontSize = scoreTable->getFontSize() / 1.5;
			scoreTable->setFontSize(newFontSize);
			scoreTable->setPosition(glm::vec3(0, glutGet(GLUT_WINDOW_HEIGHT) / 2 - newFontSize, 0));
		}
	}

	if (totalNumberOfViewports == 4) {
		//top left
		if (thisViewportNumber == 1){
			lap->setFontSize(18);
			lap->setPosition(glm::vec3(glutGet(GLUT_WINDOW_WIDTH) / 2 - 50, glutGet(GLUT_WINDOW_HEIGHT) - 18, 0));
			float newFontSize = scoreTable->getFontSize() / 3;
			scoreTable->setFontSize(newFontSize);
			scoreTable->setPosition(glm::vec3(0, glutGet(GLUT_WINDOW_HEIGHT) - newFontSize, 0));
		}
		//top right
		else if (thisViewportNumber == 2) {
			lap->setFontSize(18);
			lap->setPosition(glm::vec3(glutGet(GLUT_WINDOW_WIDTH) - 50, glutGet(GLUT_WINDOW_HEIGHT) - 18, 0));
			float newFontSize = scoreTable->getFontSize() / 3;
			scoreTable->setFontSize(newFontSize);
			scoreTable->setPosition(glm::vec3(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) - newFontSize, 0));
		}
		//bottom left
		else if (thisViewportNumber == 3) {
			lap->setFontSize(18);
			lap->setPosition(glm::vec3(glutGet(GLUT_WINDOW_WIDTH) / 2 - 50, glutGet(GLUT_WINDOW_HEIGHT) / 2 - 18, 0));
			float newFontSize = scoreTable->getFontSize() / 3;
			scoreTable->setFontSize(newFontSize);
			scoreTable->setPosition(glm::vec3(0, glutGet(GLUT_WINDOW_HEIGHT) / 2 - newFontSize, 0));
		} 
		//bottom right
		else if (thisViewportNumber == 4) {
			lap->setFontSize(18);
			lap->setPosition(glm::vec3(glutGet(GLUT_WINDOW_WIDTH) - 50, glutGet(GLUT_WINDOW_HEIGHT) / 2 - 18, 0));
			float newFontSize = scoreTable->getFontSize() / 3;
			scoreTable->setFontSize(newFontSize);
			scoreTable->setPosition(glm::vec3(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2 - newFontSize, 0));
		}
	}
}


void UI::update(float dt) {
	Object2D::update(dt);
	healthBar->update(dt);
	gaugeBar->update(dt);
	lap->update(dt);
	map->update(dt);
	powerupBorder->update(dt);
	scoreTable->update(dt);
	if (powerupIcon != NULL)
		powerupIcon->update(dt);
}