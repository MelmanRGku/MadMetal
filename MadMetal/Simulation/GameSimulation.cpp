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
#include "Objects\DeathPit.h"
#include "Objects\GooMonster.h"
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


#define NUM_OF_PLAYERS 12
#define NUM_LAPS_FOR_VICTORY 3
#define RACE_FINISH_DELAY 30

using namespace std;

GameSimulation::GameSimulation(vector<ControllableTemplate *> playerTemplates, Audio& audioHandle) : m_audioHandle(audioHandle)
{
	Waypoint::resetGlobalId();
	Waypoint::resetGlobalId();
	Car::resetGlobalPositionID();
	newMessage.setTag(SceneMessage::eNone);
	createPhysicsScene();
	musicManager = new MusicManager(audioHandle);
	m_gameFactory = GameFactory::instance(*m_world, *m_scene, audioHandle);
	GameFactory::resetId();
	PxTransform *pos = new PxTransform(PxVec3(0, 0, 0));
	m_track = static_cast<Track *>(m_gameFactory->makeObject(GameFactory::OBJECT_TRACK, pos, NULL, NULL));
	delete pos;

	m_isPaused = false;
	m_numLapsVictory = NUM_LAPS_FOR_VICTORY;
	audioHandle.resetMusicVolume();


	PxMaterial* mMaterial;
	mMaterial = PhysicsManager::createMaterial(0, 0, 0.1f);    //static friction, dynamic friction, restitution

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
			m_audioHandle.assignListener(car);

			UI *ui = dynamic_cast<UI *>(m_gameFactory->makeObject(GameFactory::OBJECT_UI, NULL, NULL, NULL));
			humanPlayer->getCar()->ui = ui;
			ui->map->setMainPlayer(humanPlayer);
			m_humanPlayers.push_back(humanPlayer);
			
			m_players.push_back(humanPlayer);

			//pass players camera to scene cameras
			m_sceneCameras.push_back(humanPlayer->getCamera());

		}
		else {
			AIControllable *ai = new AIControllable(*playerTemplates[i]);
			PxTransform *pos = spawnLocations.at(i);
			Car *car = NULL;
			/*if (playerTemplates[i]->getCarSelection() == Characters::CHARACTER_MEOW_MIX) {
				car = static_cast<MeowMix *>(m_gameFactory->makeObject(GameFactory::OBJECT_MEOW_MIX, pos, NULL, NULL));
			}
			else if (playerTemplates[i]->getCarSelection() == Characters::CHARACTER_EXPLOSIVELY_DELICIOUS) {
				car = static_cast<ExplosivelyDelicious *>(m_gameFactory->makeObject(GameFactory::OBJECT_EXPLOSIVELY_DELICIOUS, pos, NULL, NULL));
			}
			else if (playerTemplates[i]->getCarSelection() == Characters::CHARACTER_GARGANTULOUS) {
				car = static_cast<ExplosivelyDelicious *>(m_gameFactory->makeObject(GameFactory::OBJECT_GARGANTULOUS, pos, NULL, NULL));
			}*/
			car = static_cast<MeowMix *>(m_gameFactory->makeObject(GameFactory::OBJECT_MEOW_MIX, pos, NULL, NULL));
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
	setupSceneLights();
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
	gVehicleSceneQueryData->free(*PhysicsManager::getAllocator());
	gFrictionPairs->release();
	GameFactory::release();
	delete manager;
	delete musicManager;
}

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
	//std::cout << m_players[0]->getCar()->getGlobalPose().x << "    " << m_players[0]->getCar()->getGlobalPose().z << std::endl;
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
			m_players[i]->getCar()->setIsInAir(m_players[i]->getCar()->getCar().getRigidDynamicActor()->isSleeping() ? false : PxVehicleIsInAir(vehicleQueryResults[0]));
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
		m_aiPlayers[i]->processPowerups();
		m_aiPlayers[i]->processFire(&m_players);
	}

}

void GameSimulation::updateObjects(double dt) {

	m_world->update(dt);
	for (int i = 0; i < m_humanPlayers.size(); i++) {
		m_humanPlayers.at(i)->getCar()->getUI()->displayMessage->update(dt);
	}
	m_scoreTable->updateTable();

	}

void GameSimulation::initialize() {
	setupBasicGameWorldObjects();
}

