#pragma once
#include <iostream>
#include "Scene Manager\Scene.h"
#include "Global\Assets.h"
#include "Factory\GameFactory.h"
#include "Game Logic\ControllableTemplate.h"
#include "Game Logic\Controllable.h"
#include "Game Logic\PlayerControllable.h"
#include "Game Logic\AIControllable.h"

class Scene;
class Car;
class PhysicsManager;
class VehicleSceneQueryData; 
class ObjModelLoader;
class WaypointSystem;

class GameSimulation : public Scene{
private:
	void simulatePhysics(double dt);

	void simulateAnimation();

	void simulateAI();

	void simulatePlayers(double dt);

	void updateObjects(double dt);

	void createPhysicsScene();

	void createWaypointPositions(glm::vec3 centerOfPlane, float length, float width);

	void pauseControls(bool pause);

private: //members
	std::vector<Controllable *> m_players;
	std::vector<PlayerControllable*> m_humanPlayers;
	std::vector<AIControllable*> m_aiPlayers;
	PxScene* m_scene;

	PxVehicleDrivableSurfaceToTireFrictionPairs* gFrictionPairs = NULL; 
	PxVehicleDrivableSurfaceToTireFrictionPairs* createFrictionPairs(const PxMaterial* defaultMaterial);
	VehicleSceneQueryData*	gVehicleSceneQueryData = NULL;
	PxBatchQuery* gBatchQuery = NULL;
	GameFactory* m_gameFactory;
	WaypointSystem* m_waypointSystem;
	bool m_controlsPaused;
	Audio &m_audioHandle;

public:
	GameSimulation(std::vector<ControllableTemplate *> playerTemplates, Audio& audioHandle);
	~GameSimulation();

	bool simulateScene(double dt, SceneMessage &newMessage);

	void initialize();

	void setupBasicGameWorldObjects();

};