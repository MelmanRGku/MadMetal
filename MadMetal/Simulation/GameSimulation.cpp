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
#include "Game Logic\PositionManager.h"
#include "Global\Definitions.h"
#include "Objects\UIScoreTable.h"
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


#define NUM_OF_PLAYERS 12
#define NUM_LAPS_FOR_VICTORY 1
#define RACE_FINISH_DELAY 10

using namespace std;
bool gIsVehicleInAir = true;
static const float TRACK_DIMENSIONS = 200;

bool temporary = false;

GameSimulation::GameSimulation(vector<ControllableTemplate *> playerTemplates, Audio& audioHandle) : m_audioHandle(audioHandle)
{
	std::cout << "GameSimulation pushed onto the stack \n";
	newMessage.setTag(SceneMessage::eNone);
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

	std::vector<PxTransform *> spawnLocations;
	spawnLocations.push_back(new PxTransform(-15, 1, 0));
	spawnLocations.push_back(new PxTransform(0, 1, 0));
	spawnLocations.push_back(new PxTransform(-15, 1, -15));
	spawnLocations.push_back(new PxTransform(0, 1, -15));
	spawnLocations.push_back(new PxTransform(-15, 1, -30));
	spawnLocations.push_back(new PxTransform(0, 1, -30));
	spawnLocations.push_back(new PxTransform(-15, 1, -45));
	spawnLocations.push_back(new PxTransform(0, 1, -45));
	//create characters for game from templates
	for (unsigned int i = 0; i < playerTemplates.size(); i++)
	{
		if (playerTemplates[i]->getGamePad() != NULL) //if a game pad is assigned, it is a human player
		{
			PlayerControllable * humanPlayer = new PlayerControllable(*playerTemplates[i]);
			PxTransform *pos = spawnLocations.at(i);
			Car *car = NULL;
			if (playerTemplates[i]->getCarSelection() == Characters::CHARACTER_MEOW_MIX) {
				car = static_cast<MeowMix *>(m_gameFactory->makeObject(GameFactory::OBJECT_MEOW_MIX, pos, NULL, NULL));
			}
			else if (playerTemplates[i]->getCarSelection() == Characters::CHARACTER_EXPLOSIVELY_DELICIOUS) {
				car = static_cast<ExplosivelyDelicious *>(m_gameFactory->makeObject(GameFactory::OBJECT_EXPLOSIVELY_DELICIOUS, pos, NULL, NULL));
			}
			else if (playerTemplates[i]->getCarSelection() == Characters::CHARACTER_GARGANTULOUS) {
				car = static_cast<ExplosivelyDelicious *>(m_gameFactory->makeObject(GameFactory::OBJECT_GARGANTULOUS, pos, NULL, NULL));
			} 
			humanPlayer->setCar(car);

			UI *ui = dynamic_cast<UI *>(m_gameFactory->makeObject(GameFactory::OBJECT_UI, NULL, NULL, NULL));
			humanPlayer->getCar()->ui = ui;
			ui->map->setMainPlayer(humanPlayer);
			//m_world->addGameObject(ui);
			//todo: make a car for player based off template
			m_humanPlayers.push_back(humanPlayer);
			
			m_players.push_back(humanPlayer);

			//pass players camera to scene cameras
			m_sceneCameras.push_back(humanPlayer->getCamera());

		}
		else {
			AIControllable *ai = new AIControllable(*playerTemplates[i], *m_track);
			PxTransform *pos = spawnLocations.at(i);
			Car *car = NULL;
			if (playerTemplates[i]->getCarSelection() == Characters::CHARACTER_MEOW_MIX) {
				car = static_cast<MeowMix *>(m_gameFactory->makeObject(GameFactory::OBJECT_MEOW_MIX, pos, NULL, NULL));
			}
			else if (playerTemplates[i]->getCarSelection() == Characters::CHARACTER_EXPLOSIVELY_DELICIOUS) {
				car = static_cast<ExplosivelyDelicious *>(m_gameFactory->makeObject(GameFactory::OBJECT_EXPLOSIVELY_DELICIOUS, pos, NULL, NULL));
			}
			else if (playerTemplates[i]->getCarSelection() == Characters::CHARACTER_GARGANTULOUS) {
				car = static_cast<ExplosivelyDelicious *>(m_gameFactory->makeObject(GameFactory::OBJECT_GARGANTULOUS, pos, NULL, NULL));
			}
			ai->setCar(car);
			m_aiPlayers.push_back(ai);
			m_players.push_back(ai);
			//make a car for ai based off template
		}
	}

	//delete all spawn locations
	for (unsigned int i = 0; i < spawnLocations.size(); i++) {
		delete spawnLocations.at(i);
	}

	//adjust strings
	for (unsigned int i = 0; i < m_humanPlayers.size(); i++) {
		m_humanPlayers.at(i)->getCar()->getUI()->adjustStringsForViewport(i + 1, m_humanPlayers.size());
	}

	//if there is only one player, set audio to do sound attenuation to that player
	//if (m_humanPlayers.size() == 1)
	//{
		m_audioHandle.assignListener(m_humanPlayers[0]->getCar());
	//}
	
	//m_mainCamera = m_humanPlayers[0]->getCamera();
	
	initialize();
	m_scoreTable = new ScoreTable(m_players);

	PxVec3 minTrackBounds = m_track->getDrivablePart()->getActor().getWorldBounds().minimum;
	PxVec3 maxTrackBounds = m_track->getDrivablePart()->getActor().getWorldBounds().maximum;
	glm::vec3 minBounds = glm::vec3(minTrackBounds.x, minTrackBounds.y, minTrackBounds.z);
	glm::vec3 maxBounds = glm::vec3(maxTrackBounds.x, maxTrackBounds.y, maxTrackBounds.z);
	for (unsigned int i = 0; i < m_humanPlayers.size(); i++) {
		m_humanPlayers.at(i)->getCar()->getUI()->map->setTrackBounds(minBounds, maxBounds);
		m_humanPlayers.at(i)->getCar()->getUI()->map->setPlayers(&m_players);
		m_humanPlayers.at(i)->getCar()->getUI()->scoreTable->setScoreTable(m_scoreTable);
		std::stringstream ss;
		ss << "Player " << (i + 1);
		m_humanPlayers.at(i)->getCar()->getUI()->scoreTable->setOwnerName(ss.str());
	}
	

	m_positionManager = new PositionManager(m_players);
	audioHandle.queAudioSource(m_humanPlayers[0]->getCar()->getCar().getRigidDynamicActor(), StartBeepSound());
	pauseControls(true);

}

