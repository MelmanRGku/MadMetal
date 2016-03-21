#include "GameSimulation.h"
#include "GameSimulationDefinitions.h"
#include "Objects/Cars/MeowMix.h"
#include "Objects/Model.h"
#include "Objects/ObjectLoaders/ObjModelLoader.h"
#include "PhysicsManager.h"
#include "Objects\ObjectCreators\VehicleCreator.h"
#include "Objects\Waypoint.h"
#include "Game Logic\WayPointSystem.h"
#include "Objects\TestObject.h"
#include "Objects\CollisionVolume.h"
#include "Objects\PowerUp.h"
#include "ParticleSystem\ParticleSystem.h"
#include <sstream>


#define NUM_OF_PLAYERS 8
#define NUM_LAPS_FOR_VICTORY 1
#define RACE_FINISH_DELAY 10

using namespace std;
bool gIsVehicleInAir = true;
static const float TRACK_DIMENSIONS = 200;

bool temporary = false;

GameSimulation::GameSimulation(vector<ControllableTemplate *> playerTemplates, Audio& audioHandle) : m_audioHandle(audioHandle)
{
	std::cout << "GameSimulation pushed onto the stack \n";
	
	createPhysicsScene();
	musicManager = new MusicManager(audioHandle);
	m_gameFactory = GameFactory::instance(*m_world, *m_scene, audioHandle);
	m_displayMessage = static_cast<DisplayMessage *>(m_gameFactory->makeObject(GameFactory::OBJECT_DISPLAY_MESSAGE, NULL, NULL, NULL));

	PxTransform *pos = new PxTransform(PxVec3(0, 0, 0));
	m_track = static_cast<Track *>(m_gameFactory->makeObject(GameFactory::OBJECT_TRACK, pos, NULL, NULL));
	delete pos;

	m_isPaused = false;
	m_numLapsVictory = NUM_LAPS_FOR_VICTORY;


	PxMaterial* mMaterial;
	mMaterial = PhysicsManager::getPhysicsInstance().createMaterial(0, 0, 0.1f);    //static friction, dynamic friction, restitution
	//create characters for game from templates
	for (int i = 0; i < playerTemplates.size(); i++)
	{
		if (playerTemplates[i]->getGamePad() != NULL) //if a game pad is assigned, it is a human player
		{
			PlayerControllable * humanPlayer = new PlayerControllable(*playerTemplates[i]);
			PxTransform *pos = new PxTransform(-130 + i * 10, 40, 0);
			MeowMix *car = static_cast<MeowMix *>(m_gameFactory->makeObject(GameFactory::OBJECT_MEOW_MIX, pos, NULL, NULL));
			humanPlayer->setCar(car);
			delete pos;

			UI *ui = dynamic_cast<UI *>(m_gameFactory->makeObject(GameFactory::OBJECT_UI, NULL, NULL, NULL));
			humanPlayer->getCar()->ui = ui;
			ui->map->setMainPlayer(humanPlayer);
			m_world->addGameObject(ui);
			//todo: make a car for player based off template
			m_humanPlayers.push_back(humanPlayer);
			
			m_players.push_back(humanPlayer);

			//pass players camera to scene cameras
			m_sceneCameras.push_back(humanPlayer->getCamera());

		}
		else {
			AIControllable *ai = new AIControllable(*playerTemplates[i], *m_track);
			PxTransform *pos = new PxTransform(-130 + i * 10, 40, 0);
			ai->setCar(dynamic_cast<MeowMix *>(m_gameFactory->makeObject(GameFactory::OBJECT_MEOW_MIX, pos, NULL, NULL)));
			delete pos;
			m_aiPlayers.push_back(ai);
			m_players.push_back(ai);
			//make a car for ai based off template
		}
	}

	//if there is only one player, set audio to do sound attenuation to that player
	if (m_humanPlayers.size() == 1)
	{
		m_audioHandle.assignListener(m_humanPlayers[0]->getCar());
	}
	
	//m_mainCamera = m_humanPlayers[0]->getCamera();
	
	initialize();

	PxVec3 minTrackBounds = m_track->getDrivablePart()->getActor().getWorldBounds().minimum;
	PxVec3 maxTrackBounds = m_track->getDrivablePart()->getActor().getWorldBounds().maximum;
	glm::vec3 minBounds = glm::vec3(minTrackBounds.x, minTrackBounds.y, minTrackBounds.z);
	glm::vec3 maxBounds = glm::vec3(maxTrackBounds.x, maxTrackBounds.y, maxTrackBounds.z);
	for (unsigned int i = 0; i < m_humanPlayers.size(); i++) {
		m_humanPlayers.at(i)->getCar()->getUI()->map->setTrackBounds(minBounds, maxBounds);
		m_humanPlayers.at(i)->getCar()->getUI()->map->setPlayers(&m_players);
	}
	

	
	audioHandle.queAudioSource(m_humanPlayers[0]->getCar()->getCar().getRigidDynamicActor(), StartBeepSound());
	pauseControls(true);

}

