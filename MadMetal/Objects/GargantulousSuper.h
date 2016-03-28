#pragma once
#include "Cars\Car.h"
#include "Factory\GameFactory.h"
#include "HomingBullet.h"


#define GARGANTULOUS_FIRE_RATE_SECONDS 0.5 

class GargantulousSuper : public Object3D
{
public:
	GargantulousSuper(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car * owner) : Object3D(id, aable, pable, anable, rable, NULL)
	{
		m_owner = owner;
		m_fireCounter = 0;
	}
	virtual ~GargantulousSuper()
	{


	}

	void addTarget(Car * toShoot)
	{
		//std::cout << "added new target to list \n";
		m_targets.push_back(toShoot);
	}

	virtual void update(float dtMillis)
	{
		m_physicable->getActor().setGlobalPose(m_owner->getActor().getGlobalPose());
		if (m_owner->getSuperDurationRemaining() <= 0 )//|| !m_owner->isAlive())
		{
			setHasToBeDeleted(true);
			return;
		}

		m_fireCounter -= dtMillis;

		if (m_fireCounter <= 0)
		{

			if (m_targets.size())
			{
				//std::cout << "Firing at new target \n";
				m_fireCounter = GARGANTULOUS_FIRE_RATE_SECONDS;
				PxGeometry * geom[1];
				geom[0] = new PxSphereGeometry(4);
				HomingBullet * bullet = static_cast<HomingBullet*> (GameFactory::instance()->makeObject(GameFactory::OBJECT_GARGANTULOUS_SUPER_BULLET, &m_owner->getActor().getGlobalPose(), geom, m_owner));
				delete geom[0];
				bullet->setTarget(m_targets[0]);
				m_targets.erase(m_targets.begin());


			}
		}

	}
	Car * getOwner(){ return m_owner; }
private:
	std::vector<Car *> m_targets;
	Car * m_owner;
	float m_fireCounter;

};