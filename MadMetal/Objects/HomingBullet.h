#pragma once

#include "Bullet.h"

class HomingBullet : public Object3D
{
public:
	HomingBullet(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car *owner) : Object3D(id, aable, pable, anable, rable, NULL)
	{
		//std::cout << "Made new homing bullet \n";
		m_isTracking = true;
		m_owner = owner;
		m_speed = 80;
		maxLifeTime = 10;
		m_trackingDelay = 1;
		PxVec3 startVelocity = m_owner->getCar().getRigidDynamicActor()->getLinearVelocity();
		PxRigidDynamic* actor = static_cast<PxRigidDynamic *>(&m_physicable->getActor());//
		actor->setLinearVelocity(startVelocity + PxVec3(0,20,0));
		

	}
	~HomingBullet()
	{

	}
	virtual void update(float dt)
	{
		Object3D::update(dt); 
		if ((m_trackingDelay -= dt) < 0)
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
				m_speed += dt * 6;
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
	Car * getOwner() { return m_owner; }
private:
	Car * m_targetCar;
	Car* m_owner;
	float m_speed;
	bool m_isTracking;
	PxVec3 m_targetLocation;
	float m_trackingDelay;
};
