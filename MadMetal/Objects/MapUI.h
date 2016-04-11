#pragma once

#define PERCENTAGE_OF_MAP_TO_DISPLAY 60

#include "TexturedObject2D.h"

class Controllable;

class MapUI : public TexturedObject2D
{
private:
	glm::vec3 trackMinBounds, trackMaxBounds, trackSize;
	std::vector<Controllable *> *players;
	std::vector<glm::vec3> playerSizes;
	Controllable *mainPlayer;
	Model2D *meowModel;
	Model2D *explosiveModel;
	Model2D *gargModel;


	//shared amongst draw functions
	glm::vec4 partOfTheMapDisplayed;
	glm::vec2 mainPlayerPosOnMapUI;
	glm::vec4 cutOffs;

	void drawBackground();
	void drawMap();
	void drawPlayers();
public:
	MapUI(long id, Audioable *aable, Animatable *anable, Renderable2D *rable);
	virtual ~MapUI();
	void setPlayers(std::vector<Controllable *> *players);
	void setMainPlayer(Controllable *player) { mainPlayer = player; }
	void setTrackBounds(glm::vec3 min, glm::vec3 max) { trackMinBounds = min; trackMaxBounds = max; trackSize = max - min; }
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void setmeowModel(Model2D *meowModel) { this->meowModel = meowModel; }
	void setexplosiveModel(Model2D *explosiveModel) { this->explosiveModel = explosiveModel; }
	void setgargModel(Model2D *gargModel) { this->gargModel = gargModel; }
	float clip(float value, float lower, float upper);
	glm::vec4 clip(glm::vec4 value, float lower, float upper);
};