GameSimulation::~GameSimulation()
{
	PhysicsManager::getCpuDispatcher().release();
	m_scene->release();
	delete m_track;
	for (int i = 0; i < m_players.size(); i++)
	{
		delete m_players[i];
	}
	delete m_displayMessage;
	gVehicleSceneQueryData->free(*PhysicsManager::getAllocator());
	gFrictionPairs->release();
	GameFactory::release();
	delete manager;
	delete musicManager;
	
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

	for (unsigned int i = 0; i < m_players.size(); i++)
	{

	//Raycasts.
	
		PxVehicleWheels* vehicles[1] = { &m_players[i]->getCar()->getCar() };
	PxRaycastQueryResult* raycastResults = gVehicleSceneQueryData->getRaycastQueryResultBuffer(0);
	const PxU32 raycastResultsSize = gVehicleSceneQueryData->getRaycastQueryResultBufferSize();
	PxVehicleSuspensionRaycasts(gBatchQuery, 1, vehicles, raycastResultsSize, raycastResults);

	//Vehicle update.
	const PxVec3 grav = m_scene->getGravity();
	PxWheelQueryResult wheelQueryResults[PX_MAX_NB_WHEELS];
		PxVehicleWheelQueryResult vehicleQueryResults[1] = { { wheelQueryResults, m_players[i]->getCar()->getCar().mWheelsSimData.getNbWheels() } };
	PxVehicleUpdates(timestep, grav, *gFrictionPairs, 1, vehicles, vehicleQueryResults);

	//Work out if the vehicle is in the air.
		gIsVehicleInAir = m_players[i]->getCar()->getCar().getRigidDynamicActor()->isSleeping() ? false : PxVehicleIsInAir(vehicleQueryResults[0]);

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
		m_players[i]->getCar()->getCar().getRigidDynamicActor()->getShapes(tempBuffer, m_players[i]->getCar()->getCar().getRigidDynamicActor()->getNbShapes());

		PxVec3 test = m_players[i]->getCar()->getCar().getRigidDynamicActor()->getGlobalPose().q.getBasisVector1();

	if (test.y < 0.9 && gIsVehicleInAir)
	{
			//cout << "PITCH ME" << endl;
			m_players[i]->getCar()->getCar().getRigidDynamicActor()->setAngularVelocity(m_players[i]->getCar()->getCar().getRigidDynamicActor()->getAngularVelocity() + PxVec3(-0.01, 0, 0));

	}

//	cout << test.x << " " << test.y << " " << test.z << endl;
	}

	

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

	for (unsigned int i = 0; i < m_aiPlayers.size(); i++) {
		m_aiPlayers[i]->processFire(&m_players);
	}

	//m_humanPlayers[0]->playFrame(dt);
	//m_players[1]->playFrame(dt);
	
}

void GameSimulation::updateObjects(double dt) {

	m_world->update(dt);
	m_displayMessage->update(dt);

	}

void GameSimulation::initialize() {
	setupBasicGameWorldObjects();
}

