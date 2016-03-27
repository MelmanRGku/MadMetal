#pragma once

#include "Bullet.h"

class HomingBullet : public Bullet
{
public:
	HomingBullet(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car *owner) : Bullet(id, aable, pable, anable, rable, owner)
	{
		std::cout << "Made new homing bullet \n";
		m_isTracking = true;
		m_damage = 50;
		m_speed = 60;
		maxLifeTime = 10;
		m_trackingDelay = 1;
		PxVec3 startVelocity = m_owner->getCar().getRigidDynamicActor()->getLinearVelocity() + PxVec3(0,20,0);
		static_cast<PxRigidDynamic *>(&m_physicable->getActor())->setLinearVelocity(startVelocity);

	}
	~HomingBullet()
	{

	}
	virtual void update(float dt)
	{
		Bullet::update(dt); 
		if (m_trackingDelay -= dt < 0)
		{
			if (m_isTracking)
			{
				if (m_targetCar != NULL && m_targetCar->isAlive())
				{
					m_targetLocation = m_targetCar->getCar().getRigidDynamicActor()->getGlobalPose().p;
				}
				else {
					m_isTracking = false;
				}
			}

			PxVec3 currentLocation = m_physicable->getActor().getGlobalPose().p;
			PxVec3 distanceToTarget = m_targetLocation - currentLocation;
			if (distanceToTarget.magnitude() > 1)
			{
				PxVec3 newVelocity = distanceToTarget.getNormalized()  * m_speed;
				static_cast<PxRigidDynamic *>(&m_physicable->getActor())->setLinearVelocity(newVelocity);
			}
			else {
				setHasToBeDeleted(true);
			}
		}
		

	}

	void setTarget(Car* target)
	{
		m_targetCar = target;
	}

private:
	Car * m_targetCar;
	float m_speed;
	bool m_isTracking;
	PxVec3 m_targetLocation;
	float m_trackingDelay;
};
