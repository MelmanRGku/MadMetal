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
		RENDERABLE_OBJECT_EXPLOSIVELY_DELICIOUS,
		RENDERABLE_OBJECT_PLANE,
		RENDERABLE_OBJECT_TRACK_DRIVABLE,
		RENDERABLE_OBJECT_TRACK_NON_DRIVABLE,
		RENDERABLE_OBJECT_BULLET_MEOW_MIX,
		RENDERABLE_OBJECT_BULLET_EXPLOSIVELY_DELICIOUS,
		RENDERABLE_OBJECT_EXPLOSIVELY_DELICIOUS_SUPER,
		RENDERABLE_OBJECT_GGO,
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
		RENDERABLE_OBJECT_TRAIN_CAR,
		
		
		RENDERABLE_OBJECT_UI_DISTURBED_SONG_TEXTURE_THE_VENGEFUL_ONE,
		RENDERABLE_OBJECT_UI_SICK_PUPPIES_SONG_TEXTURE_YOURE_GOING_DOWN,
		RENDERABLE_OBJECT_UI_ALL_GOOD_THINGS_SONG_I_AM_THE_ENEMY,
		RENDERABLE_OBJECT_UI_METAL_MUSIC_SONG_DARKNESS_FALLS,
		RENDERABLE_OBJECT_MAP_TEXTURE,
		RENDERABLE_OBJECT_PLAYER_ON_UI_MAP_TEXTURE,
		RENDERABLE_OBJECT_ANIMATION_TEST,
		//powerups
		RENDERABLE_OBJECT_ATTACK_POWERUP_PICKUP,
		RENDERABLE_OBJECT_DEFENSE_POWERUP_PICKUP,
		RENDERABLE_OBJECT_SPEED_POWERUP_PICKUP,

		RENDERABLE_OBJECT_SHIELD_POWERUP_ACTIVE,

		RENDERABLE_OBJECT_PARTICLE_POWERUP_ATTACK,
		RENDERABLE_OBJECT_PARTICLE_POWERUP_DEFENSE,
		RENDERABLE_OBJECT_PARTICLE_POWERUP_SPEED,
	};

	
	Model *makeRenderableObject(RenderableObjects objectToMake)
	{
		switch (objectToMake) {
		case RENDERABLE_OBJECT_CAR:
			return Assets::getModel("uglyCarWithGuns");
		case RENDERABLE_OBJECT_EXPLOSIVELY_DELICIOUS:
			return Assets::getModel("twisted1");
		case RENDERABLE_OBJECT_TRAIN_CAR:
			return Assets::getModel("train_car");
		case RENDERABLE_OBJECT_PLANE:
			return Assets::getModel("plane");
		case RENDERABLE_OBJECT_BULLET_MEOW_MIX:
			return Assets::getModel("bullet");
		case RENDERABLE_OBJECT_TRACK_DRIVABLE:
			return Assets::getModel("trackv2ground");
		case RENDERABLE_OBJECT_TRACK_NON_DRIVABLE:
			return Assets::getModel("trackv2enviro");
		case RENDERABLE_OBJECT_BULLET_EXPLOSIVELY_DELICIOUS:
			return Assets::getModel("explosively_delicious_bullet");
		case RENDERABLE_OBJECT_EXPLOSIVELY_DELICIOUS_SUPER:
			return Assets::getModel("explosively_delicious_super");
		case RENDERABLE_OBJECT_GGO:
			return Assets::getModel("GGO");
		case (RENDERABLE_OBJECT_ATTACK_POWERUP_PICKUP) :
			return Assets::getModel("attackPowerUp_pickup");
		case (RENDERABLE_OBJECT_DEFENSE_POWERUP_PICKUP) :
			return Assets::getModel("defensePowerUp_pickup");
		case (RENDERABLE_OBJECT_SPEED_POWERUP_PICKUP) :
			return Assets::getModel("speedPowerUp_pickup");
		case RENDERABLE_OBJECT_SHIELD_POWERUP_ACTIVE:
			return Assets::getModel("sheildPowerUp");
		case RENDERABLE_OBJECT_PARTICLE_POWERUP_ATTACK:
			return Assets::getModel("powerup_particle_attack");
		case RENDERABLE_OBJECT_PARTICLE_POWERUP_DEFENSE:
			return Assets::getModel("powerup_particle_defense");
		case RENDERABLE_OBJECT_PARTICLE_POWERUP_SPEED:
			return Assets::getModel("powerup_particle_speed");
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