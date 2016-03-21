#pragma once
#include "Objects\Model.h"
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
		RENDERABLE_OBJECT_SHIELD_POWERUP,
		RENDERABLE_OBJECT_EXPLOSION1_1,
		RENDERABLE_OBJECT_EXPLOSION1_2,
		RENDERABLE_OBJECT_EXPLOSION1_3,
		RENDERABLE_OBJECT_EXPLOSION1_4,
		RENDERABLE_OBJECT_EXPLOSION1_5,
		RENDERABLE_OBJECT_EXPLOSION1_6,
		RENDERABLE_OBJECT_EXPLOSION1_7,
		RENDERABLE_OBJECT_EXPLOSION1_8,
		RENDERABLE_OBJECT_EXPLOSION1_9,
		RENDERABLE_OBJECT_EXPLOSION1_10,
		RENDERABLE_OBJECT_EXPLOSION1_11,
		RENDERABLE_OBJECT_EXPLOSION1_12,
		RENDERABLE_OBJECT_EXPLOSION1_13,

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
		case RENDERABLE_OBJECT_SHIELD_POWERUP:
			return Assets::getModel("sheildPowerUp");
		case RENDERABLE_OBJECT_EXPLOSION1_1:
			return Assets::getModel("explosion1_1");
		case RENDERABLE_OBJECT_EXPLOSION1_2:
			return Assets::getModel("explosion1_2");
		case RENDERABLE_OBJECT_EXPLOSION1_3:
			return Assets::getModel("explosion1_3");
		case RENDERABLE_OBJECT_EXPLOSION1_4:
			return Assets::getModel("explosion1_4");
		case RENDERABLE_OBJECT_EXPLOSION1_5:
			return Assets::getModel("explosion1_5");
		case RENDERABLE_OBJECT_EXPLOSION1_6:
			return Assets::getModel("explosion1_6");
		case RENDERABLE_OBJECT_EXPLOSION1_7:
			return Assets::getModel("explosion1_7");
		case RENDERABLE_OBJECT_EXPLOSION1_8:
			return Assets::getModel("explosion1_8");
		case RENDERABLE_OBJECT_EXPLOSION1_9:
			return Assets::getModel("explosion1_9");
		case RENDERABLE_OBJECT_EXPLOSION1_10:
			return Assets::getModel("explosion1_10");
		case RENDERABLE_OBJECT_EXPLOSION1_11:
			return Assets::getModel("explosion1_11");
		case RENDERABLE_OBJECT_EXPLOSION1_12:
			return Assets::getModel("explosion1_12");
		case RENDERABLE_OBJECT_EXPLOSION1_13:
			return Assets::getModel("explosion1_13");
		}
	}
	
private: //members
	//enum of different objects to make
	
};