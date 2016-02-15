#include "GameSimulation.h"
#include "PhysicsManager.h"
#include "PxDefaultCpuDispatcher.h"
#include "PxDefaultSimulationFilterShader.h"
#include "Objects\ObjectCreators\SnippetVehicleCreate.h"
#include "Objects\ObjectCreators\SnippetVehicleTireFriction.h"

using namespace std;
bool gIsVehicleInAir = true;

GameSimulation::GameSimulation(PhysicsManager& physicsInstance, PlayerControllable * player)
: m_physicsHandler(physicsInstance)
{
	m_mainCamera = new Camera();
	player->setCamera(m_mainCamera);
	
	m_players.push_back(player);
	player->setGameWorld(m_world);
	
	initialize();
	

}
static PxF32 gTireFrictionMultipliers[MAX_NUM_SURFACE_TYPES][MAX_NUM_TIRE_TYPES] =
{
	//NORMAL,	WORN
	{ 1.00f, 0.1f }//TARMAC
};
GameSimulation::~GameSimulation()
{
}
//Drivable surface types.
/*enum
{
	SURFACE_TYPE_TARMAC = 0,
	MAX_NUM_SURFACE_TYPES
};

//Tire types.
enum
{
	TIRE_TYPE_NORMAL = 0,
	TIRE_TYPE_WORN,
	MAX_NUM_TIRE_TYPES
};*/
PxF32 gSteerVsForwardSpeedData[2 * 8] =
{
	0.0f, 0.75f,
	5.0f, 0.75f,
	30.0f, 0.125f,
	120.0f, 0.1f,
	PX_MAX_F32, PX_MAX_F32,
	PX_MAX_F32, PX_MAX_F32,
	PX_MAX_F32, PX_MAX_F32,
	PX_MAX_F32, PX_MAX_F32
};
PxFixedSizeLookupTable<8> gSteerVsForwardSpeedTable(gSteerVsForwardSpeedData, 4);

PxVehicleDrive4WRawInputData gVehicleInputData;
PxVehicleKeySmoothingData gKeySmoothingData =
{
	{
		6.0f,	//rise rate eANALOG_INPUT_ACCEL
		6.0f,	//rise rate eANALOG_INPUT_BRAKE		
		6.0f,	//rise rate eANALOG_INPUT_HANDBRAKE	
		2.5f,	//rise rate eANALOG_INPUT_STEER_LEFT
		2.5f,	//rise rate eANALOG_INPUT_STEER_RIGHT
	},
	{
		10.0f,	//fall rate eANALOG_INPUT_ACCEL
		10.0f,	//fall rate eANALOG_INPUT_BRAKE		
		10.0f,	//fall rate eANALOG_INPUT_HANDBRAKE	
		5.0f,	//fall rate eANALOG_INPUT_STEER_LEFT
		5.0f	//fall rate eANALOG_INPUT_STEER_RIGHT
	}
};

PxVehiclePadSmoothingData gPadSmoothingData =
{
	{
		6.0f,	//rise rate eANALOG_INPUT_ACCEL
		6.0f,	//rise rate eANALOG_INPUT_BRAKE		
		6.0f,	//rise rate eANALOG_INPUT_HANDBRAKE	
		2.5f,	//rise rate eANALOG_INPUT_STEER_LEFT
		2.5f,	//rise rate eANALOG_INPUT_STEER_RIGHT
	},
	{
		10.0f,	//fall rate eANALOG_INPUT_ACCEL
		10.0f,	//fall rate eANALOG_INPUT_BRAKE		
		10.0f,	//fall rate eANALOG_INPUT_HANDBRAKE	
		5.0f,	//fall rate eANALOG_INPUT_STEER_LEFT
		5.0f	//fall rate eANALOG_INPUT_STEER_RIGHT
	}
};

