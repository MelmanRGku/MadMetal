#pragma once
#include "Object3D.h"
#include "Global\Assets.h"

class Particle : public Object3D
{
public:
	Particle(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, TestObject * parent) : Object3D(id, aable, pable, anable, rable, NULL)
	{
		m_parent = parent;
	}
	

	virtual ~Particle()
	{
		//do otherstuff
	}

private: // members
	bool m_alive;
	TestObject * m_parent;
private: //functions

};