void GameSimulation::createPhysicsScene()
{
	PxSceneDesc sceneDesc(PhysicsManager::getScale());
	sceneDesc.gravity = PxVec3(0.0f, -30.0f, 0.0f);

	manager = new CollisionManager(*m_world, m_audioHandle);
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
	mMaterial = PhysicsManager::createMaterial(0, 0, 0.1f);    //static friction, dynamic friction, restitution

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
		//no pausing in the first 3 seconds
		if (m_sceneGameTimeSeconds > 3 && m_humanPlayers[i]->getGamePad() != NULL && m_humanPlayers[i]->getGamePad()->isPressed(GamePad::StartButton))
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

		if (m_humanPlayers[i]->getGamePad() != NULL && (m_humanPlayers[i]->getGamePad()->isPressed(GamePad::DPadLeft) || m_humanPlayers[i]->getGamePad()->isPressed(GamePad::DPadRight))) {
		musicManager->changeSong();
	}
}
}

bool GameSimulation::simulateScene(double dt, SceneMessage &message)
{
	processInput();
	musicManager->update();
	m_sceneGameTimeSeconds += dt;
	if (m_sceneGameTimeSeconds > 3 && m_controlsPaused) {
		pauseControls(false);

		//make everyone invincible for 3 seconds
		for (int i = 0; i < m_players.size(); i++) {
			m_players.at(i)->getCar()->setInvincibility(2.5f);
	}
	}
	if (m_sceneGameTimeSeconds < 4 )
	{
		switch ((int)m_sceneGameTimeSeconds){
		case(0) :
		{
			for (int i = 0; i < m_humanPlayers.size(); i++) {
				m_humanPlayers.at(i)->getCar()->getUI()->displayMessage->initializeMessage("3", 0.5);
			}
			break;
		}
		case(1) :
		{
			for (int i = 0; i < m_humanPlayers.size(); i++) {
				m_humanPlayers.at(i)->getCar()->getUI()->displayMessage->initializeMessage("2", 0.5);
			}
			break;
		}
		case(2) :
		{
			for (int i = 0; i < m_humanPlayers.size(); i++) {
				m_humanPlayers.at(i)->getCar()->getUI()->displayMessage->initializeMessage("1", 0.5);
			}
			break;
		}
		case(3) :
		{
			for (int i = 0; i < m_humanPlayers.size(); i++) {
				m_humanPlayers.at(i)->getCar()->getUI()->displayMessage->initializeMessage("GO!", 0.5);
			}
			break;
		}
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
					for (int j = 0; j < m_humanPlayers.size(); j++) {
						if (m_players[i]->getCar() != m_humanPlayers[j]->getCar())
							m_humanPlayers.at(j)->getCar()->getUI()->displayMessage->initializeMessage("You have 30 seconds to finish!", 2);
					else 
							m_humanPlayers.at(j)->getCar()->getUI()->displayMessage->initializeMessage("First Across... Like a Boss", 2);
					}
					m_raceFinishedCountdownSeconds = RACE_FINISH_DELAY; //start count down
				}
				else if (RACE_FINISH_DELAY - m_raceFinishedCountdownSeconds >= 2)
				{
					for (int j = 0; j < m_humanPlayers.size(); j++) {
						if ((int)m_raceFinishedCountdownSeconds % 10 == 0 && (int)m_raceFinishedCountdownSeconds) {
							std::stringstream ss;
							ss << (int)m_raceFinishedCountdownSeconds << " seconds left!";
							m_humanPlayers.at(j)->getCar()->getUI()->displayMessage->initializeMessage(ss.str(), 1);
						}
						else if (m_raceFinishedCountdownSeconds <= 5) {
						m_humanPlayers.at(j)->getCar()->getUI()->displayMessage->initializeMessage(std::to_string((int)m_raceFinishedCountdownSeconds), 1);
					}
				}
				}
				if (!m_players[i]->getCar()->isFinishedRace())
				{
					m_players[i]->getCar()->setFinishedRace(true);
				m_players[i]->getCar()->addToScore(getFinishLineBonus(m_numPlayersFinishedRace++));
					
				}
				
			}
		}

		if (m_raceFinishedCountdownSeconds) {
			//have first 3 players crossed the finish line or count down done?
			if (m_numPlayersFinishedRace == m_players.size() || m_numPlayersFinishedRace == 3 || (m_raceFinishedCountdownSeconds -= dt) <= 0)
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
	powerGeom[0] = new PxBoxGeometry(PxVec3(4.5, 4.5, 1.5));

	pos = new PxTransform(-25, 6, 30);
	PowerUp * powerup = static_cast<PowerUp *>(m_gameFactory->makeObject(GameFactory::OBJECT_POWERUP, pos, powerGeom, NULL));
	powerup->setActiveType(2);
	delete pos;

	pos = new PxTransform(0, 6, 30);
	powerup = static_cast<PowerUp *>(m_gameFactory->makeObject(GameFactory::OBJECT_POWERUP, pos, powerGeom, NULL));
	powerup->setActiveType(2);
	delete pos;

	pos = new PxTransform(25, 6, 30);
	powerup = static_cast<PowerUp *>(m_gameFactory->makeObject(GameFactory::OBJECT_POWERUP, pos, powerGeom, NULL));
	powerup->setActiveType(2);
	delete pos;


	//now setup all other powerup locations
	std::vector<PxTransform *> powerupLocations;
	//sand
	powerupLocations.push_back(new PxTransform(-9, 6, 606));
	powerupLocations.push_back(new PxTransform(-40,31, 450));
	powerupLocations.push_back(new PxTransform(-8.75, 26, 1050));

	//caves
	powerupLocations.push_back(new PxTransform(14.5, 6, 1502.5));
	powerupLocations.push_back(new PxTransform(-19.375, 6, 1507.5));
	powerupLocations.push_back(new PxTransform(-250, 6, 1550));
	powerupLocations.push_back(new PxTransform(-600, 16, 1600));
	powerupLocations.push_back(new PxTransform(-650, 9, 1500));

	//first tunnel
	powerupLocations.push_back(new PxTransform(-960, -24, 1350));
	powerupLocations.push_back(new PxTransform(-964, -24, 950));

	//middle tunnel 
	powerupLocations.push_back(new PxTransform(-862, -24, 775));
	powerupLocations.push_back(new PxTransform(-862, -24, 745));

	//second tunnel
	powerupLocations.push_back(new PxTransform(-762, -24, 525));
	powerupLocations.push_back(new PxTransform(-762, -24, 394));

	//before circle
	//powerupLocations.push_back(new PxTransform(-543, 6, -87.5));
	//powerupLocations.push_back(new PxTransform(-543, 6, -122.5));

	//circle 
	powerupLocations.push_back(new PxTransform(-378, 6, 21.5));
	powerupLocations.push_back(new PxTransform(-378, 6, -231.5));

	//after circle
	//powerupLocations.push_back(new PxTransform(-210, 6, -87.5));
	//powerupLocations.push_back(new PxTransform(-219, 6, -122.5));

	srand(time(NULL));
	for (PxTransform *t : powerupLocations) {
		powerup = static_cast<PowerUp *>(m_gameFactory->makeObject(GameFactory::OBJECT_POWERUP, t, powerGeom, NULL));
		powerup->setActiveType(rand() % 3 + 1);
		delete t;
	}
	delete powerGeom[0];
	delete[] powerGeom;
}


