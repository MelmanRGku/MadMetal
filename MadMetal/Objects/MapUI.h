#pragma once

#include "TexturedObject2D.h"

class Controllable;

class MapUI : public TexturedObject2D
{
private:
	glm::vec3 trackMinBounds, trackMaxBounds, trackSize;
	std::vector<Controllable *> *players;
	std::vector<glm::vec3> playerSizes;
	Controllable *mainPlayer;
	Model2D *playerModel;
public:
	MapUI(long id, Audioable *aable, Animatable *anable, Renderable2D *rable);
	virtual ~MapUI();
	void setPlayers(std::vector<Controllable *> *players);
	void setMainPlayer(Controllable *player) { mainPlayer = player; }
	void setTrackBounds(glm::vec3 min, glm::vec3 max) { trackMinBounds = min; trackMaxBounds = max; trackSize = max - min; }
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void setPlayerModel(Model2D *playerModel) { this->playerModel = playerModel; }
};

