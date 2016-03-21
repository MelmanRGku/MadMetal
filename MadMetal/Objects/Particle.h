#pragma once
#include "Object3D.h"
#include "Global\Assets.h"

class Particle : public Object3D
{
public:
	Particle(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable, NULL)
	{
		//do stuff
	}
	

	virtual ~Particle()
	{
		//do otherstuff
	}

	void setAlive(bool alive) 
	{
		
		m_alive = alive;
		if (m_alive == alive)
		{
			m_renderable->setModel(Assets::getModel("sword"));
			static_cast<Renderable3D *>(m_renderable)->adjustModel(true, true);
		}
		else {
			m_renderable->setModel(NULL);
		}
	}

	PxRigidActor* getRigidActor() { 
		PxRigidActor* ptr = static_cast<PxRigidActor*>(&m_physicable->getActor());
		
		
		return ptr;
	}
private: // members
	bool m_alive;
private: //functions

};