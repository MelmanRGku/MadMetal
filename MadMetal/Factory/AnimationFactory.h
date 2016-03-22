#pragma once

#include "Renderer\Animation.h"
#include "Global\Assets.h"

class AnimationFactory
{
public:
	AnimationFactory(){}
	~AnimationFactory(){}

	enum Animations {
		ANIMATION_DEATHSTAR
	};

	Animation makeAnimation(Animations animationToMake)
	{
		Animation ret;
		switch (animationToMake) {
		case ANIMATION_DEATHSTAR:
		{
			ret.theModels.push_back(Assets::getModel("animation2"));
			ret.ticksPerFrame.push_back(1000);
			ret.theModels.push_back(Assets::getModel("animation3"));
			ret.ticksPerFrame.push_back(1000);
			ret.theModels.push_back(Assets::getModel("animation4"));
			ret.ticksPerFrame.push_back(1000);
		}
		}
		return ret;
	}
private: 

};