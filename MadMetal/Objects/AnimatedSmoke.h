#pragma once

#include "AnimatedModel.h"
#include "Global\Assets.h"

class AnimatedSmoke : public AnimatedModel
{
public:
	AnimatedSmoke(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, float duration, bool loop = false);
	virtual ~AnimatedSmoke();

	virtual void update(float dt);

protected://members
	std::vector<char*> m_sequence;

private:
	void setModel();

};

