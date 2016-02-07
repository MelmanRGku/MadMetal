#pragma once
#include <iostream>
#include "Scene Manager\Scene.h"
#include "Objects/Object.h"
#include "Objects/Model.h"
#include "Objects/ObjectUpdaters/ObjectPositionUpdater.h"
#include "Objects/ObjectUpdaters/ObjectRotationUpdater.h"
#include "Objects/ObjectUpdaters/ObjectUpdaterSequence.h"
#include "Objects/ObjectUpdaters/ObjectUpdaterParallel.h"
#include "Objects/ObjectLoaders/ObjModelLoader.h"
#include "Objects/RenderableObject.h"
#include "PhysicsManager.h"

class GameSimulation : public Scene{
private:

	std::vector<ObjectUpdater *> updaters;
	
	PhysicsManager *physics;

	void simulatePhysics();

	void simulateAnimation();

	void simulateAI();

	void simulatePlayers();

	void updateObjects(double dt);

public:
	GameSimulation();
	~GameSimulation();

	bool simulateScene(double dt, SceneMessage &newMessage);

	void initialize();

	void setupBasicGameWorldObjects();
	
};