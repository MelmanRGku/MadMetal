#include "GameFactory.h"

long GameFactory::lastId = 0;

GameFactory *GameFactory::m_factory = NULL;

GameFactory::GameFactory(World& world, PxScene& scene, Audio& audioHandle) :m_world(world), m_scene(scene)
{
	m_physicsFactory = new PhysicsFactory();
	m_renderFactory = new RenderFactory();
	m_audioFactory = new AudioFactory(audioHandle);
}

GameFactory::~GameFactory()
{
	delete m_audioFactory;
	delete m_renderFactory;
	delete m_physicsFactory;
}

TestObject * GameFactory::makeObject(Objects objectToMake, PxTransform *pos, PxGeometry *geom, TestObject *parent)
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
		PxBase *base = m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_CAR, objectId, NULL, NULL, NULL, new DrivingStyleFast(material, material), NULL);

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
		Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_TRACK), true, true);
		Audioable *audioable = new Audioable();
		Animatable *animatable = new Animatable();
		Audio *audio = new Audio();

		PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
		PxRigidStatic *physicalPlane = static_cast<PxRigidStatic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_DRIVING_BOX, objectId, pos, geom, material, NULL, NULL));
		Physicable *physicable = new Physicable(physicalPlane);

		TestObject *plane = new TestObject(objectId, *audioable, *physicable, *animatable, *renderable, *audio);

		plane->updateScale(glm::vec3(glm::vec3(plane->getWorldBounds().getDimensions().x, 1, plane->getWorldBounds().getDimensions().z)));

		m_world.addGameObject(plane);
		m_scene.addActor(*physicalPlane);

		return plane;
	}
	case OBJECT_TRACK:
	{
		Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_TRACK), true, true);
		Audioable *audioable = new Audioable();
		Animatable *animatable = new Animatable();
		Audio *audio = new Audio();
		
		PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
		PxRigidStatic *physicalPlane = static_cast<PxRigidStatic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_TRIANGLE_MESH, objectId, pos, NULL, material, NULL, NULL));
		Physicable *physicable = new Physicable(physicalPlane);

		TestObject *plane = new TestObject(objectId, *audioable, *physicable, *animatable, *renderable, *audio);

		plane->updateScale(glm::vec3(glm::vec3(plane->getWorldBounds().getDimensions().x, plane->getWorldBounds().getDimensions().y, plane->getWorldBounds().getDimensions().z)));

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
		PxRigidStatic *physicalWall = static_cast<PxRigidStatic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_WALL, objectId, pos, NULL, NULL, NULL, NULL));
		Physicable *physicable = new Physicable(physicalWall);

		TestObject *wall = new TestObject(objectId, *audioable, *physicable, *animatable, *renderable, *audio);

		m_world.addGameObject(wall);
		m_scene.addActor(*physicalWall);

		return wall;
	}
	case OBJECT_BULLET:
		Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_BULLET), true, true);
		Audioable *audioable = new Audioable();
		Animatable *animatable = new Animatable();
		Audio *audio = new Audio();

		PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
		glm::vec3 speed = 100.f * parent->getForwardVector(); speed += glm::vec3(0, 15.f, 0);
		glm::vec3 pos = parent->getFullPosition();
		PxRigidDynamic *physicalBullet = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_BULLET, objectId, new PxTransform(pos.x, pos.y, pos.z), NULL, NULL, NULL, new PxVec3(speed.x, speed.y, speed.z)));
		animatable->setRotation(parent->getFullRotation());
		animatable->updateScale(glm::vec3(-.5, -.5, -.5));
		Physicable *physicable = new Physicable(physicalBullet);

		Bullet *bullet = new Bullet(objectId, *audioable, *physicable, *animatable, *renderable, *audio, static_cast<Car *>(parent));

		m_world.addGameObject(bullet);
		m_scene.addActor(*physicalBullet);

		return bullet;
	}
}

GameFactory *GameFactory::instance() {
	if (!m_factory)
		exit(50);

	return m_factory;
}

GameFactory *GameFactory::instance(World& world, PxScene& scene, Audio& audioHandle) {
	if (!m_factory)
		m_factory = new GameFactory(world, scene, audioHandle);
	return m_factory;
}