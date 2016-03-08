#include "CollisionManager.h"
#include "Objects\Cars\Car.h"
#include "Objects\Bullet.h"
#include "Objects\Waypoint.h"
#include "Factory/GameFactory.h"
#include "Objects\CollisionVolume.h"

CollisionManager::CollisionManager(World &world) : m_world(world)
{
}


CollisionManager::~CollisionManager()
{
}

PxFilterFlags CollisionManager::TestFilterShader(
	PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	// use a group-based mechanism for all other pairs:
	// - Objects within the default group (mask 0) always collide
	// - By default, objects of the default group do not collide
	//   with any other group. If they should collide with another
	//   group then this can only be specified through the filter
	//   data of the default group objects (objects of a different
	//   group can not choose to do so)
	// - For objects that are not in the default group, a bitmask
	//   is used to define the groups they should collide with
	if ((filterData0.word0 != 0 || filterData1.word0 != 0) &&
		!(filterData0.word0&filterData1.word1 || filterData1.word0&filterData0.word1))
		return PxFilterFlag::eSUPPRESS;

	////just notify about car-car collision
	//if ((filterData0.word0 == COLLISION_FLAG_CHASSIS || filterData0.word0 == COLLISION_FLAG_WHEEL) && (filterData1.word0 == COLLISION_FLAG_CHASSIS || filterData1.word0 == COLLISION_FLAG_WHEEL)) {
	//	pairFlags = PxPairFlag::eCONTACT_DEFAULT;
	//	return PxFilterFlag::eSUPPRESS;
	//}

	if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	{

		if (filterData0.word0 & filterData1.word1 || filterData0.word1 & filterData1.word0)
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;

		}
	}
	else {
		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		if (filterData0.word0 & filterData1.word1 || filterData0.word1 & filterData1.word0)
		{
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
		}


	}
	return PxFilterFlag::eDEFAULT;
}


void CollisionManager::processBulletHit(long bulletId, long otherId) {
	Bullet *bullet = static_cast<Bullet *>(m_world.findObject(bulletId));

	if (bullet == NULL)
		return;

	TestObject *otherObj = m_world.findObject(otherId);
	Car *car = dynamic_cast<Car *>(otherObj);

	if (car != NULL && car->getId() != bullet->getOwner()->getId()) {
		car->takeDamage(bullet->getDamage());
		bullet->getOwner()->addDamageDealt(bullet->getDamage());
		bullet->setHasToBeDeleted(true);
		GameFactory * factory = GameFactory::instance();
		BulletCarCollision * col = dynamic_cast<BulletCarCollision *> (factory->makeObject(GameFactory::OBJECT_BULLET_CAR_COLLISION, new PxTransform(bullet->getPosition().x, bullet->getPosition().y, bullet->getPosition().z), NULL, NULL));
		col->setHasToBeDeleted(true);
	}
	else if (car == NULL) {//if dynamic cast to car returns NULL its probably a wall so get rid of it
		bullet->setHasToBeDeleted(true);
	}
	
}

void CollisionManager::processWaypointHit(long waypointId, long otherId)
{
	Waypoint *waypoint = dynamic_cast<Waypoint *>(m_world.findObject(waypointId));

	if (waypoint == NULL)
		return;

	TestObject *otherObj = m_world.findObject(otherId);
	Car *car = dynamic_cast<Car *>(otherObj);

	if (car != NULL) 
	{
		if (car->setCurrentWaypoint(waypoint)) {
			if (car->getCurrentWaypoint()->isFinish()) {
				car->incrementLap();
			}
		}
		
		//std::cout << "car is: " << car->getId() << " waypoint is: " << waypoint->getId() << "\n";
	}
}

void CollisionManager::processCollisionVolumeHit(long volumeId, long otherId)
{
	CollisionVolume *collisionVolume = dynamic_cast<CollisionVolume *>(m_world.findObject(volumeId));

	if (collisionVolume == NULL)
		return;

	TestObject *otherObj = m_world.findObject(otherId);
	Car *car = dynamic_cast<Car *>(otherObj);

	if (car != NULL)
	{
		if (collisionVolume->getId() == 0)
		{
			std::cout << "car: " << car->getId() << " collided with starting CollisionVolume \n";
			car->setStartingCollisionVolumeFlag(true);
		}
		else if (collisionVolume->getId() == 1)
		{
			std::cout << "car: " << car->getId() << " collided with mid CollisionVolume \n";
			car->setMidCollisionVolumeFlag(true);
		}
	}
	}

void CollisionManager::processCarCarHit(long car1Id, long car2Id) {
	Car *car1 = dynamic_cast<Car *>(m_world.findObject(car1Id));
	Car *car2 = dynamic_cast<Car *>(m_world.findObject(car2Id));
	//car1->getCar().getRigidDynamicActor()->addForce(PxVec3(0, -500, 0));
	//car2->getCar().getRigidDynamicActor()->addForce(PxVec3(0, -500, 0));
}

void CollisionManager::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	for (PxU32 i = 0; i < nbPairs; i++) {
		PxU32 firstObj = pairs[i].shapes[0]->getSimulationFilterData().word0,
			secondObj = pairs[i].shapes[1]->getSimulationFilterData().word0;

		if ((firstObj == COLLISION_FLAG_CHASSIS || firstObj == COLLISION_FLAG_WHEEL) && (secondObj == COLLISION_FLAG_CHASSIS || secondObj == COLLISION_FLAG_WHEEL)) {
			processCarCarHit(pairs[i].shapes[0]->getSimulationFilterData().word2, pairs[i].shapes[1]->getSimulationFilterData().word2);
		}
	}
}


void CollisionManager::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	for (int i = 0; i < count; i++) {
		if (pairs[i].triggerShape->getSimulationFilterData().word0 == COLLISION_FLAG_BULLET) {
			processBulletHit(pairs[i].triggerShape->getSimulationFilterData().word2, pairs[i].otherShape->getSimulationFilterData().word2);
		}
		else if (pairs[i].triggerShape->getSimulationFilterData().word0 == COLLISION_FLAG_WAYPOINT)
		{
			processWaypointHit(pairs[i].triggerShape->getSimulationFilterData().word2, pairs[i].otherShape->getSimulationFilterData().word2);
		}
		else if (pairs[i].triggerShape->getSimulationFilterData().word0 == COLLISION_FLAG_CHASSIS)
		{

		}
		else if (pairs[i].triggerShape->getSimulationFilterData().word0 == COLLISION_FLAG_COLLISION_VOLUME)
		{
			processCollisionVolumeHit(pairs[i].triggerShape->getSimulationFilterData().word2, pairs[i].otherShape->getSimulationFilterData().word2);
		}
	}

}