GameSimulation::~GameSimulation()
{
	delete m_positionManager;
	delete m_scoreTable;
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
	int numSteps = 1;
	while (dt > 1.f / 50.f) {
		dt /= 2.f;
		numSteps *= 2;
	}
	for (int i = 0; i < numSteps; i++) {

	for (unsigned int i = 0; i < m_players.size(); i++)
	{
		//This updates the ditance that the player has traveled. This is later used by the renderer ro render the tires.
		m_players[i]->getCar()->distanceTraveled += m_players[i]->getCar()->getCar().computeForwardSpeed() * dt;

		//Raycasts.

		PxVehicleWheels* vehicles[1] = { &m_players[i]->getCar()->getCar() };
		PxRaycastQueryResult* raycastResults = gVehicleSceneQueryData->getRaycastQueryResultBuffer(0);
		const PxU32 raycastResultsSize = gVehicleSceneQueryData->getRaycastQueryResultBufferSize();
		PxVehicleSuspensionRaycasts(gBatchQuery, 1, vehicles, raycastResultsSize, raycastResults);

		//Vehicle update.
		const PxVec3 grav = m_scene->getGravity();
		PxWheelQueryResult wheelQueryResults[PX_MAX_NB_WHEELS];
		PxVehicleWheelQueryResult vehicleQueryResults[1] = { { wheelQueryResults, m_players[i]->getCar()->getCar().mWheelsSimData.getNbWheels() } };
			PxVehicleUpdates(dt, grav, *gFrictionPairs, 1, vehicles, vehicleQueryResults);

		//Work out if the vehicle is in the air.
		gIsVehicleInAir = m_players[i]->getCar()->getCar().getRigidDynamicActor()->isSleeping() ? false : PxVehicleIsInAir(vehicleQueryResults[0]);


		PxShape *tempBuffer[PX_MAX_NB_WHEELS + 1];
		m_players[i]->getCar()->getCar().getRigidDynamicActor()->getShapes(tempBuffer, m_players[i]->getCar()->getCar().getRigidDynamicActor()->getNbShapes());

		PxVec3 test = m_players[i]->getCar()->getCar().getRigidDynamicActor()->getGlobalPose().q.getBasisVector1();

		if (test.y < 0.9 && gIsVehicleInAir)
		{
			//cout << "PITCH ME" << endl;
			m_players[i]->getCar()->getCar().getRigidDynamicActor()->setAngularVelocity(m_players[i]->getCar()->getCar().getRigidDynamicActor()->getAngularVelocity() + PxVec3(-0.01, 0, 0));

		}
	}

	m_scene->simulate(dt);
	m_scene->fetchResults(true);
	

}
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

}

