#pragma once
#include "Object3D.h"

class MeowMixSuper : public Object3D
{
public:
	MeowMixSuper(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car *owner) : Object3D(id, aable, pable, anable, rable, NULL)
	{
		m_owner = owner;
		m_damage = 150;
	}

	virtual ~MeowMixSuper()
	{

	}

	virtual void update(float dtMillis)
	{
		PxTransform transform = m_owner->getCar().getRigidDynamicActor()->getGlobalPose();
		glm::vec3 distance = glm::normalize(m_owner->getForwardVector());
		distance *= 50;
		transform.p += PxVec3(distance.x, distance.y, distance.z);
		getActor().setGlobalPose(transform);
		
	}

private:
	Car * m_owner;
	float m_damage;
};