enum DriveMode
{
	eDRIVE_MODE_ACCEL_FORWARDS = 0,
	eDRIVE_MODE_ACCEL_REVERSE,
	eDRIVE_MODE_HARD_TURN_LEFT,
	eDRIVE_MODE_HANDBRAKE_TURN_LEFT,
	eDRIVE_MODE_HARD_TURN_RIGHT,
	eDRIVE_MODE_HANDBRAKE_TURN_RIGHT,
	eDRIVE_MODE_BRAKE,
	eDRIVE_MODE_NONE
};

DriveMode gDriveModeOrder[] =
{
	eDRIVE_MODE_BRAKE,
	eDRIVE_MODE_ACCEL_FORWARDS,
	eDRIVE_MODE_BRAKE,
	eDRIVE_MODE_ACCEL_REVERSE,
	eDRIVE_MODE_BRAKE,
	eDRIVE_MODE_HARD_TURN_LEFT,
	eDRIVE_MODE_BRAKE,
	eDRIVE_MODE_HARD_TURN_RIGHT,
	eDRIVE_MODE_ACCEL_FORWARDS,
	eDRIVE_MODE_HANDBRAKE_TURN_LEFT,
	eDRIVE_MODE_ACCEL_FORWARDS,
	eDRIVE_MODE_HANDBRAKE_TURN_RIGHT,
	eDRIVE_MODE_NONE
};

bool PxVehicleIsInAir(const PxVehicleWheelQueryResult& vehWheelQueryResults)
{
	if (!vehWheelQueryResults.wheelQueryResults)
	{
		return true;
	}

	for (PxU32 i = 0; i<vehWheelQueryResults.nbWheelQueryResults; i++)
	{
		if (!vehWheelQueryResults.wheelQueryResults[i].isInAir)
		{
			return false;
		}
	}
	return true;
}

void GameSimulation::simulatePhysics(double dt)
{
//	audio->update();
	const PxF32 timestep = 1.0f / 60.0f;

	//Raycasts.
	
	PxVehicleWheels* vehicles[1] = { car };
	PxRaycastQueryResult* raycastResults = gVehicleSceneQueryData->getRaycastQueryResultBuffer(0);
	const PxU32 raycastResultsSize = gVehicleSceneQueryData->getRaycastQueryResultBufferSize();
	PxVehicleSuspensionRaycasts(gBatchQuery, 1, vehicles, raycastResultsSize, raycastResults);

	//Vehicle update.
	const PxVec3 grav = m_scene->getGravity();
	PxWheelQueryResult wheelQueryResults[PX_MAX_NB_WHEELS];
	PxVehicleWheelQueryResult vehicleQueryResults[1] = { { wheelQueryResults, car->mWheelsSimData.getNbWheels() } };
	PxVehicleUpdates(timestep, grav, *gFrictionPairs, 1, vehicles, vehicleQueryResults);

	//Work out if the vehicle is in the air.
	gIsVehicleInAir = car->getRigidDynamicActor()->isSleeping() ? false : PxVehicleIsInAir(vehicleQueryResults[0]);
	//gIsVehicleInAir = false;
	m_scene->simulate(timestep);
	m_scene->fetchResults(true);

}

void GameSimulation::simulateAnimation()
{
}

void GameSimulation::simulateAI()
{
}

void GameSimulation::simulatePlayers(double dt)
{
	for (unsigned int i = 0; i < m_players.size(); i++)
	{
		m_players[i]->playFrame(dt);
	}
}

void GameSimulation::updateObjects(double dt) {

	m_mainCamera->update(dt);

	for (unsigned int i = 0; i < updaters.size(); i++) {
		updaters.at(i)->update( (float)dt);
	}

}

void GameSimulation::initialize() {
	createPhysicsScene();
	setupBasicGameWorldObjects();
}

PxFilterFlags testFilter(
	PxFilterObjectAttributes attributes0, PxFilterData filterData0, 
	PxFilterObjectAttributes attributes1, PxFilterData filterData1, 
	PxPairFlags &pairFlags, const void *constantBlock, PxU32 constantBlockSize)
{
	if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	{
		std::cout << "Trigger Collision Occured \n";
		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
	}
	else {
		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
	}
	return PxFilterFlag::eDEFAULT;
}

