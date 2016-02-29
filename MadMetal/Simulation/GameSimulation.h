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
class WayPointSystem;
class VehicleSceneQueryData; 
class ObjModelLoader;

class GameSimulation : public Scene, public PxSimulationEventCallback{
private:
	void simulatePhysics(double dt);

	void simulateAnimation();

	void simulateAI();

	void simulatePlayers(double dt);

	void updateObjects(double dt);

	void createPhysicsScene();

private: //members
	std::vector<Controllable *> m_players;
	std::vector<PlayerControllable*> m_humanPlayers;
	// TODO REMOVE FROM MEMBER VARIABLES
	PxScene* m_scene;
	// TODO REMOVE FROM MEMBER VARIABLES
	PxVehicleDrive4W *car;
	PxF32 gVehicleModeTimer;
	PxI32 gVehicleOrderProgress = 0;
	bool gVehicleOrderComplete = false;
	PxVehicleDrivableSurfaceToTireFrictionPairs* gFrictionPairs = NULL; 
	PxVehicleDrivableSurfaceToTireFrictionPairs* createFrictionPairs(const PxMaterial* defaultMaterial);
	VehicleSceneQueryData*	gVehicleSceneQueryData = NULL;
	PxBatchQuery* gBatchQuery = NULL;
	GameFactory* m_gameFactory;

public:
	GameSimulation(std::vector<ControllableTemplate *> playerTemplates, Audio& audioHandle);
	~GameSimulation();

	bool simulateScene(double dt, SceneMessage &newMessage);

	void initialize();

	void setupBasicGameWorldObjects();

	void	onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);
			
	void	onTrigger(PxTriggerPair* pairs, PxU32 count);
		
	virtual void							onConstraintBreak(PxConstraintInfo*, PxU32) {}
	virtual void							onWake(PxActor**, PxU32) {}
	virtual void							onSleep(PxActor**, PxU32){}
	
};