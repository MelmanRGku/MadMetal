#include "GameFactory.h"
#include "Objects\Waypoint.h"

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

TestObject * GameFactory::makeObject(Objects objectToMake, PxTransform *pos, PxGeometry **geom, TestObject *parent)
{
	long objectId = getNextId();

	switch (objectToMake) {
	case OBJECT_MEOW_MIX:
	{
		Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_CAR), true, true);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5f, 0.3f, 0.1f);    //static friction, dynamic friction, restitution
		DrivingStyle * drivingStyle = new DrivingStyleFast(material, material);
		PxBase *base = m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_CAR, objectId, pos, NULL, 0, NULL, drivingStyle, NULL);

		PxVehicleDrive4W *physicalCar = static_cast<PxVehicleDrive4W *>(base);
		Physicable *physicable = new Physicable(physicalCar->getRigidDynamicActor());


		MeowMix *car = new MeowMix(objectId, *drivingStyle, *physicalCar, *audioable, *physicable, *animatable, *renderable);

		int k = (int)physicalCar->mWheelsSimData.getWheelData(0).mRadius * 2;
		PxVec3 physicalCarDimensions = physicalCar->getRigidDynamicActor()->getWorldBounds().getDimensions();
							car->setScale(glm::vec3(physicalCarDimensions.x, physicalCarDimensions.y + k, physicalCarDimensions.z));

		m_world.addGameObject(car);
		m_scene.addActor(*physicalCar->getRigidDynamicActor());

		//Set the vehicle to rest in first gear.
		//Set the vehicle to use auto-gears.
		physicalCar->setToRestState();
		physicalCar->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
		physicalCar->mDriveDynData.setUseAutoGears(true);

							car->healthBar = static_cast<HealthBar2D *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_HEALTH_BAR, NULL, NULL, NULL));
							car->gaugeBar = static_cast<GaugeBar *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_GAUGE_BAR, NULL, NULL, NULL));
							car->score = static_cast<Text2D *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_TEXT_2D, NULL, NULL, NULL));
							car->score->setString("Score: 0");

		return car;
	}
	case OBJECT_BUILDING:
	{
		Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_PLANE), true, true);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();

		PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
		PxGeometry** geo = new PxGeometry * [1];
		geo[0] = new PxBoxGeometry(PxVec3(60, 80, 60));
		PxRigidStatic *physicalBox = static_cast<PxRigidStatic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_BOX, objectId, pos, geo, 0, material, NULL, NULL));
		Physicable *physicable = new Physicable(physicalBox);

		TestObject *box = new TestObject(objectId, *audioable, *physicable, *animatable, *renderable);

		box->updateScale(glm::vec3(glm::vec3(box->getWorldBounds().getDimensions().x, 80, box->getWorldBounds().getDimensions().z)));

		m_world.addGameObject(box);
		m_scene.addActor(*physicalBox);

		return box;
	}
	case OBJECT_TRACK:
	{
		TestObject *drivableTrack = makeObject(GameFactory::OBJECT_TRACK_DRIVABLE, pos, geom, parent);
		TestObject *nonDrivableTrack = makeObject(GameFactory::OBJECT_TRACK_NON_DRIVABLE, pos, geom, parent);

		Track *track;
		
		Renderable *renderable = new Renderable(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		Physicable *physicable = new Physicable(NULL);
		track = new Track(objectId, *audioable, *physicable, *animatable, *renderable, drivableTrack, nonDrivableTrack);

		return track;
	}
	case OBJECT_TRACK_DRIVABLE:
	{
		TestObject *drivableTrack;
		Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_TRACK_DRIVABLE));
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();

		PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
		PxTriangleMesh ** mesh = renderable->getModel()->getPhysicsTriangleMesh();
		PxGeometry ** geom = new PxGeometry *[renderable->getModel()->getMeshes()->size()];
		for (unsigned int i = 0; i < renderable->getModel()->getMeshes()->size(); i++) {
			geom[i] = new PxTriangleMeshGeometry(mesh[i]);
		}
		PxRigidStatic *physicalDrivableTrack = static_cast<PxRigidStatic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_TRACK_DRIVABLE, objectId, pos, geom, renderable->getModel()->getMeshes()->size(), material, NULL, NULL));
		Physicable *physicable = new Physicable(physicalDrivableTrack);
		drivableTrack = new TestObject(objectId, *audioable, *physicable, *animatable, *renderable);

		m_scene.addActor(*physicalDrivableTrack);
		m_world.addGameObject(drivableTrack);

		return drivableTrack;
	}
	case OBJECT_TRACK_NON_DRIVABLE:
	{
		TestObject *nonDrivableTrack;
		Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_TRACK_NON_DRIVABLE));
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		
		PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
		PxTriangleMesh ** mesh = renderable->getModel()->getPhysicsTriangleMesh();
		PxGeometry ** geom = new PxGeometry *[renderable->getModel()->getMeshes()->size()];
		for (unsigned int i = 0; i < renderable->getModel()->getMeshes()->size(); i++) {
			geom[i] = new PxTriangleMeshGeometry(mesh[i]);
		}
		PxRigidStatic *physicalNonDrivableTrack = static_cast<PxRigidStatic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_TRACK_NON_DRIVABLE, objectId, pos, geom, (PxU32)renderable->getModel()->getMeshes()->size(), material, NULL, NULL));
		Physicable *physicable = new Physicable(physicalNonDrivableTrack);
		nonDrivableTrack = new TestObject(objectId, *audioable, *physicable, *animatable, *renderable);

		m_scene.addActor(*physicalNonDrivableTrack);
		m_world.addGameObject(nonDrivableTrack);

		return nonDrivableTrack;
	}
	case OBJECT_WALL:
	{
		Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_PLANE), true, true);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();

		PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
		PxRigidStatic *physicalWall = static_cast<PxRigidStatic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_WALL, objectId, pos, NULL, 0, NULL, NULL, NULL));
		Physicable *physicable = new Physicable(physicalWall);

		TestObject *wall = new TestObject(objectId, *audioable, *physicable, *animatable, *renderable);

		m_world.addGameObject(wall);
		m_scene.addActor(*physicalWall);

		return wall;
	}
	case OBJECT_BULLET_MEOW_MIX:
	{
		
		Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_BULLET_MEOW_MIX), true, true);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();

		PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
						  glm::vec3 speed = 300.f * parent->getForwardVector(); speed += glm::vec3(0, 1.f, 0);
		glm::vec3 pos = parent->getFullPosition();
						  PxRigidDynamic *physicalBullet = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_BULLET_MEOW_MIX, objectId, new PxTransform(pos.x, pos.y, pos.z), NULL, 0, NULL, NULL, new PxVec3(speed.x, speed.y, speed.z)));
		animatable->setRotation(parent->getFullRotation());
						  animatable->setScale(glm::vec3(.2, .2, .7));
		Physicable *physicable = new Physicable(physicalBullet);

		Bullet *bullet = new MeowMixBullet(objectId, *audioable, *physicable, *animatable, *renderable, static_cast<Car *>(parent));
		bullet->setSound(new GunShotSound());
		bullet->playSound();
		m_world.addGameObject(bullet);
		m_scene.addActor(*physicalBullet);

		return bullet;
	}
	case OBJECT_BULLET_SUPER_VOLCANO:
	{
		Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_BULLET_SUPER_VOLCANO), true, true);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
									 Animatable *animatable = new Animatable();


									 PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
									 glm::vec3 speed = 100.f * parent->getForwardVector(); speed += glm::vec3(0, 5.f, 0);
									 glm::vec3 pos = parent->getFullPosition();
									 PxRigidDynamic *physicalBullet = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_BULLET_SUPER_VOLCANO, objectId, new PxTransform(pos.x, pos.y + 2.f, pos.z), NULL, 0, NULL, NULL, new PxVec3(speed.x, speed.y, speed.z)));
									 animatable->setRotation(parent->getFullRotation());
									 animatable->setScale(glm::vec3(physicalBullet->getWorldBounds().getDimensions().x, physicalBullet->getWorldBounds().getDimensions().y, physicalBullet->getWorldBounds().getDimensions().z));
									 Physicable *physicable = new Physicable(physicalBullet);

		Bullet *bullet = new VolcanoGuySuperBullet(objectId, *audioable, *physicable, *animatable, *renderable, static_cast<Car *>(parent));
		bullet->setSound(new ExplosionSound());
		bullet->playSound();

		m_world.addGameObject(bullet);
		m_scene.addActor(*physicalBullet);

		return bullet;
	}
	case OBJECT_HEALTH_BAR:
	{
		Renderable *renderable = new Renderable(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();

		Physicable *physicable = new Physicable(NULL);

		HealthBar2D *bar = new HealthBar2D(objectId, *audioable, *physicable, *animatable, *renderable);

		m_world.addGameObject(bar);

		return bar;
	}
	case OBJECT_GAUGE_BAR:
	{
		Renderable *renderable = new Renderable(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		Physicable *physicable = new Physicable(NULL);

		GaugeBar *bar = new GaugeBar(objectId, *audioable, *physicable, *animatable, *renderable);

		m_world.addGameObject(bar);

		return bar;
	}
	case OBJECT_TEXT_2D:
	{
		Renderable *renderable = new Renderable(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		Physicable *physicable = new Physicable(NULL);

		Text2D *bar = new Text2D(objectId, *audioable, *physicable, *animatable, *renderable);

		m_world.addGameObject(bar);

		return bar;
	}

	case OBJECT_WAYPOINT:
	{
		Renderable *renderable = new Renderable(NULL);

		Animatable *animatable = new Animatable();
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());

		PxRigidDynamic *waypointTriggerVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::WAYPOINT_COLLISION_VOLUME, objectId, pos, geom, 1, NULL, NULL, NULL));
		Physicable *physicable = new Physicable(waypointTriggerVolume);

		Waypoint *waypoint = new Waypoint(objectId, *audioable, *physicable, *animatable, *renderable);

		m_world.addGameObject(waypoint);
		m_scene.addActor(*waypointTriggerVolume);

		return waypoint;
	}
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