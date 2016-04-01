#pragma once
#include "AnimatedModel.h"
#include "Global\Assets.h"

class AnimatedExplosion : public AnimatedModel
{
public:
	AnimatedExplosion(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, float duration, bool loop = false) : AnimatedModel(id, aable, pable, anable, rable, duration, loop)
	{
		
		m_sequence.push_back("explosion1_1");
		m_sequence.push_back("explosion1_2");
		m_sequence.push_back("explosion1_3");
		m_sequence.push_back("explosion1_4");
		m_sequence.push_back("explosion1_5");
		m_sequence.push_back("explosion1_6");
		m_sequence.push_back("explosion1_7");
		m_sequence.push_back("explosion1_8");
		m_sequence.push_back("explosion1_9");
		m_sequence.push_back("explosion1_10");
		m_sequence.push_back("explosion1_11");
		m_sequence.push_back("explosion1_12");
		m_sequence.push_back("explosion1_13");
		
	}
	virtual ~AnimatedExplosion() 
	{
		
	}

	virtual void update(float dt)
	{
		m_counter += dt;
		if (m_counter > m_duration)
		{
			if (m_loop)
			{
				m_counter = 0;
				setModel();

			}
			else {
				setHasToBeDeleted(true);
			}
		}
		else {
			setModel();
		}
		

	}

protected://members
	std::vector<char*> m_sequence;

private:
#define NUM_MODELS_IN_EXPLOSION_ANIMATION 13 
	void setModel()
	{
		
		float step = m_duration / NUM_MODELS_IN_EXPLOSION_ANIMATION;
		int progress = floor(m_counter / step);
		
		m_renderable->setModel(Assets::getModel(m_sequence[progress]));
	}

};