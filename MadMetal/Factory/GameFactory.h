#pragma once
#include "PhysicsFactory.h"
#include "RenderFactory.h"
#include "AudioFactory.h"
#include "PxScene.h"
#include "Simulation/World.h"
#include "Simulation\PhysicsManager.h"
#include "Audio\Audio.h"
#include "Objects\TestObject.h"
#include "Objects\Audioable.h"
#include "Objects\Animatable.h"
#include "Objects\Physicable.h"
#include "Renderer\Renderable.h"
#include "Objects\DrivingStyleFast.h"
#include "Objects\Cars\MeowMix.h"

class GameFactory
{
public:
	GameFactory(World& world, PxScene& scene, Audio& audioHandle) :m_world(world), m_scene(scene)
	{
		m_physicsFactory = new PhysicsFactory();
		m_renderFactory = new RenderFactory();
		m_audioFactory = new AudioFactory(audioHandle);
	}
	~GameFactory()
	{
		delete m_audioFactory;
		delete m_renderFactory;
		delete m_physicsFactory;
	}

	enum Objects {
		OBJECT_MEOW_MIX,
		OBJECT_PLANE,
		OBJECT_WALL,
	};
	
	TestObject * makeObject(Objects objectToMake, PxTransform *pos, PxGeometry *geom)
	{
		long objectId = getNextId();

		switch (objectToMake) {
		case OBJECT_MEOW_MIX:
		{
			Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_CAR), true, true);
			Audioable *audioable = new Audioable();
			Animatable *animatable = new Animatable();
			Audio *audio = new Audio();

			PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5f, 0.3f, 0.1f);    //static friction, dynamic friction, restitution
			PxBase *base = m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_CAR, objectId, NULL, NULL, NULL, new DrivingStyleFast(material, material));
			
			PxVehicleDrive4W *physicalCar = static_cast<PxVehicleDrive4W *>(base);
			Physicable *physicable = new Physicable(physicalCar->getRigidDynamicActor());


			MeowMix *car = new MeowMix(objectId, *physicalCar, *audioable, *physicable, *animatable, *renderable, *audio);

			int k = (int)physicalCar->mWheelsSimData.getWheelData(0).mRadius * 2;
			PxVec3 physicalCarDimensions = physicalCar->getRigidDynamicActor()->getWorldBounds().getDimensions();
			car->updateScale(glm::vec3(physicalCarDimensions.x, physicalCarDimensions.y + k, physicalCarDimensions.z));

			m_world.addGameObject(car);
			m_scene.addActor(*physicalCar->getRigidDynamicActor());

			//Set the vehicle to rest in first gear.
			//Set the vehicle to use auto-gears.
			physicalCar->setToRestState();
			physicalCar->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
			physicalCar->mDriveDynData.setUseAutoGears(true);

			return car;
		}
		case OBJECT_PLANE:
		{
			Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_PLANE), true, true);
			Audioable *audioable = new Audioable();
			Animatable *animatable = new Animatable();
			Audio *audio = new Audio();

			PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
			PxRigidStatic *physicalPlane = static_cast<PxRigidStatic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_DRIVING_BOX, objectId, pos, geom, material, NULL));
			Physicable *physicable = new Physicable(physicalPlane);
			
			TestObject *plane = new TestObject(objectId, *audioable, *physicable, *animatable, *renderable, *audio);

			plane->updateScale(glm::vec3(glm::vec3(plane->getWorldBounds().getDimensions().x, 1, plane->getWorldBounds().getDimensions().z)));

			m_world.addGameObject(plane);
			m_scene.addActor(*physicalPlane);

			return plane;
		}
		case OBJECT_WALL:
		{
			Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_PLANE), true, true);
			Audioable *audioable = new Audioable();
			Animatable *animatable = new Animatable();
			Audio *audio = new Audio();

			PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
			PxRigidStatic *physicalWall = dynamic_cast<PxRigidStatic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_WALL, objectId, pos, geom, material, NULL));
			Physicable *physicable = new Physicable(physicalWall);

			TestObject *wall = new TestObject(objectId, *audioable, *physicable, *animatable, *renderable, *audio);

			m_world.addGameObject(wall);
			m_scene.addActor(*physicalWall);

			return wall;
		}
		}
	}
	
	static long getNextId() { return ++lastId; }

private: //members
	
	PhysicsFactory * m_physicsFactory;
	RenderFactory * m_renderFactory;
	AudioFactory * m_audioFactory;
	World& m_world;
	PxScene& m_scene;
	static long lastId;
	//enum of objects to create

private:
};