#pragma once
#include "Object3D.h"
#include "Global\Assets.h"

class AnimatedModel : public Object3D
{
public:
	AnimatedModel(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, float duration, bool loop = false) : Object3D(id, aable, pable, anable, rable, NULL)
	{
		
		m_counter = 0;
		m_duration = duration;
		m_loop = loop;
	}
	virtual ~AnimatedModel() {  }

	virtual void update(float dt)
	{
		
		m_counter += dt;
		if (m_counter > m_duration)
		{
			if (m_loop)
			{
				m_counter = 0;
			}
			else {
				setHasToBeDeleted(true);
			}
		}
		setModel();
	}
	
protected://members
	float m_counter;
	float m_duration;
	bool m_loop;
	

private:
	virtual void setModel(){}

};