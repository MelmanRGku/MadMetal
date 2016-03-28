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
		RENDERABLE_OBJECT_MEOWMIX,
		RENDERABLE_OBJECT_MEOWMIX_DEATHSTAR,
		RENDERABLE_OBJECT_MEOWMIXBODY,
		RENDERABLE_OBJECT_MEOWMIXWHEEL,
		RENDERABLE_OBJECT_MEOWMIXDEATHSTAR,
		RENDERABLE_OBJECT_GARGANTULOUS,
		RENDERABLE_OBJECT_PLANE,
		RENDERABLE_OBJECT_TRACK_DRIVABLE,
		RENDERABLE_OBJECT_TRACK_NON_DRIVABLE,
		RENDERABLE_OBJECT_TRACK_WALLS,
		RENDERABLE_OBJECT_BULLET_MEOW_MIX,
		RENDERABLE_OBJECT_MEOW_MIX_SUPER,
		RENDERABLE_OBJECT_BULLET_EXPLOSIVELY_DELICIOUS,
		RENDERABLE_OBJECT_EXPLOSIVELY_DELICIOUS_SUPER,
		RENDERABLE_OBJECT_BULLET_SUPER_VOLCANO,
		RENDERABLE_OBJECT_GARGANTULOUS_SUPER_VOLUME,
		RENDERABLE_OBJECT_GARGANTULOUS_SUPER_BULLET,
		RENDERABLE_OBJECT_GARGANTULOUS_BULLET,
		
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
		RENDERABLE_OBJECT_SPEED_POWERUP_ACTIVE,

		RENDERABLE_OBJECT_PARTICLE_POWERUP_ATTACK,
		RENDERABLE_OBJECT_PARTICLE_POWERUP_DEFENSE,
		RENDERABLE_OBJECT_PARTICLE_POWERUP_SPEED,


		RENDERABLE_OBJECT_ATTACK_POWERUP_ICON,
		RENDERABLE_OBJECT_DEFENSE_POWERUP_ICON,
		RENDERABLE_OBJECT_SPEED_POWERUP_ICON,
		RENDERABLE_OBJECT_POWERUP_BORDER,


		RENDERABLE_OBJECT_UI_HEALTH_HUD,
		RENDERABLE_OBJECT_UI_HEALTH_CURRENT,
		RENDERABLE_OBJECT_UI_HEALTH_LOST,

		RENDERABLE_OBJECT_UI_GAUGE_HUD,
		RENDERABLE_OBJECT_UI_GAUGE_CURRENT,
		RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_1,
		RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_2,
		RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_3,
		RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_4,
		RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_5,
		RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_6,
	};

	
	Model *makeRenderableObject(RenderableObjects objectToMake)
	{
		switch (objectToMake) {
		case RENDERABLE_OBJECT_CAR:
			return Assets::getModel("Gargantulous");
		case RENDERABLE_OBJECT_MEOWMIX_DEATHSTAR:
			return Assets::getModel("MeowmixDeathComplete");
		case RENDERABLE_OBJECT_MEOWMIX:
			return Assets::getModel("Meowmix");
		case RENDERABLE_OBJECT_MEOWMIXWHEEL:
			return Assets::getModel("MeowmixWheel");
		case RENDERABLE_OBJECT_MEOWMIXBODY:
			return Assets::getModel("Meowmixbody");
		case RENDERABLE_OBJECT_MEOWMIXDEATHSTAR:
			return Assets::getModel("MeowmixDeathComplete");
		case RENDERABLE_OBJECT_GARGANTULOUS:
			return Assets::getModel("Gargantulous");
		case RENDERABLE_OBJECT_EXPLOSIVELY_DELICIOUS:
			return Assets::getModel("twisted1");
		case RENDERABLE_OBJECT_TRAIN_CAR:
			return Assets::getModel("train_car");
		case RENDERABLE_OBJECT_PLANE:
			return Assets::getModel("plane");
		case RENDERABLE_OBJECT_BULLET_MEOW_MIX:
			return Assets::getModel("bullet");
		case RENDERABLE_OBJECT_GARGANTULOUS_BULLET:
			return Assets::getModel("Rocket");
		case RENDERABLE_OBJECT_BULLET_SUPER_VOLCANO:
			return Assets::getModel("scareMoon");
		case RENDERABLE_OBJECT_TRACK_DRIVABLE:
			return Assets::getModel("trackv2ground");
		case RENDERABLE_OBJECT_TRACK_NON_DRIVABLE:
			return Assets::getModel("trackv2enviro");
		case RENDERABLE_OBJECT_TRACK_WALLS:
			return Assets::getModel("trackv2walls");
		case RENDERABLE_OBJECT_BULLET_EXPLOSIVELY_DELICIOUS:
			return Assets::getModel("explosively_delicious_bullet");
		case RENDERABLE_OBJECT_EXPLOSIVELY_DELICIOUS_SUPER:
			return Assets::getModel("explosively_delicious_super");
		case RENDERABLE_OBJECT_MEOW_MIX_SUPER:
			return Assets::getModel("meowmix_superbeam"); //put in beam!
		case RENDERABLE_OBJECT_GARGANTULOUS_SUPER_BULLET:
			return Assets::getModel("Meteor");
		case RENDERABLE_OBJECT_GARGANTULOUS_SUPER_VOLUME:
			return Assets::getModel("Meteor"); //do something for the super model
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
		case RENDERABLE_OBJECT_SPEED_POWERUP_ACTIVE:
			return Assets::getModel("speedPowerupModel");
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
		case RENDERABLE_OBJECT_ATTACK_POWERUP_ICON:
			return new Model2D(Assets::getTexture("life_steal"));
		case RENDERABLE_OBJECT_DEFENSE_POWERUP_ICON:
			return new Model2D(Assets::getTexture("shield-reflect"));
		case RENDERABLE_OBJECT_SPEED_POWERUP_ICON:
			return new Model2D(Assets::getTexture("speed_icon"));
		case RENDERABLE_OBJECT_POWERUP_BORDER:
			return new Model2D(Assets::getTexture("powerup_border"));
		case RENDERABLE_OBJECT_UI_HEALTH_HUD:
			return new Model2D(Assets::getTexture("health_hud"));
		case RENDERABLE_OBJECT_UI_HEALTH_CURRENT:
			return new Model2D(Assets::getTexture("current_health"));
		case RENDERABLE_OBJECT_UI_HEALTH_LOST:
			return new Model2D(Assets::getTexture("health_lost"));
		case RENDERABLE_OBJECT_UI_GAUGE_HUD:
			return new Model2D(Assets::getTexture("super_guage"));
		case RENDERABLE_OBJECT_UI_GAUGE_CURRENT:
			return new Model2D(Assets::getTexture("current_super_amount"));
		case RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_1:
			return new Model2D(Assets::getTexture("super_animation_1"));
		case RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_2:
			return new Model2D(Assets::getTexture("super_animation_2"));
		case RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_3:
			return new Model2D(Assets::getTexture("super_animation_3"));
		case RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_4:
			return new Model2D(Assets::getTexture("super_animation_4"));
		case RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_5:
			return new Model2D(Assets::getTexture("super_animation_5"));
		case RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_6:
			return new Model2D(Assets::getTexture("super_animation_6"));
		}
	}
	
private: //members
	//enum of different objects to make
	
};