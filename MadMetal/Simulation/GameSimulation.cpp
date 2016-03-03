#include "Game Logic\WayPointSystem.h"
#include "GameSimulation.h"
#include "GameSimulationDefinitions.h"
#include "Objects/Cars/MeowMix.h"
#include "Objects/Model.h"
#include "Objects/ObjectLoaders/ObjModelLoader.h"
#include "Objects/ObjectUpdaters/ObjectPositionUpdater.h"
#include "Objects/ObjectUpdaters/ObjectRotationUpdater.h"
#include "Objects/ObjectUpdaters/ObjectUpdaterParallel.h"
#include "Objects/ObjectUpdaters/ObjectUpdaterSequence.h"
#include "Objects/RenderableObject.h"
#include "PhysicsManager.h"
#include "Objects\ObjectCreators\VehicleCreator.h"
#include "CollisionManager.h"

#define NUM_OF_PLAYERS 8

using namespace std;
bool gIsVehicleInAir = true;

GameSimulation::GameSimulation(vector<ControllableTemplate *> playerTemplates, Audio* audioHandle)
{
	std::cout << "GameSimulation pushed onto the stack \n";
	createPhysicsScene();
	
	m_gameFactory = GameFactory::instance(*m_world, *m_scene, *audioHandle);

	//create characters for game from templates
	for (int i = 0; i < playerTemplates.size(); i++)
	{
		if (playerTemplates[i]->getGamePad() != NULL) //if a game pad is assigned, it is a human player
		{
			PlayerControllable * humanPlayer = new PlayerControllable(*playerTemplates[i]);
			//todo: make a car for player based off template
			m_humanPlayers.push_back(humanPlayer);
			m_players.push_back(humanPlayer);

			//pass players camera to scene cameras
			m_sceneCameras.push_back(humanPlayer->getCamera());

		}
		else {
			m_players.push_back(new AIControllable(*playerTemplates[i]));
			//make a car for ai based off template
		}
	}

	
	//add when car is created by this point. 
	//m_mainCamera = m_humanPlayers[0]->getCamera();
	
	initialize();
}

GameSimulation::~GameSimulation()
{
}

PxFixedSizeLookupTable<8> gSteerVsForwardSpeedTable(gSteerVsForwardSpeedData, 4);

PxVehicleDrive4WRawInputData gVehicleInputData;

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

	const PxF32 timestep = 1.0f / 60.0f;

	//Raycasts.
	
	PxVehicleWheels* vehicles[1] = { &m_humanPlayers[0]->getCar()->getCar() };
	PxRaycastQueryResult* raycastResults = gVehicleSceneQueryData->getRaycastQueryResultBuffer(0);
	const PxU32 raycastResultsSize = gVehicleSceneQueryData->getRaycastQueryResultBufferSize();
	PxVehicleSuspensionRaycasts(gBatchQuery, 1, vehicles, raycastResultsSize, raycastResults);

	//Vehicle update.
	const PxVec3 grav = m_scene->getGravity();
	PxWheelQueryResult wheelQueryResults[PX_MAX_NB_WHEELS];
	PxVehicleWheelQueryResult vehicleQueryResults[1] = { { wheelQueryResults, m_humanPlayers[0]->getCar()->getCar().mWheelsSimData.getNbWheels() } };
	PxVehicleUpdates(timestep, grav, *gFrictionPairs, 1, vehicles, vehicleQueryResults);

	//Work out if the vehicle is in the air.
	gIsVehicleInAir = m_humanPlayers[0]->getCar()->getCar().getRigidDynamicActor()->isSleeping() ? false : PxVehicleIsInAir(vehicleQueryResults[0]);

	// PLUG IN PITCH CORRECTION CODE HERE

	/*
	PxVec3 angularVelocity = m_humanPlayers[0]->getCar()->getCar().getRigidDynamicActor()->getAngularVelocity();


	PxShape *tempBuffer[PX_MAX_NB_WHEELS + 1];
	m_humanPlayers[0]->getCar()->getCar().getRigidDynamicActor()->getShapes(tempBuffer, m_humanPlayers[0]->getCar()->getCar().getRigidDynamicActor()->getNbShapes());

	bool carTilt = false;
	float lowest = 100000;
	float highest = -100000;
	for (int i = 0; i < 4; i++)
	{
		if (tempBuffer[i]->getLocalPose().p.y > highest) highest = tempBuffer[i]->getLocalPose().p.y;
		if (tempBuffer[i]->getLocalPose().p.y < highest) lowest = tempBuffer[i]->getLocalPose().p.y;
		cout << tempBuffer[i]->getLocalPose().p.y << endl;;
	}
	cout << endl << endl;
	//cout << lowest << " " << highest << endl;

	float pitchDist = abs(highest - lowest);

	if (gIsVehicleInAir && pitchDist > 1 )
	{
		//m_humanPlayers[0]->getCar()->getCar().getRigidDynamicActor()->setAngularVelocity(m_humanPlayers[0]->getCar()->getCar().getRigidDynamicActor()->getAngularVelocity() + PxVec3(-0.0000001 * pitchDist, 0, 0));
	}
	*/
	PxShape *tempBuffer[PX_MAX_NB_WHEELS + 1];
	m_humanPlayers[0]->getCar()->getCar().getRigidDynamicActor()->getShapes(tempBuffer, m_humanPlayers[0]->getCar()->getCar().getRigidDynamicActor()->getNbShapes());

	PxVec3 test = m_humanPlayers[0]->getCar()->getCar().getRigidDynamicActor()->getGlobalPose().q.getBasisVector1();

	if (test.y < 0.9 && gIsVehicleInAir)
	{
		cout << "PITCH ME" << endl;
		m_humanPlayers[0]->getCar()->getCar().getRigidDynamicActor()->setAngularVelocity(m_humanPlayers[0]->getCar()->getCar().getRigidDynamicActor()->getAngularVelocity() + PxVec3(-0.01, 0, 0));

	}
