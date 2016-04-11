#pragma once

#include "Scene Manager\Scene.h"
#include "Objects\Object3D.h"
#include "Objects\EndingScreenCarInfoManager.h"
#include "Objects\EndingScreenUIScoreTable.h"

class EndingScene : public Scene
{
private:
	Audio &m_audio;
	Object3D *map;
	std::vector<ControllableTemplate *> m_players;
	std::vector<ControllableTemplate *> m_playersToReturn;
	Object3D *car1,
		*car2,
		*car3;
	EndingScreenCarInfoManager *car1Manager,
		*car2Manager,
		*car3Manager;
	EndingScreenUIScoreTable *scoreTable;
public:
	EndingScene(std::vector<ControllableTemplate *> playerTemplates, Audio& audioHandle);
	~EndingScene();
	void sortPlayers();
	bool simulateScene(double dt, SceneMessage &message);
	void setupSceneLights();
};

