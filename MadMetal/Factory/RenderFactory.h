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
		RENDERABLE_OBJECT_UI_DISTURBED_SONG_TEXTURE_THE_VENGEFUL_ONE,
		RENDERABLE_OBJECT_UI_SICK_PUPPIES_SONG_TEXTURE_YOURE_GOING_DOWN,
		RENDERABLE_OBJECT_UI_ALL_GOOD_THINGS_SONG_I_AM_THE_ENEMY,
		RENDERABLE_OBJECT_UI_METAL_MUSIC_SONG_DARKNESS_FALLS,
		RENDERABLE_OBJECT_MAP_TEXTURE,
		RENDERABLE_OBJECT_PLAYER_ON_UI_MAP_TEXTURE,
		RENDERABLE_OBJECT_ANIMATION_TEST
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
		case RENDERABLE_OBJECT_UI_DISTURBED_SONG_TEXTURE_THE_VENGEFUL_ONE:
			return new Model2D(Assets::getTexture("disturbed"));
		case RENDERABLE_OBJECT_UI_SICK_PUPPIES_SONG_TEXTURE_YOURE_GOING_DOWN:
			return new Model2D(Assets::getTexture("sickpuppies-goingdown"));
		case RENDERABLE_OBJECT_UI_ALL_GOOD_THINGS_SONG_I_AM_THE_ENEMY:
			return new Model2D(Assets::getTexture("allgoodthings-iamtheenemy"));
		case RENDERABLE_OBJECT_UI_METAL_MUSIC_SONG_DARKNESS_FALLS:
			return new Model2D(Assets::getTexture("metalmusic-darknessfalls"));
		case RENDERABLE_OBJECT_MAP_TEXTURE:
			return new Model2D(Assets::getTexture("map"));
		case RENDERABLE_OBJECT_PLAYER_ON_UI_MAP_TEXTURE:
			return new Model2D(Assets::getTexture("red-car-top-view"));
		case (RENDERABLE_OBJECT_ANIMATION_TEST) :
			return Assets::getModel("animation1");
		}
	}
	
private: //members
	//enum of different objects to make
	
};