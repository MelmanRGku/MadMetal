#include "GameFactory.h"
#include "Objects\Waypoint.h"
#include "Objects\CollisionVolume.h"
#include "Objects\Particle.h"

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
		Model3D *model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_CAR));
		Renderable3D *renderable = new Renderable3D(model, true, true);
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
		Renderable2D *renderable = new Renderable2D(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		UI *ui = new UI(objectId, audioable, animatable, renderable);
		ui->healthBar = static_cast<HealthBar2D *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_HEALTH_BAR, NULL, NULL, NULL));
		ui->gaugeBar = static_cast<GaugeBar *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_GAUGE_BAR, NULL, NULL, NULL));
		ui->score = static_cast<Text2D *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_TEXT_2D, NULL, NULL, NULL));
		ui->score->setString("Score: 0");
		ui->lap = static_cast<Text2D *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_TEXT_2D, NULL, NULL, NULL));
		ui->lap->setString("Lap: 0");
		ui->lap->setPosition(glm::vec3(10, 70, 0));
		ui->map = static_cast<MapUI *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_UI_MAP, NULL, NULL, NULL));

		return ui;
	}
	case OBJECT_DISPLAY_MESSAGE:
	{
		Renderable2D *renderable = new Renderable2D(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		DisplayMessage * display = new DisplayMessage(objectId, audioable, animatable, renderable);
		Text2D *text = static_cast<Text2D *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_TEXT_2D, NULL, NULL, NULL));
		text->centerize(true);
		display->setText2D(text);
		
		return display;
	}
	case OBJECT_TRACK:
	{
		Object3D *drivableTrack = static_cast<Object3D *>(makeObject(GameFactory::OBJECT_TRACK_DRIVABLE, pos, geom, parent));
		Object3D *nonDrivableTrack = static_cast<Object3D *>(makeObject(GameFactory::OBJECT_TRACK_NON_DRIVABLE, pos, geom, parent));

		Track *track;
		
		Renderable3D *renderable = new Renderable3D(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		Physicable *physicable = new Physicable(NULL);
		track = new Track(objectId, audioable, physicable, animatable, renderable, drivableTrack, nonDrivableTrack);
		return track;
	}
	case OBJECT_TRACK_DRIVABLE:
	{
		Object3D *drivableTrack;
		Model3D *model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_TRACK_DRIVABLE));
		Renderable3D *renderable = new Renderable3D(model);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();

		PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
		PxTriangleMesh ** mesh = model->getPhysicsTriangleMesh();
		PxGeometry ** geom = new PxGeometry *[model->getMeshes()->size()];
		for (unsigned int i = 0; i < model->getMeshes()->size(); i++) {
			geom[i] = new PxTriangleMeshGeometry(mesh[i]);
		}
		delete[] mesh;
		PxRigidStatic *physicalDrivableTrack = static_cast<PxRigidStatic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_TRACK_DRIVABLE, objectId, pos, geom, model->getMeshes()->size(), material, NULL, NULL));
		for (unsigned int i = 0; i < model->getMeshes()->size(); i++) {
			delete geom[i];
		}
		delete geom;
		Physicable *physicable = new Physicable(physicalDrivableTrack);
		drivableTrack = new Object3D(objectId, audioable, physicable, animatable, renderable, NULL);

		m_scene.addActor(*physicalDrivableTrack);
		m_world.addGameObject(drivableTrack);

		return drivableTrack;
	}
	case OBJECT_TRACK_NON_DRIVABLE:
	{
		Object3D *nonDrivableTrack;
		Model3D *model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_TRACK_NON_DRIVABLE));
		Renderable3D *renderable = new Renderable3D(model);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();

		PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
		PxTriangleMesh ** mesh = model->getPhysicsTriangleMesh();
		PxGeometry ** geom = new PxGeometry *[model->getMeshes()->size()];
		for (unsigned int i = 0; i < model->getMeshes()->size(); i++) {
			geom[i] = new PxTriangleMeshGeometry(mesh[i]);
		}
		delete[] mesh;
		PxRigidStatic *physicalNonDrivableTrack = static_cast<PxRigidStatic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_TRACK_NON_DRIVABLE, objectId, pos, geom, model->getMeshes()->size(), material, NULL, NULL));
		for (unsigned int i = 0; i < model->getMeshes()->size(); i++) {
			delete geom[i];
		}
		delete geom;

		Physicable *physicable = new Physicable(physicalNonDrivableTrack);
		nonDrivableTrack = new Object3D(objectId, audioable, physicable, animatable, renderable, NULL);

		m_scene.addActor(*physicalNonDrivableTrack);
		m_world.addGameObject(nonDrivableTrack);

		return nonDrivableTrack;
	}
	case OBJECT_BULLET_MEOW_MIX:
	{
		Model3D *model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_BULLET_MEOW_MIX));
		Renderable3D *renderable = new Renderable3D(model, true, true);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();

		PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
		glm::vec3 speed = 300.f * static_cast<Object3D *>(parent)->getForwardVector(); speed += glm::vec3(0, -.4f, 0);
		PxVec3 *physicsSpeed = new PxVec3(speed.x, speed.y, speed.z);
		PxRigidDynamic *physicalBullet = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_BULLET_MEOW_MIX, objectId, pos, NULL, 0, NULL, NULL, physicsSpeed));
		delete physicsSpeed;
		animatable->setRotation(static_cast<Object3D *>(parent)->getFullRotation());
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
		Model3D *model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_BULLET_SUPER_VOLCANO));
		Renderable3D *renderable = new Renderable3D(model, true, true);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();


		PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
		glm::vec3 speed = 150.f * static_cast<Object3D *>(parent)->getForwardVector(); speed += glm::vec3(0, 5.f, 0);
		PxVec3 *physicsSpeed = new PxVec3(speed.x, speed.y, speed.z);
		PxRigidDynamic *physicalBullet = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_BULLET_SUPER_VOLCANO, objectId, pos, NULL, 0, NULL, NULL, physicsSpeed));
		delete physicsSpeed;
		animatable->setRotation(static_cast<Object3D *>(parent)->getFullRotation());
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
		Renderable2D *renderable = new Renderable2D(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();

		HealthBar2D *bar = new HealthBar2D(objectId, audioable, animatable, renderable);

		m_world.addGameObject(bar);

		return bar;
	}
	case OBJECT_GAUGE_BAR:
	{
		Renderable2D *renderable = new Renderable2D(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();

		GaugeBar *bar = new GaugeBar(objectId, audioable, animatable, renderable);

		m_world.addGameObject(bar);

		return bar;
	}
	case OBJECT_TEXT_2D:
	{
		Renderable2D *renderable = new Renderable2D(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();

		Text2D *bar = new Text2D(objectId, audioable, animatable, renderable);

		m_world.addGameObject(bar);

		return bar;
	}
	case OBJECT_TEXT_3D:
	{
		Renderable3D *renderable = new Renderable3D(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		Physicable *physicable = new Physicable(NULL);

		Text3D *text = new Text3D(objectId, audioable, physicable, animatable, renderable, 1);

		m_world.addGameObject(text);

		return text;
	}
	case OBJECT_WAYPOINT:
	{
		Model3D *model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_GGO));
		Renderable3D *renderable = new Renderable3D(model, true, true);
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

	

	case OBJECT_SHIELD_POWERUP:
	{
						   Model3D *model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_SHIELD_POWERUP));
			Renderable3D *renderable = new Renderable3D(model, true, true);
						 
			Animatable *animatable = new Animatable();
			Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());

						   PxRigidDynamic *powerupTriggerVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::SHIELD_POWERUP, objectId, pos, geom, 0, NULL, NULL, NULL));
			Physicable *physicable = new Physicable(powerupTriggerVolume);
						   PxVec3 dim = powerupTriggerVolume->getWorldBounds().getDimensions();
						   animatable->setScale(glm::vec3(dim.x > dim.z ? dim.z : dim.x, 3, dim.x > dim.z ? dim.z : dim.x));

						   PowerUpShield *shield = new PowerUpShield(objectId, audioable, physicable, animatable, renderable, static_cast<Car*>(parent));

						   m_world.addGameObject(shield);
			m_scene.addActor(*powerupTriggerVolume);

						   return shield;
	}

	case OBJECT_SPEED_POWERUP:
	{
						   Model3D *model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_ATTACK_POWERUP));
						   Renderable3D *renderable = new Renderable3D(model, true, true);
						   renderable->setModel(NULL);  // remove when there is a model for the powerup
						   Animatable *animatable = new Animatable();
						   Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());

						   PxRigidDynamic *powerupTriggerVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::SPEED_POWERUP, objectId, pos, geom, 0, NULL, NULL, NULL));
						   Physicable *physicable = new Physicable(powerupTriggerVolume);
						   animatable->setScale(glm::vec3(powerupTriggerVolume->getWorldBounds().getDimensions().x, powerupTriggerVolume->getWorldBounds().getDimensions().y, powerupTriggerVolume->getWorldBounds().getDimensions().z));

						   PowerUpSpeed *powerup = new PowerUpSpeed(objectId, audioable, physicable, animatable, renderable, static_cast<Car*>(parent));

						   m_world.addGameObject(powerup);
						   m_scene.addActor(*powerupTriggerVolume);

						   return powerup;
	}

	case OBJECT_POWERUP:
	{
						   Model3D *model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_ATTACK_POWERUP));
						   Renderable3D *renderable = new Renderable3D(model, true, true);
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
	case OBJECT_PARTICLE:
	{
							Model3D *model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_ATTACK_POWERUP));
							Renderable3D *renderable = new Renderable3D(model, true, true);
							Animatable *animatable = new Animatable();
							Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());

							PxRigidDynamic *particleVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_PARTICLE, objectId, pos, geom, 0, NULL, NULL, NULL));
							Physicable *physicable = new Physicable(particleVolume);
							
							animatable->setScale(glm::vec3(particleVolume->getWorldBounds().getDimensions().x, particleVolume->getWorldBounds().getDimensions().y, particleVolume->getWorldBounds().getDimensions().z));

							Particle *particle = new Particle(objectId, audioable, physicable, animatable, renderable);

							m_world.addGameObject(particle);
							m_scene.addActor(*particleVolume);

							return particle;
	}
	case OBJECT_EXPLOSION_1:
	{
							   Model3D *model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_EXPLOSION1_1));
							   Renderable3D *renderable = new Renderable3D(model, true, true);
							   Animatable *animatable = new Animatable();
							   Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());

							   PxRigidDynamic *explosionVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_EXPLOSION, objectId, pos, geom, 0, NULL, NULL, NULL));
							   Physicable *physicable = new Physicable(explosionVolume);

							   animatable->setScale(glm::vec3(explosionVolume->getWorldBounds().getDimensions().x, explosionVolume->getWorldBounds().getDimensions().y, explosionVolume->getWorldBounds().getDimensions().z));

							   AnimatedExplosion *explosion = new AnimatedExplosion(objectId, audioable, physicable, animatable, renderable, .5);

							   m_world.addGameObject(explosion);
							   m_scene.addActor(*explosionVolume);

							   return explosion;
	}
	case OBJECT_COLLISION_VOLUME:
	{
		Model3D *model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_GGO));
		Renderable3D *renderable = new Renderable3D(model, true, true);

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
	case OBJECT_UI_DISTURBED_SONG_TEXTURE_THE_VENGEFUL_ONE:
	{
		Renderable2D *renderable = new Renderable2D(static_cast<Model2D*>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_UI_DISTURBED_SONG_TEXTURE_THE_VENGEFUL_ONE)));
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		animatable->setPosition(glm::vec3(0, .89f, 0));
		animatable->setScale(glm::vec3(.05f, 0, 0));

		TexturedObject2D *image = new TexturedObject2D(objectId, audioable, animatable, renderable);
		image->setMaxLifeTime(2);

		ObjectScaleUpdater *upd1 = new ObjectScaleUpdater(image, glm::vec3(.0f, .2f, .0f), .5);
		ObjectScaleUpdater *upd2 = new ObjectScaleUpdater(image, glm::vec3(.0f, .0f, .0f), .2);
		ObjectScaleUpdater *upd3 = new ObjectScaleUpdater(image, glm::vec3(.45f, .0f, .0f), .3);
		ObjectUpdaterSequence *seq = new ObjectUpdaterSequence(ObjectUpdaterSequence::TYPE_ONCE);
		seq->addObjectUpdater(upd1);
		seq->addObjectUpdater(upd2);
		seq->addObjectUpdater(upd3);
		m_world.addObjectUpdater(seq);

		m_world.addGameObject(image);

		return image;
	}
	case OBJECT_UI_SICK_PUPPIES_SONG_TEXTURE_YOURE_GOING_DOWN:
	{
		Renderable2D *renderable = new Renderable2D(static_cast<Model2D*>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_UI_SICK_PUPPIES_SONG_TEXTURE_YOURE_GOING_DOWN)));
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		animatable->setPosition(glm::vec3(0, .89f, 0));
		animatable->setScale(glm::vec3(.05f, 0, 0));

		TexturedObject2D *image = new TexturedObject2D(objectId, audioable, animatable, renderable);
		image->setMaxLifeTime(2);

		ObjectScaleUpdater *upd1 = new ObjectScaleUpdater(image, glm::vec3(.0f, .2f, .0f), .5);
		ObjectScaleUpdater *upd2 = new ObjectScaleUpdater(image, glm::vec3(.0f, .0f, .0f), .2);
		ObjectScaleUpdater *upd3 = new ObjectScaleUpdater(image, glm::vec3(.45f, .0f, .0f), .3);
		ObjectUpdaterSequence *seq = new ObjectUpdaterSequence(ObjectUpdaterSequence::TYPE_ONCE);
		seq->addObjectUpdater(upd1);
		seq->addObjectUpdater(upd2);
		seq->addObjectUpdater(upd3);
		m_world.addObjectUpdater(seq);

		m_world.addGameObject(image);

		return image;
	}
	case OBJECT_UI_ALL_GOOD_THINGS_SONG_I_AM_THE_ENEMY:
	{
		Renderable2D *renderable = new Renderable2D(static_cast<Model2D*>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_UI_ALL_GOOD_THINGS_SONG_I_AM_THE_ENEMY)));
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		animatable->setPosition(glm::vec3(0, .89f, 0));
		animatable->setScale(glm::vec3(.05f, 0, 0));

		TexturedObject2D *image = new TexturedObject2D(objectId, audioable, animatable, renderable);
		image->setMaxLifeTime(2);

		ObjectScaleUpdater *upd1 = new ObjectScaleUpdater(image, glm::vec3(.0f, .2f, .0f), .5);
		ObjectScaleUpdater *upd2 = new ObjectScaleUpdater(image, glm::vec3(.0f, .0f, .0f), .2);
		ObjectScaleUpdater *upd3 = new ObjectScaleUpdater(image, glm::vec3(.45f, .0f, .0f), .3);
		ObjectUpdaterSequence *seq = new ObjectUpdaterSequence(ObjectUpdaterSequence::TYPE_ONCE);
		seq->addObjectUpdater(upd1);
		seq->addObjectUpdater(upd2);
		seq->addObjectUpdater(upd3);
		m_world.addObjectUpdater(seq);

		m_world.addGameObject(image);

		return image;
	}
	case OBJECT_UI_METAL_MUSIC_SONG_DARKNESS_FALLS:
	{
		Renderable2D *renderable = new Renderable2D(static_cast<Model2D*>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_UI_METAL_MUSIC_SONG_DARKNESS_FALLS)));
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		animatable->setPosition(glm::vec3(0, .89f, 0));
		animatable->setScale(glm::vec3(.05f, 0, 0));

		TexturedObject2D *image = new TexturedObject2D(objectId, audioable, animatable, renderable);
		image->setMaxLifeTime(2);

		ObjectScaleUpdater *upd1 = new ObjectScaleUpdater(image, glm::vec3(.0f, .2f, .0f), .5);
		ObjectScaleUpdater *upd2 = new ObjectScaleUpdater(image, glm::vec3(.0f, .0f, .0f), .2);
		ObjectScaleUpdater *upd3 = new ObjectScaleUpdater(image, glm::vec3(.45f, .0f, .0f), .3);
		ObjectUpdaterSequence *seq = new ObjectUpdaterSequence(ObjectUpdaterSequence::TYPE_ONCE);
		seq->addObjectUpdater(upd1);
		seq->addObjectUpdater(upd2);
		seq->addObjectUpdater(upd3);
		m_world.addObjectUpdater(seq);

		m_world.addGameObject(image);

		return image;
	}
	case OBJECT_UI_MAP:
	{
		Renderable2D *renderable = new Renderable2D(static_cast<Model2D*>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_MAP_TEXTURE)));
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		animatable->setPosition(glm::vec3(.8f, .8f, 0));
		animatable->setScale(glm::vec3(.38f, .38f, 0));

		MapUI *map = new MapUI(objectId, audioable, animatable, renderable);
		map->setPlayerModel(static_cast<Model2D*>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_PLAYER_ON_UI_MAP_TEXTURE)));

		m_world.addGameObject(map);

		return map;
	}
	case OBJECT_ANIMATION_TEST:
	{
								  Renderable3D *renderable = new Renderable3D(static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_ANIMATION_TEST)), true, true);
								  Animatable *animatable = new Animatable();
								  Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
								  Animation *aniable = new Animation(m_animationFactory->makeAnimation(AnimationFactory::ANIMATION_DEATHSTAR));

								  PxRigidDynamic *animationTestTriggerVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::ANIMATION_TEST, objectId, pos, geom, 0, NULL, NULL, NULL));
								  Physicable *physicable = new Physicable(animationTestTriggerVolume);
								  animatable->setScale(glm::vec3(animationTestTriggerVolume->getWorldBounds().getDimensions().x, animationTestTriggerVolume->getWorldBounds().getDimensions().y, animationTestTriggerVolume->getWorldBounds().getDimensions().z));

								  Object3D *animation = new Object3D(objectId, audioable, physicable, animatable, renderable, aniable);

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