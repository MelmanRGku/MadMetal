#pragma once
#include "PhysicsManager.h"
#include "World.h"

class CollisionManager : public PxSimulationEventCallback
{
private:
	World &m_world;
	PxScene &m_scene;

private:
	void processBulletHit(long bulletId, long otherId);

public:
	CollisionManager(World &world, PxScene &scene);
	~CollisionManager();


	static PxFilterFlags TestFilterShader(
		PxFilterObjectAttributes attributes0, PxFilterData filterData0,
		PxFilterObjectAttributes attributes1, PxFilterData filterData1,
		PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize);

	//PxSumlationEventCallback
	void	onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);
	void	onTrigger(PxTriggerPair* pairs, PxU32 count);
	void	onConstraintBreak(PxConstraintInfo*, PxU32) {}
	void	onWake(PxActor**, PxU32) {}
	void	onSleep(PxActor**, PxU32){}
	//end PxSumlationEventCallback
};

