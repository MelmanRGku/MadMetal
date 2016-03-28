#pragma once
#include "PowerUpVolume.h"

class PowerUpSpeed : public PowerUpVolume
{
public:
	PowerUpSpeed(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car * owner) : PowerUpVolume(id, aable, pable, anable, rable, owner)
	{
		m_animatable->setPosition(glm::vec3(0, -2, owner->getCar().getRigidDynamicActor()->getWorldBounds().getDimensions().z - 1));

	}
	virtual ~PowerUpSpeed()
	{

	}

	virtual void update(float dtMillis)
	{
		PowerUpVolume::update(dtMillis);
		m_physicable->getActor().setGlobalPose(m_car->getActor().getGlobalPose());

	}

private://members
	
private:

};