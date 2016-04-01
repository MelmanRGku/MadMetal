#pragma once
#include "Cars\Car.h"

class ExplosivelyDeliciousSuper : public Object3D
{
public:
	ExplosivelyDeliciousSuper(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car *owner) : Object3D(id, aable, pable, anable, rable, NULL)
	{
		m_owner = owner;
		m_damage = 200;
		maxLifeTime = 5;
	}
	virtual ~ExplosivelyDeliciousSuper()
	{

	}

	virtual void update(float dtMillis)
	{
		Object3D::update(dtMillis);
		m_animatable->updateRotation(glm::vec3(0, dtMillis * 1.5, 0));
		m_animatable->updateScale(glm::vec3( dtMillis * 15, dtMillis * 5, dtMillis * 15 ));
		m_animatable->updatePosition(glm::vec3(0, dtMillis * 3, 0));\
	}

	bool addCarHit(long id)
	{ 
		for (size_t i = 0; i < m_carsHit.size(); i++)
		{
			if (m_carsHit[i] == id)
			{
				return false;
			}
		}
		m_carsHit.push_back(id);
		return true;
	}
	float getDamage() { return m_damage; }
	Car * getOwner() { return m_owner; }

private:
	std::vector<long> m_carsHit;
	Car* m_owner;
	float m_damage;
};