void GameSimulation::updateObjects(double dt) {

	m_world->update(dt);
	m_displayMessage->update(dt);
	m_scoreTable->updateTable();

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
		}
	}

	if (m_humanPlayers[0]->getGamePad() != NULL && (m_humanPlayers[0]->getGamePad()->isPressed(GamePad::DPadLeft) || m_humanPlayers[0]->getGamePad()->isPressed(GamePad::DPadRight))) {
		musicManager->changeSong();
	}
}

bool GameSimulation::simulateScene(double dt, SceneMessage &message)
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
		std::vector<ControllableTemplate *> playerTemplates;

		//put the controllables into the vector incase the player trys to restart
		for (int i = 0; i < m_players.size(); i++)
		{
			playerTemplates.push_back(&m_players[i]->getControllableTemplate());
		}

		for (int i = 0; i < playerTemplates.size(); i++) {
			playerTemplates.at(i)->setPlayerNumber(i+1);
			playerTemplates.at(i)->setFinalPosition(m_players.at(i)->getCar()->getPositionInRace());
			playerTemplates.at(i)->setFinalScore(m_players.at(i)->getCar()->tallyScore());
		}
		message.setTag(SceneMessage::eEnd);
		message.setPlayerTemplates(playerTemplates);
		return true;
		
	}
	simulatePhysics(dt);
	simulateAnimation();
	updateObjects(dt);

	if (newMessage.getTag() != SceneMessage::eNone) {
		message.setTag(newMessage.getTag());
		message.setPlayerTemplates(newMessage.getPlayerTemplates());
		newMessage.setTag(SceneMessage::eNone);
		return true;
	}

	m_positionManager->updatePlayerPositions();

	//std::cout << "player position in race: " << m_players[0]->getCar()->getPositionInRace() << "\n";
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