void GameSimulation::createPhysicsScene()
{
	PxSceneDesc sceneDesc(PhysicsManager::getScale());
	sceneDesc.gravity = PxVec3(0.0f, -18.0f, 0.0f);

	manager = new CollisionManager(*m_world);
	sceneDesc.simulationEventCallback = manager;
	sceneDesc.filterCallback = manager;
	sceneDesc.cpuDispatcher = &PhysicsManager::getCpuDispatcher();

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

void GameSimulation::processInput() {
	//check for pause button
	for (int i = 0; i < m_humanPlayers.size(); i++)
	{
		//if (m_humanPlayers[i]->getGamePad() != NULL && m_humanPlayers[i]->getGamePad()->isPressed(GamePad::StartButton))
		//{
		//	newMessage.setTag(SceneMessage::ePause);
		//	std::vector<ControllableTemplate *> playerTemplates;
		//	//put the controllables into the vector incase the player trys to restart
		//	for (int i = 0; i < m_players.size(); i++)
		//	{
		//		playerTemplates.push_back(&m_players[i]->getControllableTemplate());
		//	}
		//	//put a dummy controllable at the front of the vector so the pause screen knows who paused
		//	playerTemplates.push_back(new ControllableTemplate(m_humanPlayers[i]->getGamePad()));
		//	newMessage.setPlayerTemplates(playerTemplates);
		//	
		//	return true;
		//}
	}

	if (m_humanPlayers[0]->getGamePad() != NULL && (m_humanPlayers[0]->getGamePad()->isPressed(GamePad::DPadLeft) || m_humanPlayers[0]->getGamePad()->isPressed(GamePad::DPadRight))) {
		musicManager->changeSong();
	}
}

bool GameSimulation::simulateScene(double dt, SceneMessage &newMessage)
{
	processInput();
	musicManager->update();
	m_sceneGameTimeSeconds += dt;
	if (m_sceneGameTimeSeconds > 3 && m_controlsPaused) {
		pauseControls(false);
	}
	if (m_sceneGameTimeSeconds < 4 )
	{
		switch ((int)m_sceneGameTimeSeconds){
		case(0) :
			m_displayMessage->initializeMessage("3", 0.5);
			break;
		case(1) :
			m_displayMessage->initializeMessage("2", 0.5);
			break;
		case(2) :
			m_displayMessage->initializeMessage("1", 0.5);
			break;
		case(3) :
			m_displayMessage->initializeMessage("GO!!", 0.5);
			break;
		default:
			break;
		}
	}


	if (!m_raceFinished)
	{
		//check for lap status
		for (int i = 0; i < m_players.size(); i++)
		{
			if (m_players[i]->getCar()->getLap() == m_numLapsVictory)
			{
				if (!m_raceFinishedCountdownSeconds)
				{
					if (i != 0)
						m_displayMessage->initializeMessage("You Better Hurry...", 2);
					else 
						m_displayMessage->initializeMessage("First Across... Like a Boss", 2);
					m_raceFinishedCountdownSeconds = RACE_FINISH_DELAY; //start count down
				}
				else if (RACE_FINISH_DELAY - m_raceFinishedCountdownSeconds >= 2)
				{
					m_displayMessage->initializeMessage(std::to_string((int)m_raceFinishedCountdownSeconds), 1);
				}
				if (!m_players[i]->getCar()->isFinishedRace())
				{
					m_players[i]->getCar()->setFinishedRace(true);
				m_players[i]->getCar()->addToScore(getFinishLineBonus(m_numPlayersFinishedRace++));
					
				}
				
			}
		}

		if (m_raceFinishedCountdownSeconds) {
			//have all players crossed the finish line or count down done?
			if (m_numPlayersFinishedRace == m_players.size() || (m_raceFinishedCountdownSeconds -= dt) <= 0)
			{
				m_raceFinished = true;
				//m_displayMessage->initializeMessage("FINISHED", 3);
			}
		}
	}
	
	//if the race is still going, do player simulations
	if (!m_raceFinished)
	{
		
		//simulate players
	
	simulatePlayers(dt);
	}
	else {
		int player = getFirstPlace();
		int score = m_players[player]->getCar()->tallyScore();
		std::stringstream s;
		s << "Player " << player + 1 << " Wins with " << score << "Points!!!";
		m_displayMessage->setFontSize(45);
		m_displayMessage->initializeMessage(s.str(), 10);
		
	}
	simulatePhysics(dt);
	simulateAnimation();
	updateObjects(dt);
	return false;
	
}

void GameSimulation::pauseControls(bool pause) {
	for (unsigned int i = 0; i < m_players.size(); i++) {
		m_players[i]->pauseControls(pause);
	}
	m_controlsPaused = pause;
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
	//Power up test
	PxTransform * pos;
	PxGeometry **powerGeom = new PxGeometry*[1];
	powerGeom[0] = new PxBoxGeometry(PxVec3(1, 5, 1));
	pos = new PxTransform(-130, 25, 20);
	//m_gameFactory->makeObject(GameFactory::OBJECT_POWERUP, pos, powerGeom, NULL);
	delete pos;

	//explosion test
	PxGeometry **explosionGeom = new PxGeometry*[1];
	explosionGeom[0] = new PxSphereGeometry(1);
	pos = new PxTransform(-130, 25, 20);
	//m_gameFactory->makeObject(GameFactory::OBJECT_EXPLOSION_1, pos, explosionGeom, NULL);
	delete pos;

	PxGeometry **geom1 = new PxGeometry *[1];
	PxGeometry **geom2 = new PxGeometry *[1];
	geom1[0] = new PxBoxGeometry(PxVec3(60, m_track->getDrivablePart()->getWorldBounds().maximum.y, 30));
	geom2[0] = new PxBoxGeometry(PxVec3(40, m_track->getDrivablePart()->getWorldBounds().maximum.y, 60));
	
	pos = new PxTransform(m_track->getWaypointAt(13)->getGlobalPose().x, m_track->getWaypointAt(13)->getGlobalPose().y, m_track->getWaypointAt(13)->getGlobalPose().z);
	m_gameFactory->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL);
	delete pos;
	pos = new PxTransform(m_track->getWaypointAt(72)->getGlobalPose().x, m_track->getWaypointAt(72)->getGlobalPose().y, m_track->getWaypointAt(72)->getGlobalPose().z);
	m_gameFactory->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom2 , NULL);


	delete pos;
	delete geom1[0];
	delete geom2[0];
	delete[] geom1;
	delete[] geom2;
}

float GameSimulation::getFinishLineBonus(int position)
{
	switch (position)
	{
	case (0) :
		return 500;
	case (1) :
		return 250;
	case(2) :
		return 100;
	default:
		return 0;
	}

	}
	
int GameSimulation::getFirstPlace()
{
	int tempPlayer = -1;
	int tempScore = 0;
	for (int i = 0; i < m_players.size(); i++)
	{
		
		if (m_players[i]->getCar()->tallyScore() > tempScore)
		{
			tempPlayer = i;
			tempScore = m_players[i]->getCar()->tallyScore();
		}
	}
	return tempPlayer;
	

}

