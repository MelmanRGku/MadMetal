#include "GameSimulation.h"
#include "PhysicsManager.h"
#include "PxDefaultCpuDispatcher.h"
#include "PxDefaultSimulationFilterShader.h"
#include "PxRigidStatic.h"

using namespace std;

GameSimulation::GameSimulation(PhysicsManager& physicsInstance, PlayerControllable * player)
: m_physicsHandler(physicsInstance)
{
	m_mainCamera = new Camera();
	player->setCamera(m_mainCamera);
	
	m_players.push_back(player);
	player->setGameWorld(m_world);
	
	initialize();
	
	
}

GameSimulation::~GameSimulation()
{
}



void GameSimulation::simulatePhysics(float dt)
{
//	audio->update();
	
	m_scene->simulate(dt);
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
	for (int i = 0; i < m_players.size(); i++)
	{
		m_players[i]->playFrame(dt);
	}
}

void GameSimulation::updateObjects(double dt) {

	m_mainCamera->update(dt);

	for (unsigned int i = 0; i < updaters.size(); i++) {
		updaters.at(i)->update(dt);
	}

}

void GameSimulation::initialize() {
	createPhysicsScene();
	setupBasicGameWorldObjects();
}

PxFilterFlags TestFilterShader(
	PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{

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
	sceneDesc.gravity = PxVec3(0.0f, -18.81, 0.0f);
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


void GameSimulation::setupBasicGameWorldObjects() {

	//Create a default material
	PxMaterial* mMaterial;
	mMaterial = m_physicsHandler.getPhysicsInstance().createMaterial(0, 0, 0.1f);    //static friction, dynamic friction, restitution
	if (!mMaterial)
	{
		std::cout << "Material failed to create. ERROR CODE: PX0006" << std::endl;
	}


	//load stormtrooper
	ObjModelLoader *loader = new ObjModelLoader();
	RenderableObject *obj = new RenderableObject();
	obj->model = loader->loadFromFile("Assets/Models/Stormtrooper.obj");
	m_world->addGameObject(obj);
	PxRigidDynamic *tmpActor = m_physicsHandler.getPhysicsInstance().createRigidDynamic(PxTransform(0, 0, -45));
	
	PxShape* aSphereShape = tmpActor->createShape(PxBoxGeometry(1,.1,1), *mMaterial);
	m_physicsHandler.setupFiltering(tmpActor,
		PhysicsManager::PLAYER,
		PhysicsManager::ENVIRONMENT | PhysicsManager::PROJECTILE | PhysicsManager::POWERUP | PhysicsManager::WAYPOINT,
		0,0);
	PxRigidBodyExt::updateMassAndInertia(*tmpActor, 0.5);
	obj->setActor(tmpActor);
	m_scene->addActor(*tmpActor);
	//assign stormtrooper to main char
	m_players[0]->setObject(tmpActor);
	
	//attach camera to stormtrooper
	m_mainCamera->setToFollow(obj);

	Projectile * ammo = new Projectile("");
	RenderableObject *ammoModel = new RenderableObject();
	ammoModel->model = loader->loadFromFile("Assets/Models/bullet.obj");
	ammoModel->
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

	
	
	//draw the floor
	loader = new ObjModelLoader();
	RenderableObject * drawPlane = new RenderableObject();
	drawPlane->model = loader->loadFromFile("Assets/Models/plane.obj");
	drawPlane->setActor(floor);
	m_world->addGameObject(drawPlane);

	loader = new ObjModelLoader();
	RenderableObject * leftPlane = new RenderableObject();
	leftPlane->model = loader->loadFromFile("Assets/Models/plane.obj");
	leftPlane->setActor(leftWall);
	leftPlane->updateRotation(glm::vec3(0, 0, 3.14 / 2));
	m_world->addGameObject(leftPlane);

	loader = new ObjModelLoader();
	RenderableObject * RightPlane = new RenderableObject();
	RightPlane->model = loader->loadFromFile("Assets/Models/plane.obj");
	RightPlane->setActor(rightWall);
	RightPlane->updateRotation(glm::vec3(0, 0, 3.14 / 2));
	m_world->addGameObject(RightPlane);


	//drawthe finish line
	loader = new ObjModelLoader();
	RenderableObject * finishLine = new RenderableObject();
	finishLine->model = loader->loadFromFile("Assets/Models/finishLine.obj");
	m_world->addGameObject(finishLine);

	//create a bounding box for storm tropper to run into
	PxRigidStatic *boundVolume = m_physicsHandler.getPhysicsInstance().createRigidStatic(PxTransform(0, 0, length - 5));
	aSphereShape = boundVolume->createShape(PxBoxGeometry(PxVec3(2,5,3)), *mMaterial);
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

