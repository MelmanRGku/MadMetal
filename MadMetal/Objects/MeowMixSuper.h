#pragma once
#include "Object3D.h"
#include "PxQueryReport.h"
#include "Factory\GameFactory.h"
#include "GargantulousSuper.h"

#define BEAM_MAX_DISTANCE 300.f
#define BEAM_RADIUS 3
#define MAX_NUM_OF_RAYCAST_TESTS 100
class MeowMixSuper : public Object3D
{
public:
	MeowMixSuper(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car *owner) : Object3D(id, aable, pable, anable, rable, NULL)
	{
		m_owner = owner;
		m_animatable->setScale(glm::vec3(BEAM_RADIUS, BEAM_RADIUS, BEAM_MAX_DISTANCE));
	}

	virtual ~MeowMixSuper()
	{

	}

	virtual void update(float dtMillis)
	{

		if (m_owner->getSuperDurationRemaining() <= 0)
		{
			setHasToBeDeleted(true);
			return;
		}
		
		PxVec3 initialPosition = m_owner->getCar().getRigidDynamicActor()->getGlobalPose().p; 
		glm::vec3 forward = glm::normalize(m_owner->getForwardVector());
		PxVec3 forwardPhysx = PxVec3(forward.x, forward.y, forward.z);

		PxRaycastBuffer hit;
		PxQueryFilterData fd = PxQueryFilterData(PxQueryFlag::eSTATIC | PxQueryFlag::eDYNAMIC);
		PxVec3 rayDirection = PxVec3(forward.x, forward.y, forward.z);
		initialPosition += rayDirection * (m_owner->getCar().getRigidDynamicActor()->getWorldBounds().getDimensions().z + 1);
		initialPosition.y += 1;
		float beamDistance = 0;
		bool forceShutdownRaycast = false;
		float numOfRaycastsLeft = MAX_NUM_OF_RAYCAST_TESTS;

		do {
			numOfRaycastsLeft--;
			GameFactory::instance()->sceneRayCast(initialPosition + forwardPhysx * beamDistance, rayDirection, BEAM_MAX_DISTANCE - beamDistance, hit, PxHitFlag::eDEFAULT, fd);

			if (hit.hasBlock)
			{

				PxShape * shapes[1];
				hit.block.actor->getShapes(shapes, 1);
				std::cout << shapes[0]->getSimulationFilterData().word0 << std::endl;
				Car * car;
				switch (shapes[0]->getSimulationFilterData().word0)
				{
				case (COLLISION_FLAG_CHASSIS):
				case (COLLISION_FLAG_WHEEL):
					//std::cout << "hit a car" << std::endl;
					car = static_cast<Car *>(GameFactory::instance()->getWorld().findObject(shapes[0]->getSimulationFilterData().word2));
					if (car == m_owner)
					{
						std::cout << "Clipping with self. increase ray start offset \n";
					}
					else if (car->isAlive())
					{
						float damageToDeal = 200.f;
						float pointsToGet = car->getHealthRemaining();
						if (car->takeDamage(damageToDeal)) {
							m_owner->addDamageDealt(pointsToGet);
						}
					}
					forceShutdownRaycast = true;
					beamDistance += hit.block.distance + 0.2f;
					break;
				case (COLLISION_FLAG_GARGANTULOUS_SUPER_VOLUME) : // hitting the delicious collision volume
				{
					car = static_cast<GargantulousSuper *>(GameFactory::instance()->getWorld().findObject(shapes[0]->getSimulationFilterData().word2))->getOwner();
					PxVec3 toCar = (car->getActor().getGlobalPose().p - m_owner->getActor().getGlobalPose().p);
					if (toCar.magnitude() > BEAM_MAX_DISTANCE)
						break;
					PxVec3 forward = PxVec3(m_owner->getForwardVector().x, m_owner->getForwardVector().y, m_owner->getForwardVector().z).getNormalized();
					std::cout << abs(forward.cross(toCar).magnitude() - 1) << std::endl;
					if (abs(forward.cross(toCar).magnitude() - 1) < 0.2)
					{
						float damageToDeal = 200.f;
						float pointsToGet = car->getHealthRemaining();
						if (car->takeDamage(damageToDeal)) {
							m_owner->addDamageDealt(pointsToGet);
						}
					}
					forceShutdownRaycast = true;
					beamDistance += hit.block.distance + 0.2f;
					break;
				}
				case (COLLISION_FLAG_OBSTACLE):
				{
					forceShutdownRaycast = true;
					beamDistance += hit.block.distance + 0.2f;
					break;
				}
				case (COLLISION_FLAG_WAYPOINT):
				case (COLLISION_FLAG_COLLISION_VOLUME):
				{
					Object3D *volume = static_cast<Object3D *>(GameFactory::instance()->getWorld().findObject(shapes[0]->getSimulationFilterData().word2));
					forceShutdownRaycast = false;
					beamDistance += hit.block.distance + 0.2f + std::max(volume->getActor().getWorldBounds().getDimensions().x, volume->getActor().getWorldBounds().getDimensions().z) / 8;
					break;
				}
				default:
					beamDistance += hit.block.distance + 0.2f;
					break;
				}
			}
			else {
				forceShutdownRaycast = true;
				beamDistance = BEAM_MAX_DISTANCE;
			}

		} while (beamDistance <= BEAM_MAX_DISTANCE && !forceShutdownRaycast && numOfRaycastsLeft > 0);

		beamDistance = std::min(BEAM_MAX_DISTANCE, beamDistance);
		PxVec3 newPosition = initialPosition - PxVec3(0, 0, m_owner->getCar().getRigidDynamicActor()->getWorldBounds().getDimensions().z / 10) + PxVec3(forward.x, forward.y, forward.z) * beamDistance / 2;
		getActor().setGlobalPose(PxTransform(newPosition, m_owner->getCar().getRigidDynamicActor()->getGlobalPose().q));
		m_animatable->setRotation(glm::vec3(0, 0, 0));
		m_animatable->setScale(glm::vec3(BEAM_RADIUS, BEAM_RADIUS, beamDistance));
	}

private:
	Car * m_owner;
	
};