#include "CollisionManager.h"
#include "Objects\Cars\Car.h"
#include "Objects\Bullet.h"

CollisionManager::CollisionManager(World &world, PxScene &scene) : m_world(world), m_scene(scene)
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
		car->takeDamage(15);
		m_world.deleteObject(bulletId);
		
	}
	else if (car == NULL) {
		m_world.deleteObject(bulletId);
	}

}

void CollisionManager::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	/*int i = 0;
	PxShape *shapes[1];
	pairHeader.actors[0]->getShapes(shapes, 1);
	i = shapes[0]->getSimulationFilterData().word2;
	std::cout << i << std::endl;
	pairHeader.actors[1]->getShapes(shapes, 1);
	i = shapes[0]->getSimulationFilterData().word2;
	std::cout << i << std::endl;*/
}


void CollisionManager::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	for (int i = 0; i < count; i++) {
		if (pairs[i].triggerShape->getSimulationFilterData().word0 == COLLISION_FLAG_BULLET) {
			processBulletHit(pairs[i].triggerShape->getSimulationFilterData().word2, pairs[i].otherShape->getSimulationFilterData().word2);
		}
	}

}