void GameSimulation::setupTrains() {
	PxGeometry **trainGeom = new PxGeometry*[1];
	trainGeom[0] = new PxBoxGeometry(PxVec3(10, 10, 50));
	PxTransform *pos = new PxTransform(-960, -30, 665);
	static_cast<TrainCar*>(m_gameFactory->makeObject(GameFactory::OBJECT_TRAIN_CAR, pos, trainGeom, NULL))->setTravelDistance(1200);
	
	delete trainGeom[0];
	delete[] trainGeom;
	delete pos;

	trainGeom = new PxGeometry*[1];
	trainGeom[0] = new PxBoxGeometry(PxVec3(10, 10, 50));
	pos = new PxTransform(-765, -30, 125);
	m_gameFactory->makeObject(GameFactory::OBJECT_TRAIN_CAR, pos, trainGeom, NULL);
	delete pos;
	delete trainGeom[0];
	delete[] trainGeom;
}

void GameSimulation::setupDeathPit() {
	PxGeometry **deathPitGeom = new PxGeometry*[1];

	//first death pit
	deathPitGeom[0] = new PxBoxGeometry(PxVec3(35, 10, 45));
	PxTransform *pos = new PxTransform(15, -20, 445);
	DeathPit *pit = static_cast<DeathPit*>(m_gameFactory->makeObject(GameFactory::OBJECT_DEATH_PIT, pos, deathPitGeom, NULL));
	pit->setRespawnLocation(pos->p + PxVec3(0, 21, 465));
	pit->getRenderable()->setModel(NULL);

	//second death pit
	deathPitGeom[0] = new PxBoxGeometry(PxVec3(35, 10, 60));
	pos = new PxTransform(-25, -20, 765);
	pit = static_cast<DeathPit*>(m_gameFactory->makeObject(GameFactory::OBJECT_DEATH_PIT, pos, deathPitGeom, NULL));
	pit->setRespawnLocation(pos->p + PxVec3(0, 21, 465));
	pit->getRenderable()->setModel(NULL);

	//green death pit
	deathPitGeom[0] = new PxBoxGeometry(PxVec3(350, 5, 200));
	pos = new PxTransform(-713, -40, 1560);
	pit = static_cast<DeathPit*>(m_gameFactory->makeObject(GameFactory::OBJECT_DEATH_PIT, pos, deathPitGeom, NULL));
	pit->getRenderable()->setModel(NULL);

	//ramp at tunnel
	deathPitGeom[0] = new PxBoxGeometry(PxVec3(30, 5, 20));
	pos = new PxTransform(-730, -30, 180);
	pit = static_cast<DeathPit*>(m_gameFactory->makeObject(GameFactory::OBJECT_DEATH_PIT, pos, deathPitGeom, NULL));
	pit->getRenderable()->setModel(NULL);

	//death pit below the map
	deathPitGeom[0] = new PxBoxGeometry(PxVec3(5000, 10, 5000));
	pos = new PxTransform(0, -50, 0);
	pit = static_cast<DeathPit*>(m_gameFactory->makeObject(GameFactory::OBJECT_DEATH_PIT, pos, deathPitGeom, NULL));
	pit->getRenderable()->setModel(NULL);


	delete pos;
	delete deathPitGeom[0];
	delete[] deathPitGeom;

	PxGeometry ** gooMonsterGeom = new PxGeometry*[1];
	gooMonsterGeom[0] = new PxBoxGeometry(10,20,25);
	pos = new PxTransform(-700, -40, 1555);
	GooMonster * monster = static_cast<GooMonster *>(m_gameFactory->makeObject(GameFactory::OBJECT_GOO_MONSTER, pos, gooMonsterGeom, NULL));
	monster->setPlayers(m_players);
	monster->setSpawnVelocity(PxVec3(0, 55,-30));

	gooMonsterGeom[0] = new PxBoxGeometry(10, 20, 25);
	pos = new PxTransform(-600, -40, 1565);
	monster = static_cast<GooMonster *>(m_gameFactory->makeObject(GameFactory::OBJECT_GOO_MONSTER, pos, gooMonsterGeom, NULL));
	monster->setPlayers(m_players);
	monster->setSpawnVelocity(PxVec3(0, 55, 20));

	delete pos;
	delete gooMonsterGeom[0];
	delete[] gooMonsterGeom;
}

