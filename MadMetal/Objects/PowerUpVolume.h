#pragma once
#include "Object3D.h"
#include "Cars\Car.h"
#include "PowerUp.h"

class PowerUpVolume : public Object3D
{
public:
	PowerUpVolume(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car * owner) : Object3D(id, aable, pable, anable, rable)
	{
		m_car = owner;
		m_type = owner->getActivePowerUpType();
		counter = 0;
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
				updateRotation(glm::vec3(0, 360, 0) * dt / (50 * PowerUp::getPowerUpDuration(PowerUpType::DEFENSE)));
				PxVec3 dim = m_car->getCar().getRigidDynamicActor()->getWorldBounds().getDimensions();
				PxVec3 pos = m_car->getCar().getRigidDynamicActor()->getGlobalPose().p;
				//pos.y += dim.y / 2;
				m_physicable->getActor().setGlobalPose(PxTransform(pos));
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