#include "CollisionManager.h"
#include "Objects\Cars\Car.h"
#include "Objects\Bullet.h"

CollisionManager::CollisionManager(World &world, PxScene &scene) : m_world(world), m_scene(scene)
{
}


CollisionManager::~CollisionManager()
{
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
