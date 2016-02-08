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
	void simulatePhysics(float dt);

	void simulateAnimation();

	void simulateAI();

	void simulatePlayers();

	void updateObjects(double dt);

	void createPhysicsScene();

private: //members
	std::vector<ObjectUpdater *> updaters;

	PhysicsManager& m_physicsHandler;
	PxScene* m_scene;
public:
	GameSimulation(PhysicsManager& physicsInstance);
	~GameSimulation();

	bool simulateScene(double dt, SceneMessage &newMessage);

	void initialize();

	void setupBasicGameWorldObjects();
	
};