//	cout << test.x << " " << test.y << " " << test.z << endl;



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
		
		//m_players[i]->playFrame(dt);
		
	}
	m_humanPlayers[0]->playFrame(dt);
	
}

void GameSimulation::updateObjects(double dt) {

	m_world->update(dt);

	}

void GameSimulation::initialize() {
	setupBasicGameWorldObjects();
}

void GameSimulation::createPhysicsScene()
{
	PxSceneDesc sceneDesc(PhysicsManager::getScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);

	CollisionManager *manager = new CollisionManager(*m_world);
	sceneDesc.simulationEventCallback = manager;
	sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(8);

	if (!sceneDesc.filterShader)
	{
		sceneDesc.filterShader = CollisionManager::TestFilterShader;
	}

	m_scene = PhysicsManager::getPhysicsInstance().createScene(sceneDesc);
	if (!m_scene)
	{
		std::cout << "The scene is a lie. ERROR CODE: PX0005" << std::endl;
	}

	m_world->setScene(m_scene);

	PxInitVehicleSDK(PhysicsManager::getPhysicsInstance());
	PxVehicleSetBasisVectors(PxVec3(0, 1, 0), PxVec3(0, 0, 1));
	PxVehicleSetUpdateMode(PxVehicleUpdateMode::eVELOCITY_CHANGE);


	PxMaterial* mMaterial;
	mMaterial = PhysicsManager::getPhysicsInstance().createMaterial(0, 0, 0.1f);    //static friction, dynamic friction, restitution

	//Create the batched scene queries for the suspension raycasts.
	gVehicleSceneQueryData = VehicleSceneQueryData::allocate(NUM_OF_PLAYERS, PX_MAX_NB_WHEELS, NUM_OF_PLAYERS, *PhysicsManager::getAllocator());
	gBatchQuery = VehicleSceneQueryData::setUpBatchedSceneQuery(0, *gVehicleSceneQueryData, m_scene);

	//Create the friction table for each combination of tire and surface type.
	gFrictionPairs = createFrictionPairs(mMaterial);
}



