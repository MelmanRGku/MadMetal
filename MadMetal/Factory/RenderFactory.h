#pragma once
#include "Objects\Model.h"
#include "Objects\Model2D.h"
#include "Global\Assets.h"

class RenderFactory
{
public:
	RenderFactory(){}
	~RenderFactory(){}

	enum RenderableObjects {
		RENDERABLE_OBJECT_CAR,
		RENDERABLE_OBJECT_PLANE,
		RENDERABLE_OBJECT_TRACK_DRIVABLE,
		RENDERABLE_OBJECT_TRACK_NON_DRIVABLE,
		RENDERABLE_OBJECT_BULLET_MEOW_MIX,
		RENDERABLE_OBJECT_BULLET_SUPER_VOLCANO,
		RENDERABLE_OBJECT_GGO,
		RENDERABLE_OBJECT_ATTACK_POWERUP,
		RENDERABLE_OBJECT_DISTURBED_TEXTURE,
		RENDERABLE_OBJECT_MAP_TEXTURE,
	};

	
	Model *makeRenderableObject(RenderableObjects objectToMake)
	{
		switch (objectToMake) {
		case RENDERABLE_OBJECT_CAR:
			return Assets::getModel("UglyCarWithGuns");
		case RENDERABLE_OBJECT_PLANE:
			return Assets::getModel("plane");
		case RENDERABLE_OBJECT_BULLET_MEOW_MIX:
			return Assets::getModel("bullet");
		case RENDERABLE_OBJECT_TRACK_DRIVABLE:
			return Assets::getModel("texturedTrack");
		case RENDERABLE_OBJECT_TRACK_NON_DRIVABLE:
			return Assets::getModel("texturedBorder");
		case RENDERABLE_OBJECT_BULLET_SUPER_VOLCANO:
			return Assets::getModel("scareMoon");
		case RENDERABLE_OBJECT_GGO:
			return Assets::getModel("GGO");
		case (RENDERABLE_OBJECT_ATTACK_POWERUP) :
			return Assets::getModel("sword");
		case RENDERABLE_OBJECT_DISTURBED_TEXTURE:
			return new Model2D(Assets::getTexture("tex1"));
		case RENDERABLE_OBJECT_MAP_TEXTURE:
			return new Model2D(Assets::getTexture("topViewMap"));
		}
	}
	
private: //members
	//enum of different objects to make
	
};