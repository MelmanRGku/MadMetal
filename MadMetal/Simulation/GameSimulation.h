#pragma once
#include <iostream>
#include "Scene.h"
#include "Objects/GameObject.h"
#include "Objects/Model.h"
#include "Objects/ObjModel.h"
#include "Renderer/VAO.h"
#include "PhysicsManager.h"
#include "Objects/ObjectUpdaters/ObjectPositionUpdater.h"
#include "Objects/ObjectUpdaters/ObjectRotationUpdater.h"
#include "Objects/ObjectUpdaters/ObjectUpdaterSequence.h"
#include "Objects/ObjectUpdaters/ObjectUpdaterParallel.h"


class GameSimulation : public Scene{
private:

	std::vector<ObjectUpdater *> updaters;
	
	PhysicsManager *physics;

	void simulatePhysics(float dt);

	void simulateAnimation();

	void simulateAI();

	void simulatePlayers();

	void updateObjects(double dt);

public:
	GameSimulation();
	~GameSimulation();

	void simulate(float dt);

	void initialize();

	void setupBasicGameWorldObjects();
	
};