bool GameSimulation::simulateScene(double dt, SceneMessage &newMessage)
{
	for (int i = 0; i < m_humanPlayers.size(); i++)
	{
		if (m_humanPlayers[i]->getGamePad() != NULL && m_humanPlayers[i]->getGamePad()->isPressed(GamePad::StartButton))
		{
			newMessage.setTag(SceneMessage::ePause);
			std::vector<ControllableTemplate *> playerTemplates;
			//put the controllables into the vector incase the player trys to restart
			for (int i = 0; i < m_players.size(); i++)
			{
				playerTemplates.push_back(&m_players[i]->getControllableTemplate());
			}
			//put a dummy controllable at the front of the vector so the pause screen knows who paused
			playerTemplates.push_back(new ControllableTemplate(m_humanPlayers[i]->getGamePad()));
			newMessage.setPlayerTemplates(playerTemplates);
			return true;
		}
	}
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
	PxMaterial* mMaterial;
	mMaterial = PhysicsManager::getPhysicsInstance().createMaterial(0, 0, 0.1f);    //static friction, dynamic friction, restitution

	MeowMix *meowMix = dynamic_cast<MeowMix *>(m_gameFactory->makeObject(GameFactory::OBJECT_MEOW_MIX, NULL, NULL, NULL));
	m_humanPlayers[0]->setCar(meowMix);

	MeowMix *meowMixAi = dynamic_cast<MeowMix *>(m_gameFactory->makeObject(GameFactory::OBJECT_MEOW_MIX, new PxTransform(-15, 0, -15), NULL, NULL));

	float length = 50;
	float width = 10;

	float dims = 200;

	//Create the drivable geometry
	m_gameFactory->makeObject(GameFactory::OBJECT_PLANE, new PxTransform(PxVec3(0, 0, 0)), new PxBoxGeometry(width, 0.5, length), NULL);
	m_gameFactory->makeObject(GameFactory::OBJECT_PLANE, new PxTransform(PxVec3(0, -100, 0)), new PxBoxGeometry(dims, 0.5, dims), NULL);

	// Create the collidable walls
	/*PxRigidStatic * leftWall = PhysicsManager::getPhysicsInstance().createRigidStatic(PxTransform(width, width, 0));
	leftWall->createShape(PxBoxGeometry(0.5, width, length), *mMaterial);
	m_scene->addActor(*leftWall);
	PxRigidStatic * rightWall = PhysicsManager::getPhysicsInstance().createRigidStatic(PxTransform(-width, width, 0));
	rightWall->createShape(PxBoxGeometry(.5, width, length), *mMaterial);
	m_scene->addActor(*rightWall);
	PxRigidStatic * frontWall = PhysicsManager::getPhysicsInstance().createRigidStatic(PxTransform(0, width, length));
	frontWall->createShape(PxBoxGeometry(width, width, 0.5), *mMaterial);
	m_scene->addActor(*frontWall);

	
	RenderableObject * FrontPlane = new RenderableObject();
	FrontPlane->setModel(Assets::getModel("plane"), true, true);
	FrontPlane->updateScale(glm::vec3(glm::vec3(frontWall->getWorldBounds().getDimensions().x, 1, frontWall->getWorldBounds().getDimensions().y)));
	FrontPlane->setActor(frontWall);
	FrontPlane->updateRotation(glm::vec3(3.14 / 2, 0, 0));
	m_world->addGameObject(FrontPlane);

	RenderableObject * leftPlane = new RenderableObject();
	leftPlane->setModel(Assets::getModel("plane"));
	leftPlane->setActor(leftWall);
	leftPlane->updatePosition(glm::vec3(leftPlane->getPosition().x, leftPlane->getPosition().y, leftPlane->getPosition().z));
	leftPlane->updateRotation(glm::vec3(0, 0, 3.14 / 2));
	m_world->addGameObject(leftPlane);

	RenderableObject * RightPlane = new RenderableObject();
	RightPlane->setModel(Assets::getModel("plane"));
	RightPlane->setActor(rightWall);
	RightPlane->updateRotation(glm::vec3(0, 0, 3.14 / 2));
	m_world->addGameObject(RightPlane);
	*/


	//drawthe finish line
	/*RenderableObject * finishLine = new RenderableObject();
	finishLine->setModel(Assets::getModel("finishLine"));
	m_world->addGameObject(finishLine);*/

	//create a bounding box for storm tropper to run into
	/*PxRigidStatic *boundVolume = PhysicsManager::getPhysicsInstance().createRigidStatic(PxTransform(0, 0, length - 5));
	PxShape* aSphereShape = boundVolume->createShape(PxBoxGeometry(PxVec3(2, 5, 3)), *mMaterial);
	aSphereShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	aSphereShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	//m_scene->addActor(*boundVolume);
	finishLine->setActor(boundVolume);
	PhysicsManager::setupFiltering(boundVolume,
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
	positions.push_back(glm::vec3(0, 0, 20));*/
	
}

