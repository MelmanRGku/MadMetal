#include "GameFactory.h"
#include "Objects\Waypoint.h"
#include "Objects\CollisionVolume.h"
#include "Objects\Particle.h"
#include "Objects\PowerUpAttack.h"
#include "Objects\UIScoreTable.h"
#include "Objects\MeowMixSuper.h"
#include "Objects\GargantulousSuper.h"
#include "Objects\HomingBullet.h"
#include "Objects\GargantulousBullet.h"

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
	delete m_animationFactory;
	m_factory = NULL;
}

bool GameFactory::sceneRayCast(PxVec3 origin, PxVec3 direction, PxReal maxDistance, PxRaycastBuffer &hit, PxHitFlags flags, PxQueryFilterData fd)
{
	return m_scene.raycast(origin, direction, maxDistance, hit, flags, fd);
}

bool GameFactory::sceneSweep(PxGeometry sweepShape, PxTransform origin, PxVec3 sweepDirection, float maxDistance, PxSweepBuffer& hit)
{
	return m_scene.sweep(sweepShape, origin, sweepDirection, maxDistance, hit);
}


TestObject * GameFactory::makeObject(Objects objectToMake, PxTransform *pos, PxGeometry **geom, TestObject *parent)
{
	long objectId = getNextId();

	switch (objectToMake) {
	case OBJECT_MEOW_MIX:
	{
//		Model3D *model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_MEOWMIXWHEEL));
//		Renderable3D *renderable = new Renderable3D(model, true, true);
//		Model3D *model2 = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_MEOWMIXBODY));
//		Renderable3D *renderable2 = new Renderable3D(model2, true, true);

	Model3D *model = NULL;
	model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_MEOWMIXBODY));
Renderable3D *renderable = new Renderable3D(model, true, true);
Model3D *model2 = NULL;
model2 = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_MEOWMIXWHEEL));
Renderable3D *renderable2 = new Renderable3D(model2, true, true);


		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5f, 0.3f, 0.1f);    //static friction, dynamic friction, restitution
		DrivingStyle * drivingStyle = new DrivingStyleMeowMix(material, material);
		PxBase *base = m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_CAR, objectId, pos, NULL, 0, NULL, drivingStyle, NULL);

		PxVehicleDrive4W *physicalCar = static_cast<PxVehicleDrive4W *>(base);
		Physicable *physicable = new Physicable(physicalCar->getRigidDynamicActor());


		MeowMix *car = new MeowMix(objectId, drivingStyle, *physicalCar, audioable, physicable, animatable, renderable, renderable2);

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
#define EXPLOSIVELY_DELICIOUS_HEIGHT_ADDITION 3
	case OBJECT_EXPLOSIVELY_DELICIOUS:
	{
										 Model3D *model = NULL;
										 model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_EXPLOSIVELY_DELICIOUS));
										 Renderable3D *renderable = new Renderable3D(model, true, true);
										 Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
										 Animatable *animatable = new Animatable();
										 PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5f, 0.3f, 0.1f);    //static friction, dynamic friction, restitution
										 DrivingStyle * drivingStyle = new DrivingStyleExplosivelyDelicious(material, material);
										 PxBase *base = m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_CAR, objectId, pos, NULL, 0, NULL, drivingStyle, NULL);

										 PxVehicleDrive4W *physicalCar = static_cast<PxVehicleDrive4W *>(base);
										 Physicable *physicable = new Physicable(physicalCar->getRigidDynamicActor());


										 ExplosivelyDelicious *car = new ExplosivelyDelicious(objectId, drivingStyle, *physicalCar, audioable, physicable, animatable, renderable);

										 int k = (int)physicalCar->mWheelsSimData.getWheelData(0).mRadius * 2 + EXPLOSIVELY_DELICIOUS_HEIGHT_ADDITION;

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
	case OBJECT_GARGANTULOUS:
	{
								Model3D *model = NULL;
								model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_GARGANTULOUS));
							Renderable3D *renderable = new Renderable3D(model, true, true);
							Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
							Animatable *animatable = new Animatable();
							PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5f, 0.3f, 0.1f);    //static friction, dynamic friction, restitution
							DrivingStyle * drivingStyle = new DrivingStyleGargantulous(material, material);
							PxBase *base = m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_CAR, objectId, pos, NULL, 0, NULL, drivingStyle, NULL);

							PxVehicleDrive4W *physicalCar = static_cast<PxVehicleDrive4W *>(base);
							Physicable *physicable = new Physicable(physicalCar->getRigidDynamicActor());


							Gargantulous *car = new Gargantulous(objectId, drivingStyle, *physicalCar, audioable, physicable, animatable, renderable);

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
		ui->lap = static_cast<Text2D *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_TEXT_2D, NULL, NULL, NULL));
		ui->lap->setString("Lap: 0");
		ui->lap->centerize(true);
		ui->lap->setPosition(glm::vec3(glutGet(GLUT_WINDOW_WIDTH) - 150, glutGet(GLUT_WINDOW_HEIGHT) - 36, 0));
		ui->map = static_cast<MapUI *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_UI_MAP, NULL, NULL, NULL));
		ui->powerupBorder = static_cast<TexturedObject2D *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_UI_POWERUP_BORDER_ICON, NULL, NULL, NULL));
		ui->scoreTable = static_cast<UIScoreTable *>(GameFactory::instance()->makeObject(GameFactory::OBJECT_UI_SCORE_TABLE, NULL, NULL, NULL));
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
		m_world.addGameObject(text);
		display->setText2D(text);
		
		return display;
	}
	case OBJECT_TRACK:
	{
		Object3D *drivableTrack = static_cast<Object3D *>(makeObject(GameFactory::OBJECT_TRACK_DRIVABLE, pos, geom, parent));
		Object3D *nonDrivableTrack = static_cast<Object3D *>(makeObject(GameFactory::OBJECT_TRACK_NON_DRIVABLE, pos, geom, parent));
		Object3D *trackWalls = static_cast<Object3D *>(makeObject(GameFactory::OBJECT_TRACK_WALLS, pos, geom, parent));

		Track *track;
		
		Renderable3D *renderable = new Renderable3D(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		Physicable *physicable = new Physicable(NULL);
		track = new Track(objectId, audioable, physicable, animatable, renderable, drivableTrack, nonDrivableTrack, trackWalls);
		return track;
	}
	case OBJECT_TRACK_DRIVABLE:
	{
		Object3D *drivableTrack;
		Model3D *model = NULL;
		model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_TRACK_DRIVABLE));
		Renderable3D *renderable = new Renderable3D(model);
		//Renderable3D *renderable = new Renderable3D(NULL);
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
		Model3D *model = NULL;
		model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_TRACK_NON_DRIVABLE));
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
	case OBJECT_TRACK_WALLS:
	{
									  Object3D *trackWalls;
									  Model3D *model = NULL;
									  model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_TRACK_WALLS));
									  Renderable3D *renderable = new Renderable3D(NULL);
									  Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
									  Animatable *animatable = new Animatable();

									  PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0, 0, 0);    //static friction, dynamic friction, restitution
									  PxTriangleMesh ** mesh = model->getPhysicsTriangleMesh();
									  PxGeometry ** geom = new PxGeometry *[model->getMeshes()->size()];
									  for (unsigned int i = 0; i < model->getMeshes()->size(); i++) {
										  geom[i] = new PxTriangleMeshGeometry(mesh[i]);
									  }
									  delete[] mesh;
									  PxRigidStatic *physicalTrackWalls = static_cast<PxRigidStatic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_TRACK_WALLS, objectId, pos, geom, model->getMeshes()->size(), material, NULL, NULL));
									  for (unsigned int i = 0; i < model->getMeshes()->size(); i++) {
										  delete geom[i];
									  }
									  delete geom;

									  Physicable *physicable = new Physicable(physicalTrackWalls);
									  trackWalls = new Object3D(objectId, audioable, physicable, animatable, renderable, NULL);

									  m_scene.addActor(*physicalTrackWalls);
									  m_world.addGameObject(trackWalls);

									  return trackWalls;
	}
	case OBJECT_BULLET_MEOW_MIX:
	{
								   Model3D *model = NULL;
								   model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_BULLET_MEOW_MIX));
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
	case OBJECT_GARGANTULOUS_BULLET:
	{
									   Model3D *model = NULL;
									   model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_GARGANTULOUS_BULLET));
								   Renderable3D *renderable = new Renderable3D(model, true, true);
								   Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
								   Animatable *animatable = new Animatable();

								   PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
		glm::vec3 speed = 250.0f * static_cast<Object3D *>(parent)->getForwardVector();
								   PxVec3 *physicsSpeed = new PxVec3(speed.x, speed.y, speed.z);
								   PxRigidDynamic *physicalBullet = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_GARGANTULOUS_BULLET, objectId, pos, NULL, 0, NULL, NULL, physicsSpeed));
								   delete physicsSpeed;
								   animatable->setRotation(static_cast<Object3D *>(parent)->getFullRotation());
								   animatable->setScale(glm::vec3(physicalBullet->getWorldBounds().getDimensions().x, physicalBullet->getWorldBounds().getDimensions().y, physicalBullet->getWorldBounds().getDimensions().z));
								   Physicable *physicable = new Physicable(physicalBullet);

								   Bullet *bullet = new GargantulousBullet(objectId, audioable, physicable, animatable, renderable, static_cast<Car *>(parent));
								   bullet->setSound(GunShotSound());
								   bullet->playSound();
								   m_world.addGameObject(bullet);
								   m_scene.addActor(*physicalBullet);

								   return bullet;
	}
	case OBJECT_BULLET_EXPLOSIVELY_DELICIOUS:
	{
												Model3D *model = NULL;
												model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_BULLET_EXPLOSIVELY_DELICIOUS));
		Renderable3D *renderable = new Renderable3D(model, true, true);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();


		PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
		glm::vec3 speed = 160.f * static_cast<Object3D *>(parent)->getForwardVector(); speed += glm::vec3(0, 7.f, 0);
		PxVec3 *physicsSpeed = new PxVec3(speed.x, speed.y, speed.z);
		PxRigidDynamic *physicalBullet = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_BULLET_SUPER_VOLCANO, objectId, pos, NULL, 0, NULL, NULL, physicsSpeed));
		
		delete physicsSpeed;
		animatable->setRotation(static_cast<Object3D *>(parent)->getFullRotation());
		animatable->setScale(glm::vec3(physicalBullet->getWorldBounds().getDimensions().x, physicalBullet->getWorldBounds().getDimensions().y, physicalBullet->getWorldBounds().getDimensions().z));
		Physicable *physicable = new Physicable(physicalBullet);

		Bullet *bullet = new ExplosivelyDeliciousBullet(objectId, audioable, physicable, animatable, renderable, static_cast<Car *>(parent));
		bullet->setSound(ExplosionSound());
		bullet->playSound();

		m_world.addGameObject(bullet);
		m_scene.addActor(*physicalBullet);

		return bullet;
	}
	case OBJECT_BULLET_SUPER_VOLCANO:
	{
										Model3D *model = NULL;
										model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_BULLET_SUPER_VOLCANO));
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

	case OBJECT_EXPLOSIVELY_DELICIOUS_SUPER:
	{
											   Model3D *model = NULL;
											   model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_EXPLOSIVELY_DELICIOUS_SUPER));
											   Renderable3D *renderable = new Renderable3D(model, true, true);
											   Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
											   Animatable *animatable = new Animatable();


											   PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution
											   
											   PxRigidDynamic *explosion = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_EXPLOSIVELY_DELICIOUS_SUPER, objectId, pos, geom, 0, NULL, NULL, NULL));
											   
											   animatable->setRotation(static_cast<Object3D *>(parent)->getFullRotation());
											   animatable->setScale(glm::vec3(explosion->getWorldBounds().getDimensions().x / 5, explosion->getWorldBounds().getDimensions().y / 5, explosion->getWorldBounds().getDimensions().z / 5));
											   Physicable *physicable = new Physicable(explosion);

											   ExplosivelyDeliciousSuper *superExplosion = new ExplosivelyDeliciousSuper(objectId, audioable, physicable, animatable, renderable, static_cast<Car *>(parent));
											   superExplosion->setSound(ExplosionSound());
											   superExplosion->playSound();

											   m_world.addGameObject(superExplosion);
											   m_scene.addActor(*explosion);
											   return superExplosion;
	}
	case OBJECT_MEOW_MIX_SUPER:
	{
								  Model3D *model = NULL;
								  model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_MEOW_MIX_SUPER));
											   Renderable3D *renderable = new Renderable3D(model, true, true);
											   Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
											   Animatable *animatable = new Animatable();


											   PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution

											   PxRigidDynamic *beam = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_MEOW_MIX_SUPER, objectId, pos, geom, 0, NULL, NULL, NULL));
											   
											   Physicable *physicable = new Physicable(beam);

											   MeowMixSuper * superBeam = new MeowMixSuper(objectId, audioable, physicable, animatable, renderable, static_cast<Car *>(parent));
											   superBeam->setSound(ExplosionSound());
											   superBeam->playSound();

											   m_world.addGameObject(superBeam);
											   m_scene.addActor(*beam);
											   return superBeam;
	}
	case OBJECT_GARGANTULOUS_SUPER_VOLUME:
	{
											 Model3D *model = NULL;
											 model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_GARGANTULOUS_SUPER_VOLUME));
											   Renderable3D *renderable = new Renderable3D(model, true, true);
											   renderable->setModel(NULL); //remove when we have a good model
											   Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
											   Animatable *animatable = new Animatable();


											   PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution

											   PxRigidDynamic *superVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_GARGANTULOUS_SUPER_VOLUME, objectId, pos, geom, 0, NULL, NULL, NULL));

											   //animatable->setRotation(static_cast<Object3D *>(parent)->getFullRotation());
											   //animatable->setScale(glm::vec3(superVolume->getWorldBounds().getDimensions().x / 5, superVolume->getWorldBounds().getDimensions().y / 5, superVolume->getWorldBounds().getDimensions().z / 5));
											   Physicable *physicable = new Physicable(superVolume);

											   GargantulousSuper *super = new GargantulousSuper(objectId, audioable, physicable, animatable, renderable, static_cast<Car *>(parent));
											   super->setSound(ExplosionSound());
											   super->playSound();

											   m_world.addGameObject(super);
											   m_scene.addActor(*superVolume);
											   return super;
	}

	case OBJECT_GARGANTULOUS_SUPER_BULLET:
	{
											 Model3D *model = NULL;
											 model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_GARGANTULOUS_SUPER_BULLET));
											 Renderable3D *renderable = new Renderable3D(model, true, true);
											
											 Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
											 Animatable *animatable = new Animatable();


											 PxMaterial* material = PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f);    //static friction, dynamic friction, restitution

											 PxRigidDynamic *superVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_GARGANTULOUS_SUPER_BULLET, objectId, pos, geom, 0, NULL, NULL, NULL));

											 animatable->setRotation(static_cast<Object3D *>(parent)->getFullRotation());
											 animatable->setScale(glm::vec3(superVolume->getWorldBounds().getDimensions().x, superVolume->getWorldBounds().getDimensions().y, superVolume->getWorldBounds().getDimensions().z));
											 Physicable *physicable = new Physicable(superVolume);

											 HomingBullet *super = new HomingBullet(objectId, audioable, physicable, animatable, renderable, static_cast<Car *>(parent));
											 super->setSound(ExplosionSound());
											 super->playSound();

											 m_world.addGameObject(super);
											 m_scene.addActor(*superVolume);
											 return super;
	}
	case OBJECT_HEALTH_BAR:
	{
		Renderable2D *renderable = new Renderable2D(static_cast<Model2D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_UI_HEALTH_HUD)));
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		animatable->setPosition(glm::vec3(-.75f, -.5f, 0));
		animatable->setScale(glm::vec3(.55f, .38f, 1));
		Model2D *currentHealthModel = NULL,
			*lostHealthModel = NULL;
		currentHealthModel = static_cast<Model2D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_UI_HEALTH_CURRENT));
		lostHealthModel = static_cast<Model2D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_UI_HEALTH_LOST));
		HealthBar2D *bar = new HealthBar2D(objectId, audioable, animatable, renderable, currentHealthModel, lostHealthModel);

		return bar;
	}
	case OBJECT_GAUGE_BAR:
	{
		Renderable2D *renderable = new Renderable2D(static_cast<Model2D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_UI_GAUGE_HUD)));
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		animatable->setPosition(glm::vec3(-.70f, -.8f, 0));
		animatable->setScale(glm::vec3(.55f, .38f, 1));
		Model2D *currentGaugeModel = NULL;
		currentGaugeModel = static_cast<Model2D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_UI_GAUGE_CURRENT));
		std::vector<Model2D *> animationModels;
		animationModels.push_back(static_cast<Model2D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_1)));
		animationModels.push_back(static_cast<Model2D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_2)));
		animationModels.push_back(static_cast<Model2D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_3)));
		animationModels.push_back(static_cast<Model2D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_4)));
		animationModels.push_back(static_cast<Model2D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_5)));
		animationModels.push_back(static_cast<Model2D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_UI_GAUGE_FULL_EFFECT_6)));

		GaugeBar *bar = new GaugeBar(objectId, audioable, animatable, renderable, currentGaugeModel, animationModels);

		return bar;
	}
	case OBJECT_TEXT_2D:
	{
		Renderable2D *renderable = new Renderable2D(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();

		Text2D *bar = new Text2D(objectId, audioable, animatable, renderable);

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
		Model3D *model = NULL;
		model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_GGO));
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
								  Model3D *model = NULL;
								  model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_SHIELD_POWERUP_ACTIVE));
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
	case OBJECT_TRAIN_CAR:
	{
							 Model3D *model = NULL;
							 model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_TRAIN_CAR));
		Renderable3D *renderable = new Renderable3D(model, true, true);

		Animatable *animatable = new Animatable();
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());

		
		PxRigidDynamic *trainCarTriggerVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::DEATH_VOLUME, objectId, pos, geom, 0, NULL, NULL, NULL));
	
		Physicable *physicable = new Physicable(trainCarTriggerVolume);
		PxVec3 dim = trainCarTriggerVolume->getWorldBounds().getDimensions();
		
		animatable->setScale(glm::vec3(dim.x, dim.y, dim.z));
		pos->p.y += dim.y / 2;
		TrainCar *trainCar = new TrainCar(objectId, audioable, physicable, animatable, renderable, pos->p);

		m_world.addGameObject(trainCar);
		m_scene.addActor(*trainCarTriggerVolume);
		return trainCar;
	}

	case OBJECT_DEATH_PIT:
	{
							 //Model3D *model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_TRAIN_CAR));
							 //Renderable3D *renderable = new Renderable3D(model, true, true);
							 //renderable->setModel(NULL);
							 //Animatable *animatable = new Animatable();
							 //Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());


							 PxRigidDynamic *trainCarTriggerVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::DEATH_VOLUME, objectId, pos, geom, 0, NULL, NULL, NULL));

							 //Physicable *physicable = new Physicable(trainCarTriggerVolume);
							 PxVec3 dim = trainCarTriggerVolume->getWorldBounds().getDimensions();

							 //animatable->setScale(glm::vec3(dim.x, dim.y, dim.z));
							 //pos->p.y += dim.y / 2;
							 //TrainCar *trainCar = new TrainCar(objectId, audioable, physicable, animatable, renderable, pos->p);

							 //m_world.addGameObject(trainCar);
							 m_scene.addActor(*trainCarTriggerVolume);
							 return NULL;
	}
	case OBJECT_SPEED_POWERUP:
	{
								 Model3D *model = NULL;
								 model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_SPEED_POWERUP_ACTIVE));
						   Renderable3D *renderable = new Renderable3D(model, true, true);
						 
						   Animatable *animatable = new Animatable();
						   Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());

						   PxRigidDynamic *powerupTriggerVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::SPEED_POWERUP, objectId, pos, geom, 0, NULL, NULL, NULL));
						   Physicable *physicable = new Physicable(powerupTriggerVolume);
						   animatable->setScale(glm::vec3(powerupTriggerVolume->getWorldBounds().getDimensions().x/1.2, powerupTriggerVolume->getWorldBounds().getDimensions().y/4, 3));

						   PowerUpSpeed *powerup = new PowerUpSpeed(objectId, audioable, physicable, animatable, renderable, static_cast<Car*>(parent));

						   m_world.addGameObject(powerup);
						   m_scene.addActor(*powerupTriggerVolume);

						   return powerup;
	}
	case OBJECT_ATTACK_POWERUP:
	{
								  Model3D *model = NULL;
								  model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_ATTACK_POWERUP_PICKUP));
								 Renderable3D *renderable = new Renderable3D(model, true, true);
								 renderable->setModel(NULL);  // remove when there is a model for the powerup
								 Animatable *animatable = new Animatable();
								 Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());

								 PxRigidDynamic *powerupTriggerVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::SPEED_POWERUP, objectId, pos, geom, 0, NULL, NULL, NULL));
								 Physicable *physicable = new Physicable(powerupTriggerVolume);
								 //animatable->setScale(glm::vec3(powerupTriggerVolume->getWorldBounds().getDimensions().x, powerupTriggerVolume->getWorldBounds().getDimensions().y, powerupTriggerVolume->getWorldBounds().getDimensions().z));

								 PowerUpAttack *powerup = new PowerUpAttack(objectId, audioable, physicable, animatable, renderable, static_cast<Car*>(parent));

								 m_world.addGameObject(powerup);
								 m_scene.addActor(*powerupTriggerVolume);

								 return powerup;
	}

	case OBJECT_POWERUP:
	{
						   Model3D *model = NULL;
						   model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_ATTACK_POWERUP_PICKUP));
						   Renderable3D *renderable = new Renderable3D(model, true, true);
						   Animatable *animatable = new Animatable();
						   Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());

						   PxRigidDynamic *powerupTriggerVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::POWER_UP, objectId, pos, geom, 0, NULL, NULL, NULL));
						   Physicable *physicable = new Physicable(powerupTriggerVolume);
						   animatable->setScale(glm::vec3(powerupTriggerVolume->getWorldBounds().getDimensions().x, powerupTriggerVolume->getWorldBounds().getDimensions().y, powerupTriggerVolume->getWorldBounds().getDimensions().z));

						   PowerUp *powerup = new PowerUp(objectId, audioable, physicable, animatable, renderable);

						   m_world.addGameObject(powerup);
						   m_scene.addActor(*powerupTriggerVolume);

						   //setup updaters
						   ObjectPositionUpdater *updUp1 = new ObjectPositionUpdater(powerup, glm::vec3(0, 1, 0), .4f);
						   ObjectPositionUpdater *updDown = new ObjectPositionUpdater(powerup, glm::vec3(0, -2, 0), .8f);
						   ObjectPositionUpdater *updUp2 = new ObjectPositionUpdater(powerup, glm::vec3(0, 1, 0), .4f);
						   ObjectUpdaterSequence *seq = new ObjectUpdaterSequence(ObjectUpdaterSequence::TYPE_ONCE);
						   seq->addObjectUpdater(updUp1);
						   seq->addObjectUpdater(updDown);
						   seq->addObjectUpdater(updUp2);
						   ObjectRotationUpdater *updRot = new ObjectRotationUpdater(powerup, glm::vec3(0, 180, 0), 1.6f, ObjectRotationUpdater::ANGLE_TYPE_DEGREES);
						   ObjectUpdaterParallel *par = new ObjectUpdaterParallel(ObjectUpdaterParallel::TYPE_INFINITE);
						   par->addObjectUpdater(seq);
						   par->addObjectUpdater(updRot);
						   m_world.addObjectUpdater(par);

						   return powerup;
	}
	case OBJECT_PARTICLE:
	{
							Model3D *model = NULL;
							model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_PARTICLE_POWERUP_ATTACK));
							Renderable3D *renderable = new Renderable3D(model, true, true);
							Animatable *animatable = new Animatable();
							
							Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());

							PxRigidDynamic *particleVolume = static_cast<PxRigidDynamic *>(m_physicsFactory->makePhysicsObject(PhysicsFactory::PHYSICAL_OBJECT_PARTICLE, objectId, pos, geom, 0, NULL, NULL, NULL));
							Physicable *physicable = new Physicable(particleVolume);
							
							//animatable->setScale(glm::vec3(particleVolume->getWorldBounds().getDimensions().x, particleVolume->getWorldBounds().getDimensions().y, particleVolume->getWorldBounds().getDimensions().z));

							Particle *particle = new Particle(objectId, audioable, physicable, animatable, renderable, NULL);

							m_world.addGameObject(particle);
							m_scene.addActor(*particleVolume);

							return particle;
	}
	case OBJECT_EXPLOSION_1:
	{
							   Model3D *model = NULL;
							   model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_EXPLOSION1_1));
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
									Model3D *model = NULL;
									model = static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_GGO));
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
	case OBJECT_UI_POWERUP_BORDER_ICON:
	{
		Renderable2D *renderable = new Renderable2D(static_cast<Model2D*>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_POWERUP_BORDER)));
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		animatable->setPosition(glm::vec3(0, -.75f, 0));
		animatable->setScale(glm::vec3(.38f, .38f, 0));

		TexturedObject2D *border = new TexturedObject2D(objectId, audioable, animatable, renderable);

		return border;
	}
	case OBJECT_UI_SHIELD_POWERUP_ICON:
	{
		Renderable2D *renderable = new Renderable2D(static_cast<Model2D*>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_DEFENSE_POWERUP_ICON)));
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		animatable->setPosition(glm::vec3(0, -.75f, 0));
		animatable->setScale(glm::vec3(.34f, .34f, 0));

		TexturedObject2D *icon = new TexturedObject2D(objectId, audioable, animatable, renderable);

		return icon;
	}
	case OBJECT_UI_ATTACK_POWERUP_ICON:
	{
		Renderable2D *renderable = new Renderable2D(static_cast<Model2D*>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_ATTACK_POWERUP_ICON)));
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		animatable->setPosition(glm::vec3(0, -.75f, 0));
		animatable->setScale(glm::vec3(.34f, .34f, 0));

		TexturedObject2D *icon = new TexturedObject2D(objectId, audioable, animatable, renderable);

		return icon;
	}
	case OBJECT_UI_SPEED_POWERUP_ICON:
	{
		Renderable2D *renderable = new Renderable2D(static_cast<Model2D*>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_SPEED_POWERUP_ICON)));
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		animatable->setPosition(glm::vec3(0, -.75f, 0));
		animatable->setScale(glm::vec3(.34f, .34f, 0));

		TexturedObject2D *icon = new TexturedObject2D(objectId, audioable, animatable, renderable);

		return icon;
	}
	case OBJECT_UI_MAP:
	{
		Renderable2D *renderable = new Renderable2D(static_cast<Model2D*>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_MAP_TEXTURE)));
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();
		animatable->setPosition(glm::vec3(.75f, -.75f, 0));
		animatable->setScale(glm::vec3(.38f, .38f, 0));

		MapUI *map = new MapUI(objectId, audioable, animatable, renderable);
		map->setPlayerModel(static_cast<Model2D*>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_PLAYER_ON_UI_MAP_TEXTURE)));

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
	case OBJECT_UI_SCORE_TABLE:
	{
		Renderable2D *renderable = new Renderable2D(NULL);
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());
		Animatable *animatable = new Animatable();

		UIScoreTable *table = new UIScoreTable(objectId, audioable, animatable, renderable);
		animatable->setPosition(glm::vec3(0, glutGet(GLUT_WINDOW_HEIGHT) - table->getFontSize(), 0));

		return table;
	}
	case OBJECT_SKY_BOX:
	{
		Renderable3D *renderable = new Renderable3D(static_cast<Model3D *>(m_renderFactory->makeRenderableObject(RenderFactory::RENDERABLE_OBJECT_SKY_BOX)), true, true);
		Animatable *animatable = new Animatable();
		animatable->setScale(glm::vec3(5000, 5000, 5000));
		Audioable *audioable = new Audioable(m_audioFactory->getAudioHandle());

		Physicable *physicable = new Physicable(NULL);

		Object3D *skybox = new Object3D(objectId, audioable, physicable, animatable, renderable, NULL);

		m_world.addGameObject(skybox);

		return skybox;
	
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