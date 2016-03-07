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
#include "Renderer\Renderable.h"
#include "Objects\DrivingStyleFast.h"
#include "Objects\Cars\MeowMix.h"
#include "Objects\Bullet.h"
#include "Objects\MeowMixBullet.h"
#include "Objects\VolcanoGuySuperBullet.h"
#include "Objects\Track.h"

class GameFactory
{
public:
	enum Objects {
		OBJECT_MEOW_MIX,
		OBJECT_PLANE,
		OBJECT_WALL,
		OBJECT_BULLET_MEOW_MIX,
		OBJECT_BULLET_SUPER_VOLCANO,
		OBJECT_HEALTH_BAR,
		OBJECT_GAUGE_BAR,
		OBJECT_TEXT_2D,
		OBJECT_TRACK,
		OBJECT_TRACK_DRIVABLE,
		OBJECT_TRACK_NON_DRIVABLE,
		OBJECT_BUILDING
	};

	TestObject * makeObject(Objects objectToMake, PxTransform *pos, PxGeometry **geom, TestObject *parent);

	static long getNextId() { return ++lastId; }

	static GameFactory *instance();

	static GameFactory *instance(World& world, PxScene& scene, Audio& audioHandle);

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