void GameSimulation::setupBasicGameWorldObjects() {
	setupPowerups();
	setupTrains();
	setupDeathPit();
	m_gameFactory->makeObject(GameFactory::OBJECT_SKY_BOX, NULL, NULL, NULL);
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


void GameSimulation::onPause() {
	m_audioHandle.clearListeners();
}

void GameSimulation::onResume() {
	for (PlayerControllable *p : m_humanPlayers) {
		m_audioHandle.assignListener(p->getCar());
	}
}
void GameSimulation::setupSceneLights() {
	//start line
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(5, 30, 35));
		firstLight->colour = glm::vec3(.7, .7, .7);
		firstLight->constant = 0.05;
		firstLight->linear = 0.01;
		firstLight->quad = 0.0;
		firstLight->cutoff = 100.0;
		m_world->addLightObject(firstLight);
	}


	//goo pit top (on ceiling)
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-587, 150, 1562));
		firstLight->colour = glm::vec3(1, 1, 1);
		firstLight->constant = 0.02;
		firstLight->linear = 0.03;
		firstLight->quad = 0;
		firstLight->cutoff = 200.0;
		m_world->addLightObject(firstLight);
	}

	//goo pit left (in death pit)
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-650, -50, 1663));
		firstLight->colour = glm::vec3(0, 1, 0);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0;
		firstLight->cutoff = 200.0;
		m_world->addLightObject(firstLight);
	}

	//goo pit left 2 (in death pit)
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-882, -50, 1712));
		firstLight->colour = glm::vec3(0, 1, 0);
		firstLight->constant = 0.02;
		firstLight->linear = 0.1;
		firstLight->quad = 0;
		firstLight->cutoff = 70.0;
		m_world->addLightObject(firstLight);
	}

	//goo pit right (in death pit)
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-740, -50, 1435));
		firstLight->colour = glm::vec3(0, 1, 0);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0;
		firstLight->cutoff = 200.0;
		m_world->addLightObject(firstLight);
	}

	//goo pit close to cave entrance (in death pit)
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-430, -50, 1564));
		firstLight->colour = glm::vec3(0, 1, 0);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0;
		firstLight->cutoff = 200.0;
		m_world->addLightObject(firstLight);
	}

	//goo pit waterfall to the right closest
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-589, -2, 1401));
		firstLight->colour = glm::vec3(0, 1, 0);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0.01;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	//goo pit waterfall to the right furthest
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-660, -2, 1401));
		firstLight->colour = glm::vec3(0, 1, 0);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0.01;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	//train path 1 1st light
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-975, -10, 1372));
		firstLight->colour = glm::vec3(0.57, 0.93, 0.93);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	//train path 1 2nd light
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-975, -10, 1243));
		firstLight->colour = glm::vec3(0.57, 0.93, 0.93);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	//train path 1 3rd light
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-975, -10, 1115));
		firstLight->colour = glm::vec3(0.57, 0.93, 0.93);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	//train path 1 4th light
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-975, -10, 988));
		firstLight->colour = glm::vec3(0.57, 0.93, 0.93);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	//train path 1 5th light
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-975, -10, 859));
		firstLight->colour = glm::vec3(0.57, 0.93, 0.93);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	//green arrow in the end of the tunnel
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-975, -7, 799));
		firstLight->colour = glm::vec3(0.0, 1, 0.0);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0.04;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	//path in between two train paths
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-854, -10, 752));
		firstLight->colour = glm::vec3(0.57, 0.93, 0.93);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	//train path 2 1st light
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-749, -10, 694));
		firstLight->colour = glm::vec3(0.57, 0.93, 0.93);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	//train path 2 2nd light
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-748, -10, 587));
		firstLight->colour = glm::vec3(0.57, 0.93, 0.93);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	//train path 2 3rd light
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-747, -10, 484));
		firstLight->colour = glm::vec3(0.57, 0.93, 0.93);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	//train path 2 4th light
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-746, -10, 375));
		firstLight->colour = glm::vec3(0.57, 0.93, 0.93);
		firstLight->constant = 0.02;
		firstLight->linear = 0.05;
		firstLight->quad = 0;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	////train path 2 5th light
	//{
	//	Animatable *anable = new Animatable();
	//	Light *firstLight = new Light(1, anable);
	//	anable->setPosition(glm::vec3(-747, -10, 200));
	//	firstLight->colour = glm::vec3(0.57, 0.93, 0.93);
	//	firstLight->constant = 0.02;
	//	firstLight->linear = 0.05;
	//	firstLight->quad = 0;
	//	firstLight->cutoff = 50.0;
	//	m_world->addLightObject(firstLight);
	//}


	//train path 2 exit
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-738, 70, 63));
		firstLight->colour = glm::vec3(1, 1, 1);
		firstLight->constant = 0.00;
		firstLight->linear = 0.00;
		firstLight->quad = 0.01;
		firstLight->cutoff = 200.0;
		m_world->addLightObject(firstLight);
	}



	//---------------------------------
	//----light around the statue------
	//---------------------------------

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-465, 8, -105));
		firstLight->colour = glm::vec3(1, 1, 1);
		firstLight->constant = 0.00;
		firstLight->linear = 0.00;
		firstLight->quad = 0.03;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-455, 8, -57));
		firstLight->colour = glm::vec3(1, 1, 1);
		firstLight->constant = 0.00;
		firstLight->linear = 0.00;
		firstLight->quad = 0.03;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-410, 8, -25));
		firstLight->colour = glm::vec3(1, 1, 1);
		firstLight->constant = 0.00;
		firstLight->linear = 0.00;
		firstLight->quad = 0.03;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-360, 8, -15));
		firstLight->colour = glm::vec3(1, 1, 1);
		firstLight->constant = 0.00;
		firstLight->linear = 0.00;
		firstLight->quad = 0.03;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-315, 8, -42));
		firstLight->colour = glm::vec3(1, 1, 1);
		firstLight->constant = 0.00;
		firstLight->linear = 0.00;
		firstLight->quad = 0.03;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-295, 8, -86));
		firstLight->colour = glm::vec3(1, 1, 1);
		firstLight->constant = 0.00;
		firstLight->linear = 0.00;
		firstLight->quad = 0.03;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-298, 8, -135));
		firstLight->colour = glm::vec3(1, 1, 1);
		firstLight->constant = 0.00;
		firstLight->linear = 0.00;
		firstLight->quad = 0.03;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-325, 8, -175));
		firstLight->colour = glm::vec3(1, 1, 1);
		firstLight->constant = 0.00;
		firstLight->linear = 0.00;
		firstLight->quad = 0.03;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-375, 8, -190));
		firstLight->colour = glm::vec3(1, 1, 1);
		firstLight->constant = 0.00;
		firstLight->linear = 0.00;
		firstLight->quad = 0.03;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-419, 8, -180));
		firstLight->colour = glm::vec3(1, 1, 1);
		firstLight->constant = 0.00;
		firstLight->linear = 0.00;
		firstLight->quad = 0.03;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-455, 8, -140));
		firstLight->colour = glm::vec3(1, 1, 1);
		firstLight->constant = 0.00;
		firstLight->linear = 0.00;
		firstLight->quad = 0.03;
		firstLight->cutoff = 50.0;
		m_world->addLightObject(firstLight);
	}

	//top of the statue
	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-388, 100, -108));
		firstLight->colour = glm::vec3(1, 1, 0.3);
		firstLight->constant = 0.04;
		firstLight->linear = 0.02;
		firstLight->quad = 0.01;
		firstLight->cutoff = 300.0;
		m_world->addLightObject(firstLight);
	}

	//---------------------------------
	//--end light around the statue----
	//---------------------------------





	//---------------------------------
	//------finish line lights---------
	//---------------------------------

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(38.5, 2, -52));
		firstLight->colour = glm::vec3(0, 0, 1);
		firstLight->constant = 0.1;
		firstLight->linear = 0.0;
		firstLight->quad = 0.03;
		firstLight->cutoff = 20.0;
		m_world->addLightObject(firstLight);
	}

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(25, 2, -52));
		firstLight->colour = glm::vec3(0, 0, 1);
		firstLight->constant = 0.1;
		firstLight->linear = 0.0;
		firstLight->quad = 0.03;
		firstLight->cutoff = 20.0;
		m_world->addLightObject(firstLight);
	}

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(11.5, 2, -52));
		firstLight->colour = glm::vec3(0, 0, 1);
		firstLight->constant = 0.1;
		firstLight->linear = 0.0;
		firstLight->quad = 0.03;
		firstLight->cutoff = 20.0;
		m_world->addLightObject(firstLight);
	}

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-2, 2, -52));
		firstLight->colour = glm::vec3(0, 0, 1);
		firstLight->constant = 0.1;
		firstLight->linear = 0.0;
		firstLight->quad = 0.03;
		firstLight->cutoff = 20.0;
		m_world->addLightObject(firstLight);
	}

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-15.5, 2, -52));
		firstLight->colour = glm::vec3(0, 0, 1);
		firstLight->constant = 0.1;
		firstLight->linear = 0.0;
		firstLight->quad = 0.03;
		firstLight->cutoff = 20.0;
		m_world->addLightObject(firstLight);
	}

	{
		Animatable *anable = new Animatable();
		Light *firstLight = new Light(1, anable);
		anable->setPosition(glm::vec3(-29, 2, -52));
		firstLight->colour = glm::vec3(0, 0, 1);
		firstLight->constant = 0.1;
		firstLight->linear = 0.0;
		firstLight->quad = 0.03;
		firstLight->cutoff = 20.0;
		m_world->addLightObject(firstLight);
	}


	//---------------------------------
	//----end finish line lights-------
	//---------------------------------
}