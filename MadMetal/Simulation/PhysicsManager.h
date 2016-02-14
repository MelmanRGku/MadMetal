#pragma once

#include	<PxPhysicsAPI.h>
#include	<PxFoundation.h>
#include	<PxPhysics.h>



using namespace physx;

class PhysicsManager
{
public:
	enum ObjectID
	{
		PLAYER = (1 << 0),
		PROJECTILE = (1 << 1),
		ENVIRONMENT = (1 << 2),
		WAYPOINT = (1 << 3),
		POWERUP = (1 << 4)
	};

	PhysicsManager();
	virtual ~PhysicsManager();
	//void updatePhysics(float dt);
	PxPhysics& getPhysicsInstance();
	PxTolerancesScale& getScale();
	void static setupFiltering(PxRigidActor * actor, unsigned int actorId, unsigned int filterTargets, unsigned int extraActorInfo, unsigned int extraInteractionInfo);
	
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