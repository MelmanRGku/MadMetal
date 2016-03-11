#pragma once

#include	<PxPhysicsAPI.h>
#include	<PxFoundation.h>
#include	<PxPhysics.h>

using namespace physx;

class PhysicsManager
{
public:
	static enum ObjectID
	{
		PLAYER = (1 << 0),
		PROJECTILE = (1 << 1),
		ENVIRONMENT = (1 << 2),
		WAYPOINT = (1 << 3),
		POWERUP = (1 << 4)
	};

private:
	PhysicsManager();
	PhysicsManager(PhysicsManager & manager);

public:
	virtual ~PhysicsManager();
	//void updatePhysics(float dt);
	static PxPhysics& getPhysicsInstance();
	static PxTolerancesScale& getScale();
	static void setupFiltering(PxRigidActor * actor, unsigned int actorId, unsigned int filterTargets, unsigned int extraActorInfo, unsigned int extraInteractionInfo);
	static PxDefaultAllocator *getAllocator() { return defaultAllocator_; }
	static PxFoundation& getFoundation();
	static PxCooking& getCookingInstance();
	static PxDefaultCpuDispatcher &getCpuDispatcher();

public:
	static void init();
	static void release();

private:
	static void initPhysicsSimulation();
	static void initCarPhysics();
	static void shutdownPhysicsSimualtion();

private: // members
	static PxFoundation* physicsFoundation_;

	static PxDefaultAllocator* defaultAllocator_;
	static PxDefaultErrorCallback* defaultErrorCallback_;

	static PxPhysics* topLevelPhysics_;
	static PxCooking* m_cooking;

	static PxDefaultCpuDispatcher* mCpuDispatcher;

	static PxTolerancesScale *m_scale;

	static bool initialized;

	static PxDefaultCpuDispatcher *cpuDispatcher;
};