PxFilterFlags SampleVehicleFilterShader(
	PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	PX_UNUSED(constantBlock);
	PX_UNUSED(constantBlockSize);

	// let triggers through
	if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
		return PxFilterFlags();
	}



	// use a group-based mechanism for all other pairs:
	// - Objects within the default group (mask 0) always collide
	// - By default, objects of the default group do not collide
	//   with any other group. If they should collide with another
	//   group then this can only be specified through the filter
	//   data of the default group objects (objects of a different
	//   group can not choose to do so)
	// - For objects that are not in the default group, a bitmask
	//   is used to define the groups they should collide with
	if ((filterData0.word0 != 0 || filterData1.word0 != 0) &&
		!(filterData0.word0&filterData1.word1 || filterData1.word0&filterData0.word1))
		return PxFilterFlag::eSUPPRESS;

	pairFlags = PxPairFlag::eCONTACT_DEFAULT;

	// The pairFlags for each object are stored in word2 of the filter data. Combine them.
	pairFlags |= PxPairFlags(PxU16(filterData0.word2 | filterData1.word2));
	return PxFilterFlags();
}

PxFilterFlags TestFilterShader(
	PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	// use a group-based mechanism for all other pairs:
	// - Objects within the default group (mask 0) always collide
	// - By default, objects of the default group do not collide
	//   with any other group. If they should collide with another
	//   group then this can only be specified through the filter
	//   data of the default group objects (objects of a different
	//   group can not choose to do so)
	// - For objects that are not in the default group, a bitmask
	//   is used to define the groups they should collide with
	if ((filterData0.word0 != 0 || filterData1.word0 != 0) &&
		!(filterData0.word0&filterData1.word1 || filterData1.word0&filterData0.word1))
		return PxFilterFlag::eSUPPRESS;

	if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	{
		
		if (filterData0.word0 & filterData1.word1 || filterData0.word1 & filterData1.word0)
		{
		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			
	}
	}
	else {
		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		if (filterData0.word0 & filterData1.word1 || filterData0.word1 & filterData1.word0)
		{
		pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
	}
		

	}
	return PxFilterFlag::eDEFAULT;
}


void GameSimulation::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	
}


void GameSimulation::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	//Player Interactions. Shouldn't really be anyother type
	if (pairs->otherShape->getSimulationFilterData().word0 == PhysicsManager::PLAYER)
	{
		PlayerControllable * player = m_players[pairs->otherShape->getSimulationFilterData().word2];
		//std::cout << "hit waypoint " << pairs[0].triggerShape->getSimulationFilterData().word2 << std::endl;
		player->setWayPoint(m_wayPoints->getWayPointAt(pairs[0].triggerShape->getSimulationFilterData().word2),
			pairs[0].triggerShape->getSimulationFilterData().word3 == 1); // is it the finish line?
		
	}
}


