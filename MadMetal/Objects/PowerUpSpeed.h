#pragma once
#include "PowerUpVolume.h"

class PowerUpSpeed : public PowerUpVolume
{
public:
	PowerUpSpeed(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car * owner) : PowerUpVolume(id, aable, pable, anable, rable, owner)
	{

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