#pragma once
#include <iostream>
#include "Scene Manager\Scene.h"
#include "Global\Assets.h"

class Scene;
class Car;
class PhysicsManager;
class WayPointSystem;
class ObjectUpdater;
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
	std::vector<ObjectUpdater *> updaters;
	std::vector<PlayerControllable *> m_players;
	WayPointSystem * m_wayPoints;
	PhysicsManager& m_physicsHandler;
	PxScene* m_scene;
	PxCooking* m_cooking;
	PxVehicleDrive4W *car;
	PxF32 gVehicleModeTimer;
	PxI32 gVehicleOrderProgress = 0;
	bool gVehicleOrderComplete = false;
	PxVehicleDrivableSurfaceToTireFrictionPairs* gFrictionPairs = NULL; 
	PxVehicleDrivableSurfaceToTireFrictionPairs* createFrictionPairs(const PxMaterial* defaultMaterial);
	VehicleSceneQueryData*	gVehicleSceneQueryData = NULL;
	PxBatchQuery* gBatchQuery = NULL;
	ObjModelLoader *m_objLoader;
public:
	GameSimulation(PhysicsManager& physicsInstance, PlayerControllable * player);
	~GameSimulation();

	bool simulateScene(double dt, SceneMessage &newMessage);

	void initialize();

	void setupBasicGameWorldObjects();

	void	onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);
			
	void	onTrigger(PxTriggerPair* pairs, PxU32 count);
		
	virtual void							onConstraintBreak(PxConstraintInfo*, PxU32) {}
	virtual void							onWake(PxActor**, PxU32) {}
	virtual void							onSleep(PxActor**, PxU32){}
	
	void incrementDrivingMode(float dt);
};