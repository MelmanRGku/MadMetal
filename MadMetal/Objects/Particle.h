#pragma once
#include "Object3D.h"

class Particle : public Object3D
{
public:
	Particle(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable)
	{
		//do stuff
	}
	

	virtual ~Particle()
	{
		//do otherstuff
	}

	void setAlive(bool alive) 
	{
		if (m_alive = alive)
		{
			m_renderable->setModel(Assets::getModel("sword"));
		}
		else {
			m_renderable->setModel(NULL);
		}
	}

	PxRigidDynamic* getRigidActor() { return static_cast<PxRigidDynamic*>(&m_physicable->getActor()); }
private: // members
	bool m_alive;
private: //functions

};