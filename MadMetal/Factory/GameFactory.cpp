#include "GameFactory.h"
#include "Objects\Waypoint.h"
#include "Objects\CollisionVolume.h"

long GameFactory::lastId = 0;

GameFactory *GameFactory::m_factory = NULL;

GameFactory::GameFactory(World& world, PxScene& scene, Audio& audioHandle) :m_world(world), m_scene(scene)
{
	m_physicsFactory = new PhysicsFactory();
	m_renderFactory = new RenderFactory();
	m_audioFactory = new AudioFactory(audioHandle);
	m_animationFactory = new AnimationFactory();
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


		MeowMix *car = new MeowMix(objectId, drivingStyle, *physicalCar, audioable, physicable, animatable, renderable);

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


		car->setSoundChassis(ChassisCrashSound());
		return car;
	}
	case OBJECT_UI:
	{
		Renderable *renderable = new Renderable(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		Physicable *physicable = new Physicable(NULL);
		UI *ui = new UI(objectId, audioable, physicable, animatable, renderable);
		ui->healthBar = static_cast<HealthBar2D *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_HEALTH_BAR, NULL, NULL, NULL));
		ui->gaugeBar = static_cast<GaugeBar *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_GAUGE_BAR, NULL, NULL, NULL));
		ui->score = static_cast<Text2D *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_TEXT_2D, NULL, NULL, NULL));
		ui->score->setString("Score: 0");
		ui->lap = static_cast<Text2D *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_TEXT_2D, NULL, NULL, NULL));
		ui->lap->setString("Lap: 0");
		ui->lap->setPos(glm::vec3(10, 70, 0));

		return ui;
	}
	case OBJECT_DISPLAY_MESSAGE:
	{
		Renderable *renderable = new Renderable(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		Physicable *physicable = new Physicable(NULL);
		DisplayMessage * display = new DisplayMessage(objectId, audioable, physicable, animatable, renderable);
		Text2D *text = static_cast<Text2D *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_TEXT_2D, NULL, NULL, NULL));
		text->centerize(true);
		display->setText2D(text);
		
		return display;
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

		TestObject *box = new TestObject(objectId, audioable, physicable, animatable, renderable, NULL);

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
		track = new Track(objectId, audioable, physicable, animatable, renderable, drivableTrack, nonDrivableTrack);
		track->setSound(TrackMusicSound());
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
		delete[] mesh;
		PxRigidStatic *physicalDrivableTrack = static_cast<PxRigidStatic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_TRACK_DRIVABLE, objectId, pos, geom, renderable->getModel()->getMeshes()->size(), material, NULL, NULL));
		for (unsigned int i = 0; i < renderable->getModel()->getMeshes()->size(); i++) {
			delete geom[i];
		}
		delete geom;
		Physicable *physicable = new Physicable(physicalDrivableTrack);
		drivableTrack = new TestObject(objectId, audioable, physicable, animatable, renderable, NULL);

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
		delete[] mesh;
		PxRigidStatic *physicalNonDrivableTrack = static_cast<PxRigidStatic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_TRACK_NON_DRIVABLE, objectId, pos, geom, renderable->getModel()->getMeshes()->size(), material, NULL, NULL));
		for (unsigned int i = 0; i < renderable->getModel()->getMeshes()->size(); i++) {
			delete geom[i];
		}
		delete geom;

		Physicable *physicable = new Physicable(physicalNonDrivableTrack);
		nonDrivableTrack = new TestObject(objectId, audioable, physicable, animatable, renderable, NULL);

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

		TestObject *wall = new TestObject(objectId, audioable, physicable, animatable, renderable, NULL);

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
						  glm::vec3 speed = 300.f * parent->getForwardVector(); speed += glm::vec3(0, -.4f, 0);
						  PxVec3 *physicsSpeed = new PxVec3(speed.x, speed.y, speed.z);
						  PxRigidDynamic *physicalBullet = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_BULLET_MEOW_MIX, objectId, pos, NULL, 0, NULL, NULL, physicsSpeed));
						  delete physicsSpeed;
		animatable->setRotation(parent->getFullRotation());
		animatable->setScale(glm::vec3(physicalBullet->getWorldBounds().getDimensions().x, physicalBullet->getWorldBounds().getDimensions().y, physicalBullet->getWorldBounds().getDimensions().z));
		Physicable *physicable = new Physicable(physicalBullet);

		Bullet *bullet = new MeowMixBullet(objectId, audioable, physicable, animatable, renderable, static_cast<Car *>(parent));
		bullet->setSound(GunShotSound());
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
		glm::vec3 speed = 150.f * parent->getForwardVector(); speed += glm::vec3(0, 5.f, 0);
		PxVec3 *physicsSpeed = new PxVec3(speed.x, speed.y, speed.z);
		PxRigidDynamic *physicalBullet = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_BULLET_SUPER_VOLCANO, objectId, pos, NULL, 0, NULL, NULL, physicsSpeed));
		delete physicsSpeed;
		animatable->setRotation(parent->getFullRotation());
		animatable->setScale(glm::vec3(physicalBullet->getWorldBounds().getDimensions().x, physicalBullet->getWorldBounds().getDimensions().y, physicalBullet->getWorldBounds().getDimensions().z));
		Physicable *physicable = new Physicable(physicalBullet);

		Bullet *bullet = new VolcanoGuySuperBullet(objectId, audioable, physicable, animatable, renderable, static_cast<Car *>(parent));
		bullet->setSound(ExplosionSound());
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

		HealthBar2D *bar = new HealthBar2D(objectId, audioable, physicable, animatable, renderable);

		m_world.addGameObject(bar);

		return bar;
	}
	case OBJECT_GAUGE_BAR:
	{
		Renderable *renderable = new Renderable(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		Physicable *physicable = new Physicable(NULL);

		GaugeBar *bar = new GaugeBar(objectId, audioable, physicable, animatable, renderable);

		m_world.addGameObject(bar);

		return bar;
	}
	case OBJECT_TEXT_2D:
	{
		Renderable *renderable = new Renderable(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		Physicable *physicable = new Physicable(NULL);

		Text2D *bar = new Text2D(objectId, audioable, physicable, animatable, renderable);

		m_world.addGameObject(bar);

		return bar;
	}
	case OBJECT_TEXT_3D:
	{
		Renderable *renderable = new Renderable(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		Physicable *physicable = new Physicable(NULL);

		Text3D *text = new Text3D(objectId, audioable, physicable, animatable, renderable, 1);

		m_world.addGameObject(text);

		return text;
	}
	case OBJECT_WAYPOINT:
	{
		Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_GGO), true, true);
		renderable->setAlpha(0.4);

		Animatable *animatable = new Animatable();
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());

		PxRigidDynamic *waypointTriggerVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::WAYPOINT_COLLISION_VOLUME, objectId, pos, geom, 1, NULL, NULL, NULL));
		Physicable *physicable = new Physicable(waypointTriggerVolume);
		animatable->setScale(glm::vec3(waypointTriggerVolume->getWorldBounds().getDimensions().x, waypointTriggerVolume->getWorldBounds().getDimensions().y, waypointTriggerVolume->getWorldBounds().getDimensions().z));

		Waypoint *waypoint = new Waypoint(objectId, audioable, physicable, animatable, renderable);

		m_world.addGameObject(waypoint);
		m_scene.addActor(*waypointTriggerVolume);

		return waypoint;
	}

	case OBJECT_POWERUP:
	{
			Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_ATTACK_POWERUP), true, true);
			Animatable *animatable = new Animatable();
			Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());

			PxRigidDynamic *powerupTriggerVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::POWER_UP, objectId, pos, geom, 0, NULL, NULL, NULL));
			Physicable *physicable = new Physicable(powerupTriggerVolume);
			animatable->setScale(glm::vec3(powerupTriggerVolume->getWorldBounds().getDimensions().x, powerupTriggerVolume->getWorldBounds().getDimensions().y, powerupTriggerVolume->getWorldBounds().getDimensions().z));

			PowerUp *powerup = new PowerUp(objectId, audioable, physicable, animatable, renderable);

			m_world.addGameObject(powerup);
			m_scene.addActor(*powerupTriggerVolume);

			return powerup;
	}
	case OBJECT_BULLET_CAR_COLLISION:
	{
		Renderable *renderable = new Renderable(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		Physicable *physicable = new Physicable(NULL);


		BulletCarCollision * col = new BulletCarCollision(objectId, audioable, physicable, animatable, renderable);
		col->setSound(BulletCarCollisionSound());
		col->playSound();

		return col;
	}
	case OBJECT_COLLISION_VOLUME:
	{
		Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_GGO), true, true);

		Animatable *animatable = new Animatable();
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());

		PxRigidDynamic *physicalCollisionVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::COLLISION_VOLUME, objectId, pos, geom, 1, NULL, NULL, NULL));
		Physicable *physicable = new Physicable(physicalCollisionVolume);
		animatable->setScale(glm::vec3(physicalCollisionVolume->getWorldBounds().getDimensions().x, physicalCollisionVolume->getWorldBounds().getDimensions().y, physicalCollisionVolume->getWorldBounds().getDimensions().z));

		CollisionVolume *collisionVolume = new CollisionVolume(objectId, audioable, physicable, animatable, renderable);

		m_world.addGameObject(collisionVolume);
		m_scene.addActor(*physicalCollisionVolume);

		return collisionVolume;
	}
	case OBJECT_ANIMATION_TEST:
	{
		Renderable *renderable = new Renderable(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_ANIMATION_TEST), true, true);
		Animatable *animatable = new Animatable();
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animation *aniable = new Animation(m_animationFactory->makeAnimation(AnimationFactory::ANIMATION_DEATHSTAR));

		PxRigidDynamic *animationTestTriggerVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::ANIMATION_TEST, objectId, pos, geom, 0, NULL, NULL, NULL));
		Physicable *physicable = new Physicable(animationTestTriggerVolume);
		animatable->setScale(glm::vec3(animationTestTriggerVolume->getWorldBounds().getDimensions().x, animationTestTriggerVolume->getWorldBounds().getDimensions().y, animationTestTriggerVolume->getWorldBounds().getDimensions().z));

		TestObject *animation = new TestObject(objectId, audioable, physicable, animatable, renderable, aniable);

		m_world.addGameObject(animation);
		m_scene.addActor(*animationTestTriggerVolume);

		return animation;
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