#pragma once
#include "PhysicsFactory.h"
#include "RenderFactory.h"
#include "AudioFactory.h"
#include "PxScene.h"
#include "Simulation/World.h"
#include "Simulation\PhysicsManager.h"
#include "Audio\Audio.h"
#include "Objects\Audioable.h"
#include "Objects\Animatable.h"
#include "Objects\Physicable.h"
#include "Renderer\Renderable3D.h"
#include "Renderer\Renderable2D.h"
#include "Objects\DrivingStyleFast.h"
#include "Objects\Cars\MeowMix.h"
#include "Objects\Bullet.h"
#include "Objects\MeowMixBullet.h"
#include "Objects\VolcanoGuySuperBullet.h"
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

class GameFactory
{
public:
	enum Objects {
		OBJECT_MEOW_MIX,
		OBJECT_PLANE,
		OBJECT_BULLET_MEOW_MIX,
		OBJECT_BULLET_SUPER_VOLCANO,
		OBJECT_HEALTH_BAR,
		OBJECT_GAUGE_BAR,
		OBJECT_TEXT_2D,
		OBJECT_TRACK,
		OBJECT_TRACK_DRIVABLE,
		OBJECT_TRACK_NON_DRIVABLE,
		OBJECT_WAYPOINT,
		OBJECT_BULLET_CAR_COLLISION,
		OBJECT_UI,
		OBJECT_DISPLAY_MESSAGE,
		OBJECT_TEXT_3D,
		OBJECT_COLLISION_VOLUME,
		OBJECT_POWERUP,
		OBJECT_SHIELD_POWERUP,
		OBJECT_SPEED_POWERUP,
		OBJECT_UI_DISTURBED_SONG,
		OBJECT_UI_MAP,

	};

	TestObject * makeObject(Objects objectToMake, PxTransform *pos, PxGeometry **geom, TestObject *parent);

	static long getNextId() { return ++lastId; }

	static GameFactory *instance();

	static GameFactory *instance(World& world, PxScene& scene, Audio& audioHandle);

	static void release() {
		delete m_factory;
	}

private:
	GameFactory(World& world, PxScene& scene, Audio& audioHandle);
	~GameFactory();

private: //members

	PhysicsFactory * m_physicsFactory;
	RenderFactory * m_renderFactory;
	AudioFactory * m_audioFactory;
	World& m_world;
	PxScene& m_scene;
	static long lastId;
	static GameFactory *m_factory;
	//enum of objects to create
};