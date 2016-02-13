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
#include "Objects/Car.h"
#include "PhysicsManager.h"
#include "Objects\ObjectCreators\SnippetVehicleRaycast.h"

class GameSimulation : public Scene{
private:
	void simulatePhysics(float dt);

	void simulateAnimation();

	void simulateAI();

	void simulatePlayers(double dt);

	void updateObjects(double dt);

	void createPhysicsScene();

private: //members
	std::vector<ObjectUpdater *> updaters;
	std::vector<PlayerControllable *> m_players;

	PhysicsManager& m_physicsHandler;
	PxScene* m_scene;
	PxCooking* m_cooking;
	PxVehicleDrive4W *car;
	PxF32 gVehicleModeTimer;
	PxI32 gVehicleOrderProgress = 0;
	bool gVehicleOrderComplete = false;
	PxVehicleDrivableSurfaceToTireFrictionPairs* gFrictionPairs = NULL; 
	PxVehicleDrivableSurfaceToTireFrictionPairs* createFrictionPairs(const PxMaterial* defaultMaterial);
public:
	GameSimulation(PhysicsManager& physicsInstance, PlayerControllable * player);
	~GameSimulation();

	bool simulateScene(double dt, SceneMessage &newMessage);

	void initialize();

	void setupBasicGameWorldObjects();

	void incrementDrivingMode(float dt);
	
};