void GameSimulation::setupPowerups() {
	//initial 3 powerups are fixed and all have shield setup in the beginning
	PxTransform * pos;
	PxGeometry **powerGeom = new PxGeometry*[1];
	powerGeom[0] = new PxBoxGeometry(PxVec3(3, 3, 1));

	pos = new PxTransform(0, 5, 20);
	PowerUp * powerup = static_cast<PowerUp *>(m_gameFactory->makeObject(GameFactory::OBJECT_POWERUP, pos, powerGeom, NULL));
	powerup->setActiveType(2);
	delete pos;

	pos = new PxTransform(-10, 5, 20);
	powerup = static_cast<PowerUp *>(m_gameFactory->makeObject(GameFactory::OBJECT_POWERUP, pos, powerGeom, NULL));
	powerup->setActiveType(2);
	delete pos;

	pos = new PxTransform(10, 5, 20);
	powerup = static_cast<PowerUp *>(m_gameFactory->makeObject(GameFactory::OBJECT_POWERUP, pos, powerGeom, NULL));
	powerup->setActiveType(2);
	delete pos;


	//now setup all other powerup locations
	std::vector<PxTransform *> powerupLocations;
	//sand
	powerupLocations.push_back(new PxTransform(61, 5, 494));
	powerupLocations.push_back(new PxTransform(86, 5, 504));
	powerupLocations.push_back(new PxTransform(111, 5, 514));

	//caves
	powerupLocations.push_back(new PxTransform(-34, 5, 1406));
	powerupLocations.push_back(new PxTransform(1, 5, 1410));
	powerupLocations.push_back(new PxTransform(36, 5, 1415));

	//first tunnel
	powerupLocations.push_back(new PxTransform(-454, 5, 841));
	powerupLocations.push_back(new PxTransform(-452, 5, 635));

	//second tunnel
	powerupLocations.push_back(new PxTransform(-589, 5, -19));

	//before finish line
	powerupLocations.push_back(new PxTransform(-279, 5, -201));
	powerupLocations.push_back(new PxTransform(-279, 5, -160));

	srand(time(NULL));
	for (PxTransform *t : powerupLocations) {
		powerup = static_cast<PowerUp *>(m_gameFactory->makeObject(GameFactory::OBJECT_POWERUP, t, powerGeom, NULL));
		powerup->setActiveType(rand() % 3 + 1);
		delete t;
	}
	delete powerGeom[0];
	delete[] powerGeom;
}

void GameSimulation::setupBasicGameWorldObjects() {
	setupPowerups();

	//trainCar test
	PxGeometry **trainGeom = new PxGeometry*[1];
	trainGeom[0] = new PxBoxGeometry(PxVec3(6,5,50));
	PxTransform *pos = new PxTransform(-450, 0, 360);
	m_gameFactory->makeObject(GameFactory::OBJECT_TRAIN_CAR, pos, trainGeom, NULL);
	delete trainGeom[0];
	delete[] trainGeom;
	delete pos;

	trainGeom = new PxGeometry*[1];
	trainGeom[0] = new PxBoxGeometry(PxVec3(6, 5, 50));
	pos = new PxTransform(-579, 0, -260.85);
	m_gameFactory->makeObject(GameFactory::OBJECT_TRAIN_CAR, pos, trainGeom, NULL);
	delete pos;
	delete trainGeom[0];
	delete[] trainGeom;

	//death pit
	PxGeometry **deathPitGeom = new PxGeometry*[1];
	deathPitGeom[0] = new PxBoxGeometry(PxVec3(250, 5, 50));
	pos = new PxTransform(-275, -40, 1500);
	m_gameFactory->makeObject(GameFactory::OBJECT_DEATH_PIT, pos, deathPitGeom, NULL);
	delete pos;
	delete deathPitGeom[0];
	delete[] deathPitGeom;

	//PxGeometry **geom1 = new PxGeometry *[1];
	//PxGeometry **geom2 = new PxGeometry *[1];
	//geom1[0] = new PxBoxGeometry(PxVec3(60, m_track->getDrivablePart()->getWorldBounds().maximum.y, 30));
	//geom2[0] = new PxBoxGeometry(PxVec3(40, m_track->getDrivablePart()->getWorldBounds().maximum.y, 60));
	//
	//pos = new PxTransform(m_track->getWaypointAt(13)->getGlobalPose().x, m_track->getWaypointAt(95)->getGlobalPose().y, m_track->getWaypointAt(13)->getGlobalPose().z);
	//m_gameFactory->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL);
	//delete pos;
	//pos = new PxTransform(m_track->getWaypointAt(72)->getGlobalPose().x, m_track->getWaypointAt(73)->getGlobalPose().y, m_track->getWaypointAt(72)->getGlobalPose().z);
	//m_gameFactory->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom2 , NULL);


	//delete pos;
	//delete geom1[0];
	//delete geom2[0];
	//delete[] geom1;
	//delete[] geom2;
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

