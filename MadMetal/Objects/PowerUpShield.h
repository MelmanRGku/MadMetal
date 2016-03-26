#pragma once
#include "PowerUpVolume.h"
#include "ObjectUpdaters\ObjectRotationUpdater.h"
class PowerUpShield : public PowerUpVolume
{
public:
	
	PowerUpShield(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car * owner) : PowerUpVolume(id, aable, pable, anable, rable, owner)
	{

	}

	virtual ~PowerUpShield()
	{

	}
	virtual void update(float dt)
	{
		PowerUpVolume::update(dt);
		//std::cout << "Updating sheild position \n";
		updateRotation(glm::vec3(0, 360, 0) * dt / (50 * PowerUp::getPowerUpDuration(PowerUpType::DEFENSE)));
		PxVec3 dim = m_car->getCar().getRigidDynamicActor()->getWorldBounds().getDimensions();
		PxVec3 pos = m_car->getCar().getRigidDynamicActor()->getGlobalPose().p;
		//pos.y += dim.y / 2;
		m_physicable->getActor().setGlobalPose(PxTransform(pos));
	}
private://members

private:

};