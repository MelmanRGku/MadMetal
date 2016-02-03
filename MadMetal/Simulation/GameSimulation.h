#pragma once
#include <iostream>
#include "Scene.h"
#include "Objects/GameObject.h"
#include "Objects/Model.h"
#include "Objects/ObjModel.h"
#include "Renderer/VAO.h"
#include "Objects/ObjectUpdaters/ObjectPositionUpdater.h"
#include "Objects/ObjectUpdaters/ObjectRotationUpdater.h"
#include "Objects/ObjectUpdaters/ObjectUpdaterSequence.h"
#include "Objects/ObjectUpdaters/ObjectUpdaterParallel.h"


class GameSimulation : public Scene{
private:

	std::vector<ObjectUpdater *> updaters;
	
	void simulatePhysics();

	void simulateAnimation();

	void simulateAI();

	void simulatePlayers();

	void updateObjects(double dt);

public:
	GameSimulation();
	~GameSimulation();

	void simulate(double dt);

	void initialize();

	void setupBasicGameWorldObjects();
	
};