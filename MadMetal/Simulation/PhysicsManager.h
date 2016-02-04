#pragma once

#include	<PxPhysicsAPI.h>
#include	<PxFoundation.h>
#include	<PxPhysics.h>
class GameWorld;

using namespace physx;

class PhysicsManager
{
public:
	PhysicsManager(GameWorld & world);
	virtual ~PhysicsManager();
	void updatePhysics(float dt);

private:
	void initPhysicsSimulation();
	void shutdownPhysicsSimualtion();


private: // members
	PxFoundation* physicsFoundation_;

	GameWorld & world_;

	PxDefaultAllocator* defaultAllocator_;
	PxDefaultErrorCallback* defaultErrorCallback_;

	PxPhysics* topLevelPhysics_;

	PxDefaultCpuDispatcher* mCpuDispatcher;

	PxScene* mScene;

	PxSceneDesc* sceneDesc;
};