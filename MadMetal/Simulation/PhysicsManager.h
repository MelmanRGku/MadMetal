#pragma once

#include	<PxPhysicsAPI.h>
#include	<PxFoundation.h>
#include	<PxPhysics.h>

using namespace physx;

class PhysicsManager
{
public:
	PhysicsManager();
	virtual ~PhysicsManager();
	//void updatePhysics(float dt);
	PxPhysics& getPhysicsInstance();
	PxTolerancesScale& getScale();

private:
	void initPhysicsSimulation();
	void shutdownPhysicsSimualtion();

private: // members
	PxFoundation* physicsFoundation_;

	PxDefaultAllocator* defaultAllocator_;
	PxDefaultErrorCallback* defaultErrorCallback_;

	PxPhysics* topLevelPhysics_;

	PxDefaultCpuDispatcher* mCpuDispatcher;

	PxSceneDesc* sceneDesc;

	PxTolerancesScale *m_scale;
};