void GameSimulation::createPhysicsScene()
{
	PxSceneDesc sceneDesc(m_physicsHandler.getScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	sceneDesc.simulationEventCallback = this;
	sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(8);

	if (!sceneDesc.filterShader)
	{
		sceneDesc.filterShader = TestFilterShader;
	}

	m_scene = m_physicsHandler.getPhysicsInstance().createScene(sceneDesc);
	if (!m_scene)
	{
		std::cout << "The scene is a lie. ERROR CODE: PX0005" << std::endl;
	}
	m_cooking = PxCreateCooking(PX_PHYSICS_VERSION, m_physicsHandler.getFoundation(), PxCookingParams(PxTolerancesScale()));
	if (!m_cooking)
	{
		std::cout << "A fatal error has occured. ERROR CODE PX0007" << std::endl;
	}

	PxInitVehicleSDK(m_physicsHandler.getPhysicsInstance());
	PxVehicleSetBasisVectors(PxVec3(0, 1, 0), PxVec3(0, 0, 1));
	PxVehicleSetUpdateMode(PxVehicleUpdateMode::eVELOCITY_CHANGE);
}



bool GameSimulation::simulateScene(double dt, SceneMessage &newMessage)
{
	simulateAI();
	simulatePlayers(dt);
	simulatePhysics(dt);
	simulateAnimation();
	updateObjects(dt);
	return false;
}


PxVehicleDrivableSurfaceToTireFrictionPairs* GameSimulation::createFrictionPairs(const PxMaterial* defaultMaterial)
{
	PxVehicleDrivableSurfaceType surfaceTypes[1];
	surfaceTypes[0].mType = SURFACE_TYPE_TARMAC;

	const PxMaterial* surfaceMaterials[1];
	surfaceMaterials[0] = defaultMaterial;

	PxVehicleDrivableSurfaceToTireFrictionPairs* surfaceTirePairs =
		PxVehicleDrivableSurfaceToTireFrictionPairs::allocate(MAX_NUM_TIRE_TYPES, MAX_NUM_SURFACE_TYPES);

	surfaceTirePairs->setup(MAX_NUM_TIRE_TYPES, MAX_NUM_SURFACE_TYPES, surfaceMaterials, surfaceTypes);

	for (PxU32 i = 0; i < MAX_NUM_SURFACE_TYPES; i++)
	{
		for (PxU32 j = 0; j < MAX_NUM_TIRE_TYPES; j++)
		{
			surfaceTirePairs->setTypePairFriction(i, j, gTireFrictionMultipliers[i][j]);
		}
	}
	return surfaceTirePairs;
}

void GameSimulation::setupBasicGameWorldObjects() {
	ObjModelLoader *loader = new ObjModelLoader();
	Car *obj = new Car();
	obj->setModel(loader->loadFromFile("Assets/Models/Ugly_Car.obj"), true, true);
	m_world->addGameObject(obj);
	PxMaterial* mMaterial;
	mMaterial = m_physicsHandler.getPhysicsInstance().createMaterial(0, 0, 0.1f);    //static friction, dynamic friction, restitution
	if (!mMaterial)
	{
		std::cout << "Material failed to create. ERROR CODE: PX0006" << std::endl;
	}

	//Set up the chassis mass, dimensions, moment of inertia, and center of mass offset.
	//The moment of inertia is just the moment of inertia of a cuboid but modified for easier steering.
	//Center of mass offset is 0.65m above the base of the chassis and 0.25m towards the front.
	const PxF32 chassisMass = 1500.0f;
	const PxVec3 chassisDims(2.5f, 2.0f, 5.0f);
	const PxVec3 chassisMOI
		((chassisDims.y*chassisDims.y + chassisDims.z*chassisDims.z)*chassisMass / 12.0f,
		(chassisDims.x*chassisDims.x + chassisDims.z*chassisDims.z)*0.8f*chassisMass / 12.0f,
		(chassisDims.x*chassisDims.x + chassisDims.y*chassisDims.y)*chassisMass / 12.0f);
	const PxVec3 chassisCMOffset(0.0f, -chassisDims.y*0.5f + 0.65f, 0.25f);

	//Set up the wheel mass, radius, width, moment of inertia, and number of wheels.
	//Moment of inertia is just the moment of inertia of a cylinder.
	const PxF32 wheelMass = 20.0f;
	const PxF32 wheelRadius = 0.5f;
	const PxF32 wheelWidth = 0.4f;
	const PxF32 wheelMOI = 0.5f*wheelMass*wheelRadius*wheelRadius;
	const PxU32 nbWheels = 6;



	//Create the batched scene queries for the suspension raycasts.
	gVehicleSceneQueryData = VehicleSceneQueryData::allocate(1, PX_MAX_NB_WHEELS, 1, *m_physicsHandler.getAllocator());
	gBatchQuery = VehicleSceneQueryData::setUpBatchedSceneQuery(0, *gVehicleSceneQueryData, m_scene);

	//Create the friction table for each combination of tire and surface type.
	gFrictionPairs = createFrictionPairs(mMaterial);

	VehicleDesc vehicleDesc;
	vehicleDesc.chassisMass = chassisMass;
	vehicleDesc.chassisDims = chassisDims;
	vehicleDesc.chassisMOI = chassisMOI;
	vehicleDesc.chassisCMOffset = chassisCMOffset;
	vehicleDesc.chassisMaterial = mMaterial;
	vehicleDesc.wheelMass = wheelMass;
	vehicleDesc.wheelRadius = wheelRadius;
	vehicleDesc.wheelWidth = wheelWidth;
	vehicleDesc.wheelMOI = wheelMOI;
	vehicleDesc.numWheels = nbWheels;
	vehicleDesc.wheelMaterial = mMaterial;
	PxRigidStatic* gGroundPlane = NULL;
	//Create a plane to drive on.
	gGroundPlane = createDrivablePlane(mMaterial, &m_physicsHandler.getPhysicsInstance());
	m_scene->addActor(*gGroundPlane);
	loader = new ObjModelLoader();
	/*
	RenderableObject *plane = new RenderableObject();
	plane->model = loader->loadFromFile("Assets/Models/plane.obj");
	plane->setActor(gGroundPlane);
	m_world->addGameObject(plane);
	*/

	//Create a vehicle that will drive on the plane.
	car = createVehicle4W(vehicleDesc, &m_physicsHandler.getPhysicsInstance(), m_cooking);
	PxTransform startTransform(PxVec3(0, 3+(vehicleDesc.chassisDims.y*0.5f + vehicleDesc.wheelRadius + 1.0f), 0), PxQuat(PxIdentity));
	car->getRigidDynamicActor()->setGlobalPose(startTransform);
	m_scene->addActor(*car->getRigidDynamicActor());

	//Set the vehicle to rest in first gear.
	//Set the vehicle to use auto-gears.
	car->setToRestState();
	car->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
	car->mDriveDynData.setUseAutoGears(true);
	//std::cout << car->getRigidDynamicActor()->getWorldBounds().getDimensions().y << " " << car->getRigidDynamicActor()->getWorldBounds().minimum.y << " " << car->getRigidDynamicActor()->getWorldBounds().maximum.y << std::endl;
	//obj->updatePosition(glm::vec3(0, -car->getRigidDynamicActor()->getWorldBounds().getDimensions().y / 2 , 0));
	int k = (int)car->mWheelsSimData.getWheelData(0).mRadius * 2;
	obj->updateScale(glm::vec3(car->getRigidDynamicActor()->getWorldBounds().getDimensions().x, car->getRigidDynamicActor()->getWorldBounds().getDimensions().y + k, car->getRigidDynamicActor()->getWorldBounds().getDimensions().z));
	//	gVehicleInputData.setDigitalAccel(true); TOMS TODO

	gVehicleModeTimer = 0.0f;
	gVehicleOrderProgress = 0;
	obj->setCar(car);

	//PxRigidDynamic *tmpActor = m_physicsHandler.getPhysicsInstance().createRigidDynamic(PxTransform(0, 5, -40));
	//PxShape* aSphereShape = tmpActor->createShape(PxSphereGeometry(0.2), *mMaterial);
	//PxRigidBodyExt::updateMassAndInertia(*tmpActor, 0.5);


	// PETER!!!

	//load stormtrooper
	/*ObjModelLoader *loader = new ObjModelLoader();
	RenderableObject *obj = new RenderableObject();
	obj->model = loader->loadFromFile("Assets/Models/Stormtrooper.obj");
	m_world->addGameObject(obj);
	PxRigidDynamic *tmpActor = m_physicsHandler.getPhysicsInstance().createRigidDynamic(PxTransform(0, 0, -45));

	PxShape* aSphereShape = tmpActor->createShape(PxBoxGeometry(1, .1, 1), *mMaterial);
	m_physicsHandler.setupFiltering(tmpActor,
		PhysicsManager::PLAYER,
		PhysicsManager::ENVIRONMENT | PhysicsManager::PROJECTILE | PhysicsManager::POWERUP | PhysicsManager::WAYPOINT,
		0, 0);
	PxRigidBodyExt::updateMassAndInertia(*tmpActor, 0.5);
	obj->setActor(tmpActor);
	m_scene->addActor(*tmpActor);*/

	//m_scene->addActor(*tmpActor);
	//assign stormtrooper to main char
	m_players[0]->setObject(obj);
	
	//attach camera to stormtrooper
	m_mainCamera->setToFollow(obj);

	Projectile * ammo = new Projectile("");
	RenderableObject *ammoModel = new RenderableObject();
	ammoModel->setModel(loader->loadFromFile("Assets/Models/bullet.obj"), true);
	ammo->setObject(ammoModel);
	m_players[0]->setAmmunition(ammo);


	

	float length = 50;
	float width = 10;
	//create a plane to run on
	//PxRigidStatic * plane = PxCreatePlane(m_physicsHandler.getPhysicsInstance(), PxPlane(PxVec3(0, 1, 0), 0), *mMaterial);
	PxRigidStatic * floor = m_physicsHandler.getPhysicsInstance().createRigidStatic(PxTransform(0, -.5, 0));
	floor->createShape(PxBoxGeometry(width, .5, length), *mMaterial);
	m_scene->addActor(*floor);

	PxRigidStatic * leftWall = m_physicsHandler.getPhysicsInstance().createRigidStatic(PxTransform(width, 0, 0));
	leftWall->createShape(PxBoxGeometry(0.5, width, length), *mMaterial);
	m_scene->addActor(*leftWall);
	PxRigidStatic * rightWall = m_physicsHandler.getPhysicsInstance().createRigidStatic(PxTransform(-width, 0, 0));
	rightWall->createShape(PxBoxGeometry(.5, width, length), *mMaterial);
	m_scene->addActor(*rightWall);
	PxRigidStatic * frontWall = m_physicsHandler.getPhysicsInstance().createRigidStatic(PxTransform(0, 0, length));
	frontWall->createShape(PxBoxGeometry(width, width, 0.5), *mMaterial);
	m_scene->addActor(*frontWall);
	PxRigidStatic * backWall = m_physicsHandler.getPhysicsInstance().createRigidStatic(PxTransform(0, 0, -length));
	backWall->createShape(PxBoxGeometry(width, width, 0.5), *mMaterial);
	m_scene->addActor(*backWall);
	
	//if (!plane)
	//{
		//std::cout << "Something went wrong loading the plane..\n";
	//}
	//m_scene->addActor(*plane);
	
	//draw the floor
	loader = new ObjModelLoader();
	RenderableObject * drawPlane = new RenderableObject();
	drawPlane->setModel(loader->loadFromFile("Assets/Models/plane.obj"));
	drawPlane->setActor(floor);
	m_world->addGameObject(drawPlane);

	loader = new ObjModelLoader();
	RenderableObject * leftPlane = new RenderableObject();
	leftPlane->setModel(loader->loadFromFile("Assets/Models/plane.obj"));
	leftPlane->setActor(leftWall);
	leftPlane->updateRotation(glm::vec3(0, 0, 3.14 / 2));
	m_world->addGameObject(leftPlane);

	loader = new ObjModelLoader();
	RenderableObject * RightPlane = new RenderableObject();
	RightPlane->setModel(loader->loadFromFile("Assets/Models/plane.obj"));
	RightPlane->setActor(rightWall);
	RightPlane->updateRotation(glm::vec3(0, 0, 3.14 / 2));
	m_world->addGameObject(RightPlane);


	//drawthe finish line
	loader = new ObjModelLoader();
	RenderableObject * finishLine = new RenderableObject();
	finishLine->setModel(loader->loadFromFile("Assets/Models/finishLine.obj"));
	m_world->addGameObject(finishLine);

	//create a bounding box for storm tropper to run into
	PxRigidStatic *boundVolume = m_physicsHandler.getPhysicsInstance().createRigidStatic(PxTransform(0, 0, length - 5));
	PxShape* aSphereShape = boundVolume->createShape(PxBoxGeometry(PxVec3(2, 5, 3)), *mMaterial);
	aSphereShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	aSphereShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	//m_scene->addActor(*boundVolume);
	finishLine->setActor(boundVolume);
	m_physicsHandler.setupFiltering(boundVolume,
		PhysicsManager::WAYPOINT,
		PhysicsManager::PLAYER,
		0,
		0);

	//create waypoints
	
	vector<glm::vec3> positions;
	positions.push_back(glm::vec3(0, 0, 40));
	positions.push_back(glm::vec3(0, 0, -40));
	positions.push_back(glm::vec3(0, 0, -20));
	positions.push_back(glm::vec3(0, 0, 0));
	positions.push_back(glm::vec3(0, 0, 20));

	m_wayPoints = new WayPointSystem(m_scene, positions);
	

/*	Mesh *mesh = new Mesh();
	mesh->loadFromFile("Assets/Models/Avent.obj");
	Model *model = new ObjModel("Assets/Models/Stormtrooper.obj");
	VAO *vao = new VAO(model);
	GameObject *obj = new GameObject(vao, model);
	obj->mesh = mesh;
	world->addGameObject(obj);*/
	//ObjectPositionUpdater *up = new ObjectPositionUpdater(obj, glm::vec3(-15, -15, -15), 3000);
	//updaters.push_back(up);
	//ObjectRotationUpdater *up = new ObjectRotationUpdater(obj, glm::vec3(0, 180, 0), 10000, ObjectRotationUpdater::ANGLE_TYPE_DEGREES);

	//--------------------TEST 1------------------------------------------------------------------------------------------------
	/*
	ObjectUpdaterSequence *upd = new ObjectUpdaterSequence(ObjectUpdaterSequence::TYPE_MULTIPLE_TIMES, 3);
	upd->addObjectUpdater(new ObjectRotationUpdater(obj, glm::vec3(0, 180, 0), 3000, ObjectRotationUpdater::ANGLE_TYPE_DEGREES));
	upd->addObjectUpdater(new ObjectPositionUpdater(obj, glm::vec3(-1, -1, -1), 1000));
	updaters.push_back(upd);
	*/

	//--------------------TEST 2------------------------------------------------------------------------------------------------
	/*
	ObjectUpdaterSequence *upd = new ObjectUpdaterSequence(ObjectUpdaterSequence::TYPE_INFINITE);
	upd->addObjectUpdater(new ObjectPositionUpdater(obj, glm::vec3(0, 0.5, 0), 1000));
	upd->addObjectUpdater(new ObjectPositionUpdater(obj, glm::vec3(0, -1, 0), 2000));
	upd->addObjectUpdater(new ObjectPositionUpdater(obj, glm::vec3(0, 0.5, 0), 1000));
	updaters.push_back(upd);
	*/

	//--------------------TEST 3------------------------------------------------------------------------------------------------
	/*
	ObjectUpdaterSequence *upd1 = new ObjectUpdaterSequence(ObjectUpdaterSequence::TYPE_ONCE);
	upd1->addObjectUpdater(new ObjectPositionUpdater(obj, glm::vec3(0, 0.5, 0), 1));
	upd1->addObjectUpdater(new ObjectPositionUpdater(obj, glm::vec3(0, -1, 0), 2));
	upd1->addObjectUpdater(new ObjectPositionUpdater(obj, glm::vec3(0, 0.5, 0), 1));

	ObjectUpdaterParallel *upd = new ObjectUpdaterParallel(ObjectUpdaterSequence::TYPE_INFINITE);
	upd->addObjectUpdater(upd1);
	upd->addObjectUpdater(new ObjectRotationUpdater(obj, glm::vec3(0, 180, 0), 1, ObjectRotationUpdater::ANGLE_TYPE_DEGREES));
	updaters.push_back(upd);*/
	
}

