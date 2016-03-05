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
		RENDERABLE_OBJECT_BULLET,
		RENDERABLE_OBJECT_TRACK,
	};

	
	Model *makeRenderableObject(RenderableObjects objectToMake)
	{
		switch (objectToMake) {
		case RENDERABLE_OBJECT_CAR:
			return Assets::getModel("Ugly_Car");
		case RENDERABLE_OBJECT_PLANE:
			return Assets::getModel("plane");
		case RENDERABLE_OBJECT_BULLET:
			return Assets::getModel("bullet");
		case RENDERABLE_OBJECT_TRACK:
			return Assets::getModel("TRACK");

		}
	}
	
private: //members
	//enum of different objects to make
	
};