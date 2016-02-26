#pragma once
#include "PhysicsFactory.h"
#include "RenderFactory.h"
#include "AudioFactory.h"
#include "PxScene.h"
#include "Simulation/World.h"
#include "Simulation\PhysicsManager.h"
#include "Audio\Audio.h"

class GameFactory
{
public:
	GameFactory(World& world, PxScene& scene, PhysicsManager manager, Audio& audioHandle) :m_world(world), m_scene(scene)
	{
		m_physicsFactory = new PhysicsFactory(manager);
		m_renderFactory = new RenderFactory();
		m_audioFactory = new AudioFactory(audioHandle);
	}
	~GameFactory()
	{
		delete m_audioFactory;
		delete m_renderFactory;
		delete m_physicsFactory;
	}

	/*
	Object * makeObject(Enum objectToMake)
	{
		Big switch statement utilizing the enum object types
	}
	*/

private: //members
	
	PhysicsFactory * m_physicsFactory;
	RenderFactory * m_renderFactory;
	AudioFactory * m_audioFactory;
	World& m_world;
	PxScene& m_scene;
	//enum of objects to create

private:
};