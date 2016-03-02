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
		}
	}
	
private: //members
	//enum of different objects to make
	
};