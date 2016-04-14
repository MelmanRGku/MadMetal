#pragma once
#include <iostream>
#include "Scene Manager\Scene.h"
#include "Global\Assets.h"
#include "Factory\GameFactory.h"
#include "Game Logic\ControllableTemplate.h"
#include "Game Logic\Controllable.h"
#include "Game Logic\PlayerControllable.h"
#include "Game Logic\AIControllable.h"
#include "Objects\DisplayMessage.h"
#include "CollisionManager.h"
#include "Objects\ObjectUpdaters\ObjectPositionUpdater.h"
#include "Objects\ObjectUpdaters\ObjectRotationUpdater.h"
#include "Objects\ObjectUpdaters\ObjectScaleUpdater.h"
#include "Objects\ObjectUpdaters\ObjectUpdaterSequence.h"
#include "Objects\ObjectUpdaters\ObjectUpdaterParallel.h"
#include "Audio\MusicManager.h"
#include "Objects\ScoreTable.h"
#include <time.h>

class Scene;
class Car;
class PhysicsManager;
class VehicleSceneQueryData; 
class ObjModelLoader;
class WaypointSystem;
class CollisionVolume;
class PositionManager;

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

	float getFinishLineBonus(int position);

	int getFirstPlace();

	void processInput();

	void setupPowerups();
	void setupTrains();
	void setupDeathPit();

private: //members
	std::vector<Controllable *> m_players;
	std::vector<PlayerControllable*> m_humanPlayers;
	std::vector<AIControllable*> m_aiPlayers;
	PxScene* m_scene;
	SceneMessage newMessage;

	PxVehicleDrivableSurfaceToTireFrictionPairs* gFrictionPairs = NULL; 
	PxVehicleDrivableSurfaceToTireFrictionPairs* createFrictionPairs(const PxMaterial* defaultMaterial);
	VehicleSceneQueryData*	gVehicleSceneQueryData = NULL;
	PxBatchQuery* gBatchQuery = NULL;
	GameFactory* m_gameFactory;
	Audio &m_audioHandle;
	Track* m_track;
	CollisionManager *manager;

	int m_numLapsVictory;
	int m_numPlayersFinishedRace;
	bool m_raceFinished;
	float m_raceFinishedCountdownSeconds;
	bool m_controlsPaused;
	float m_timeFinishedRace;

	CollisionVolume * m_startingCollisionVolume;
	CollisionVolume * m_midCollisionVolume;
	
	MusicManager *musicManager;
	PositionManager* m_positionManager;
	ScoreTable *m_scoreTable;


public:
	GameSimulation(std::vector<ControllableTemplate *> playerTemplates, Audio& audioHandle);
	~GameSimulation();

	bool simulateScene(double dt, SceneMessage &newMessage);

	void initialize();

	void setupBasicGameWorldObjects();
	void onPause();
	void onResume();

	std::vector<PlayerControllable*> *getHumanPlayers() { return &m_humanPlayers; }
	void setupSceneLights();
};