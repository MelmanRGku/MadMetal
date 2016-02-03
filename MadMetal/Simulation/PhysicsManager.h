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
	

private:
	void initPhysicsSimulation();
	void shutdownPhysicsSimualtion();

private: // members
	PxFoundation* physicsFoundation_;

	PxDefaultAllocator* defaultAllocator_;
	PxDefaultErrorCallback* defaultErrorCallback_;

	PxPhysics* topLevelPhysics_;

	PxDefaultCpuDispatcher* mCpuDispatcher;
};