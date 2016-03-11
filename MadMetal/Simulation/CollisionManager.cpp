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

	//just notify about car-car collision
	if ((filterData0.word0 == COLLISION_FLAG_CHASSIS || filterData0.word0 == COLLISION_FLAG_WHEEL) && (filterData1.word0 == COLLISION_FLAG_CHASSIS || filterData1.word0 == COLLISION_FLAG_WHEEL)) {
		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		return PxFilterFlag::eCALLBACK;
	}

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
		PxTransform *pos = new PxTransform(bullet->getPosition().x, bullet->getPosition().y, bullet->getPosition().z);
		BulletCarCollision * col = dynamic_cast<BulletCarCollision *> (factory->makeObject(GameFactory::OBJECT_BULLET_CAR_COLLISION, pos, NULL, NULL));
		delete pos;
		delete col;
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
			//	car->incrementLap();
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
			//std::cout << "car: " << car->getId() << " collided with starting CollisionVolume \n";
			car->setStartingCollisionVolumeFlag(true);
		}
		else if (collisionVolume->getId() == 1)
		{
			//std::cout << "car: " << car->getId() << " collided with mid CollisionVolume \n";
			car->setMidCollisionVolumeFlag(true);
		}
	}
	}

void CollisionManager::processCarCarHit(long car1Id, long car2Id) {
	Car *car1 = dynamic_cast<Car *>(m_world.findObject(car1Id));
	Car *car2 = dynamic_cast<Car *>(m_world.findObject(car2Id));
	glm::vec3 car1Pos = car1->getFullPosition(),
		car2Pos = car2->getFullPosition();
	glm::vec3 vectorBetweenCars = glm::normalize(car2Pos - car1Pos);
	glm::vec3 car1ForwardVector = car1->getForwardVector();
	glm::vec3 car2ForwardVector = car2->getForwardVector();

	float car1Mass = car1->getDrivingStyle().getChassisMass();
	float car2Mass = car2->getDrivingStyle().getChassisMass();
	//if car1 hit car2
	if (glm::dot(car1ForwardVector, vectorBetweenCars) > 0) {
		glm::vec3 forceToApply = car1->getCar().computeForwardSpeed() * car1Mass * car1ForwardVector / 7.f;
		car2->getCar().getRigidDynamicActor()->addForce(PxVec3(forceToApply.x, forceToApply.y, forceToApply.z), PxForceMode::eIMPULSE);
		car1->getCar().getRigidDynamicActor()->addForce(-PxVec3(forceToApply.x, forceToApply.y, forceToApply.z), PxForceMode::eIMPULSE);
	}
	//car2 hit car1
	if (glm::dot(car2ForwardVector, -vectorBetweenCars) > 0) {
		glm::vec3 forceToApply = car2->getCar().computeForwardSpeed() * car2Mass * car2ForwardVector / 7.f;
		car1->getCar().getRigidDynamicActor()->addForce(PxVec3(forceToApply.x, forceToApply.y, forceToApply.z), PxForceMode::eIMPULSE);
		car2->getCar().getRigidDynamicActor()->addForce(-PxVec3(forceToApply.x, forceToApply.y, forceToApply.z), PxForceMode::eIMPULSE);
	}
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

PxFilterFlags CollisionManager::pairFound(PxU32 pairID, PxFilterObjectAttributes attributes0, PxFilterData filterData0, const PxActor *a0, const PxShape *s0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1, const PxActor *a1, const PxShape *s1, PxPairFlags &pairFlags) {
	processCarCarHit(filterData0.word2, filterData1.word2);
	return PxFilterFlags(PxFilterFlag::eDEFAULT);
}


void CollisionManager::pairLost(PxU32 pairID, PxFilterObjectAttributes attributes0, PxFilterData filterData0, PxFilterObjectAttributes attributes1, PxFilterData filterData1, bool objectDeleted){

}


bool CollisionManager::statusChange(PxU32 &pairID, PxPairFlags &pairFlags, PxFilterFlags &filterFlags) {
	return false;
}
