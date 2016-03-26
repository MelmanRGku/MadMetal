#pragma once
#include "Object3D.h"
#include "Cars\Car.h"
#include "PowerUp.h"

class PowerUpVolume : public Object3D
{
public:
	PowerUpVolume(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car * owner) : Object3D(id, aable, pable, anable, rable, NULL)
	{
		m_car = owner;
		m_type = owner->getActivePowerUpType();
		counter = 0;
	}
	virtual ~PowerUpVolume() { m_car = NULL; }
	virtual void update(float dt)
	{
		if (m_car != NULL)
		{
			if (m_car->getActivePowerUpType() != m_type || m_car->getActivePowerUpType() == NULL)
			{
				setHasToBeDeleted(true);
			}
		}
	}
	bool isOwner(Car* toCheck) { return toCheck == m_car; }
	Car* getOwner(){ return m_car; }
protected://members
	Car* m_car;
	PowerUpType m_type;
	float counter;
private:

};