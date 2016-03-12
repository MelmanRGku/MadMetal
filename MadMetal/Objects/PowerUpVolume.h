#pragma once
#include "TestObject.h"
#include "Cars\Car.h"
#include "PowerUp.h"

class PowerUpVolume : public TestObject
{
public:
	PowerUpVolume(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable *rable, Car * owner) : TestObject(id, aable, pable, anable, rable)
	{
		m_car = owner;
		m_type = owner->getActivePowerUpType();
	}
	virtual ~PowerUpVolume() { m_car = NULL; }
	void update(float dt)
	{
		if (m_car != NULL)
		{
			if (m_car->getActivePowerUpType() != m_type || m_car->getActivePowerUpType() == NULL)
			{
				setHasToBeDeleted(true);
				
			}
			else {
				//std::cout << "Updating sheild position \n";
				m_physicable->getActor().setGlobalPose(m_car->getActor().getGlobalPose());
			}
		}
	}
	bool isOwner(Car* toCheck) { return toCheck == m_car; }
	Car* getOwner(){ return m_car; }
protected://members
	Car* m_car;
	PowerUpType m_type;
private:

};