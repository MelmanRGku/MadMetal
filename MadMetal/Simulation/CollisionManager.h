#pragma once
#include "PhysicsManager.h"
#include "World.h"

class CollisionManager : public PxSimulationEventCallback, public PxSimulationFilterCallback
{
private:
	World &m_world;

private:
	void processBulletHit(long bulletId, long otherId);
	void processWaypointHit(long waypointId, long otherId);
	void processCollisionVolumeHit(long volumeId, long otherId);
	void processCarCarHit(long car1Id, long car2Id);
	void processPowerUpHit(long powerupId, long otherId);
	void processShieldPowerUpHit(long shieldPowerUpId, long otherId);
	void processSpeedPowerUpHit(long speedPowerUpId, long otherId);

public:
	CollisionManager(World &world);
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

	//PxSimulationFilterCallback
	PxFilterFlags pairFound(PxU32 pairID, PxFilterObjectAttributes attributes0, PxFilterData filterData0, const PxActor *a0, const PxShape *s0, PxFilterObjectAttributes attributes1, PxFilterData filterData1, const PxActor *a1, const PxShape *s1, PxPairFlags &pairFlags);
	void pairLost(PxU32 pairID, PxFilterObjectAttributes attributes0, PxFilterData filterData0, PxFilterObjectAttributes attributes1, PxFilterData filterData1, bool objectDeleted);
	bool statusChange(PxU32 &pairID, PxPairFlags &pairFlags, PxFilterFlags &filterFlags);
	//end PxSimulationFilterCallback
};

