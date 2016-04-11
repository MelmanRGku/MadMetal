#pragma once

#include "Bullet.h"

class GargantulousBullet : public Bullet
{
private:
	Car *m_toFollow;
	float m_speed;
public:
	GargantulousBullet(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car *owner) : Bullet(id, aable, pable, anable, rable, owner)
	{
		m_damage = 25;
	}

	~GargantulousBullet()
	{

	}

	void setSpeed(float speed) {
		m_speed = speed;
	}

	virtual void update(float dt) { 
		Bullet::update(dt);
		if (m_toFollow != NULL) {
			if (m_toFollow->getHealthRemaining() >= 0) {
				PxVec3 currentLocation = m_physicable->getActor().getGlobalPose().p;
				PxVec3 distanceToTarget = m_toFollow->getActor().getGlobalPose().p - currentLocation;
				if (distanceToTarget.magnitude() > 1)
				{
					PxVec3 newVelocity = distanceToTarget.getNormalized()  * m_speed;
					static_cast<PxRigidDynamic *>(&m_physicable->getActor())->setLinearVelocity(newVelocity);
				}
			}
			else {
				m_toFollow = NULL;
			}
		}
	}

	void setToFollow(Car *car) {
		m_toFollow = car;
	}

};

