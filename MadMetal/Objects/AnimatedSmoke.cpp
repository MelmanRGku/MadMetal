#include "AnimatedSmoke.h"

AnimatedSmoke::AnimatedSmoke(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, float duration, bool loop) : AnimatedModel(id, aable, pable, anable, rable, duration, loop)
{

	m_sequence.push_back("smoke_1");
	m_sequence.push_back("smoke_2");
	m_sequence.push_back("smoke_3");
	m_sequence.push_back("smoke_4");
	m_sequence.push_back("smoke_5");
	m_sequence.push_back("smoke_6");
	m_sequence.push_back("smoke_7");
	m_sequence.push_back("smoke_8");
	m_sequence.push_back("smoke_9");
	m_sequence.push_back("smoke_10");
	m_sequence.push_back("smoke_11");
	m_sequence.push_back("smoke_12");
	m_sequence.push_back("smoke_13");
	m_sequence.push_back("smoke_14");

}
AnimatedSmoke::~AnimatedSmoke()
{

}

void AnimatedSmoke::update(float dt)
{
	static_cast<PxRigidDynamic*>(&getActor())->addForce(PxVec3(0, 50, 0));

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

#define NUM_MODELS_IN_EXPLOSION_ANIMATION 14 
void AnimatedSmoke::setModel()
{

	float step = m_duration / NUM_MODELS_IN_EXPLOSION_ANIMATION;
	int progress = floor(m_counter / step);

	if (progress == NUM_MODELS_IN_EXPLOSION_ANIMATION)
		progress = NUM_MODELS_IN_EXPLOSION_ANIMATION - 1;

	m_renderable->setModel(Assets::getModel(m_sequence[progress]));
}
