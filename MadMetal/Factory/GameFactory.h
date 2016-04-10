#pragma once
#include "PhysicsFactory.h"
#include "RenderFactory.h"
#include "AudioFactory.h"
#include "PxScene.h"
#include "AnimationFactory.h"
#include "Simulation/World.h"
#include "Simulation\PhysicsManager.h"
#include "Audio\Audio.h"
#include "Objects\Audioable.h"
#include "Objects\Animatable.h"
#include "Objects\Physicable.h"
#include "Renderer\Renderable3D.h"
#include "Renderer\Renderable2D.h"

#include "Objects\Cars\DrivingStyleMeowMix.h"
#include "Objects\Cars\DrivingStyleExplosivelyDelicious.h"
#include "Objects\Cars\DrivingStyleGargantulous.h"


#include "Objects\Cars\MeowMix.h"

#include "Objects\Cars\ExplosivelyDelicious.h"
#include "Objects\Cars\Gargantulous.h"


#include "Objects\ExplosivelyDeliciousSuper.h"
#include "Objects\Bullet.h"
#include "Objects\MeowMixBullet.h"
#include "Objects\VolcanoGuySuperBullet.h"
#include "Objects\ExplosivelyDeliciousBullet.h"
#include "Objects\Track.h"
#include "Objects\BulletCarCollision.h"
#include "Objects\UI.h"
#include "Objects\DisplayMessage.h"
#include "Objects\Text3D.h"
#include "Objects\PowerUpShield.h"
#include "Objects\PowerUpSpeed.h"

#include "Objects\TexturedObject2D.h"
#include "Objects/ObjectUpdaters/ObjectPositionUpdater.h"
#include "Objects/ObjectUpdaters/ObjectRotationUpdater.h"
#include "Objects/ObjectUpdaters/ObjectScaleUpdater.h"
#include "Objects/ObjectUpdaters/ObjectUpdaterParallel.h"
#include "Objects/ObjectUpdaters/ObjectUpdaterSequence.h"
#include "Objects\AnimatedExplosion.h"
#include "Objects\TrainCar.h"
#include "PxQueryReport.h"
#include "Objects\VehicleSpecificationsMeowMix.h"

class GameFactory
{
public:
	enum Objects {
		OBJECT_MEOW_MIX,
		OBJECT_EXPLOSIVELY_DELICIOUS,
		OBJECT_GARGANTULOUS,
		OBJECT_BULLET_MEOW_MIX,
		OBJECT_MEOW_MIX_SUPER,
		OBJECT_BULLET_EXPLOSIVELY_DELICIOUS,
		OBJECT_BULLET_EXPLOSIVELY_DELICIOUS_RANDOM_DIRECTION,
		OBJECT_EXPLOSIVELY_DELICIOUS_SUPER,
		OBJECT_GARGANTULOUS_SUPER_VOLUME,
		OBJECT_GARGANTULOUS_SUPER_BULLET,
		OBJECT_GARGANTULOUS_BULLET,
		OBJECT_BULLET_SUPER_VOLCANO,
		OBJECT_PLANE,
		OBJECT_HEALTH_BAR,
		OBJECT_GAUGE_BAR,
		OBJECT_TEXT_2D,
		OBJECT_TRACK,
		OBJECT_TRACK_DRIVABLE,
		OBJECT_TRACK_NON_DRIVABLE,
		OBJECT_TRACK_WALLS,
		OBJECT_WAYPOINT,
		OBJECT_UI,
		OBJECT_DISPLAY_MESSAGE,
		OBJECT_TEXT_3D,
		OBJECT_COLLISION_VOLUME,
		OBJECT_POWERUP,
		OBJECT_SHIELD_POWERUP,
		OBJECT_SPEED_POWERUP,
		OBJECT_ATTACK_POWERUP,
		OBJECT_UI_DISTURBED_SONG_TEXTURE_THE_VENGEFUL_ONE,
		OBJECT_UI_SICK_PUPPIES_SONG_TEXTURE_YOURE_GOING_DOWN,
		OBJECT_UI_ALL_GOOD_THINGS_SONG_I_AM_THE_ENEMY,
		OBJECT_UI_METAL_MUSIC_SONG_DARKNESS_FALLS,
		OBJECT_UI_MAP,
		OBJECT_PARTICLE,
		OBJECT_EXPLOSION_1, 
		OBJECT_SMOKE_1,
		OBJECT_TRAIN_CAR,
		OBJECT_DEATH_PIT,
		OBJECT_ANIMATION_TEST,
		OBJECT_UI_POWERUP_BORDER_ICON,
		OBJECT_UI_SHIELD_POWERUP_ICON,
		OBJECT_UI_ATTACK_POWERUP_ICON,
		OBJECT_UI_SPEED_POWERUP_ICON,
		OBJECT_UI_SCORE_TABLE,
		OBJECT_SKY_BOX,
		OBJECT_GOO_MONSTER,
		OBJECT_BOMB_EXPLOSION,
		OBJECT_BLOB_SHADOW,
	};

	

	TestObject * makeObject(Objects objectToMake, PxTransform *pos, PxGeometry **geom, TestObject *parent);
	World& getWorld() { return m_world; }
	bool sceneRayCast(PxVec3 origin, PxVec3 direction, PxReal MaxDistance, PxRaycastBuffer &hit, PxHitFlags flag = PxHitFlags(PxHitFlag::eDEFAULT), PxQueryFilterData fd = PxQueryFilterData());
	bool sceneSweep(PxGeometry sweepShape, PxTransform origin, PxVec3 sweepDirection, float maxDistance, PxSweepBuffer& hit, PxHitFlags	hitFlags = PxHitFlags(PxHitFlag::eDEFAULT),	const PxQueryFilterData &filterData = PxQueryFilterData());

	static long getNextId() { 
		return ++lastId; 
	}

	static GameFactory *instance();

	static GameFactory *instance(World& world, PxScene& scene, Audio& audioHandle);

	static void release() {
		delete m_factory;
	}

	static void resetId()
	{
		lastId = 0;
	}

private:
	GameFactory(World& world, PxScene& scene, Audio& audioHandle);
	~GameFactory();

private: //members

	PhysicsFactory * m_physicsFactory;
	RenderFactory * m_renderFactory;
	AudioFactory * m_audioFactory;
	AnimationFactory * m_animationFactory;
	World& m_world;
	PxScene& m_scene;
	static long lastId;
	static GameFactory *m_factory;
	//enum of objects to create
};