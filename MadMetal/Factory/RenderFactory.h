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
	};

	
	Model *makeRenderableObject(RenderableObjects objectToMake)
	{
		switch (objectToMake) {
		case RENDERABLE_OBJECT_CAR:
			return Assets::getModel("Ugly_Car");
		case RENDERABLE_OBJECT_PLANE:
			return Assets::getModel("plane");
		case RENDERABLE_OBJECT_BULLET_MEOW_MIX:
			return Assets::getModel("bullet");
		case RENDERABLE_OBJECT_TRACK_DRIVABLE:
			return Assets::getModel("texturedTrack");
		case RENDERABLE_OBJECT_TRACK_NON_DRIVABLE:
			return Assets::getModel("border");
		case RENDERABLE_OBJECT_BULLET_SUPER_VOLCANO:
			return Assets::getModel("scareMoon");
		}
	}
	
private: //members
	//enum of different objects to make
	
};