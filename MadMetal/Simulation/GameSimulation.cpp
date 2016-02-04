#include "GameSimulation.h"

using namespace std;

void GameSimulation::simulatePhysics(float dt)
{
	std::cout << "Physics Simulated \n";
	//audio.update();
	//NOTE: a.update() doesn't belong here. Replace with some function that registers stuff to do with the audio engine
	//a.playNewSound(0);
	//a.playNewSound(0);
	//world->getGameObjects()->at(0)->updatePosition(0.03f, 0.0f, 0.0f);
	physics->updatePhysics(dt);
	PxTransform temp = world->getGameObjects()->at(0)->physxActor->getGlobalPose();
	world->getGameObjects()->at(0)->updatePosition(glm::vec3(temp.p.x, temp.p.y, temp.p.z));

	cout << world->getGameObjects()->at(0)->position.x << endl;
	cout << world->getGameObjects()->at(0)->position.y << endl;
	cout << world->getGameObjects()->at(0)->position.z << endl;
}

void GameSimulation::simulateAnimation()
{
	std::cout << "Animation Simulated \n";
}

void GameSimulation::simulateAI()
{
	std::cout << "AI Simulated \n";
}

void GameSimulation::simulatePlayers()
{
	std::cout << "Players Simulated \n";
}

void GameSimulation::updateObjects(double dt) {

	for (unsigned int i = 0; i < updaters.size(); i++) {
		updaters.at(i)->update(dt);
	}

}

void GameSimulation::initialize() {
	setupBasicGameWorldObjects();
	physics = new PhysicsManager(* world);
}

GameSimulation::GameSimulation()
{
}
GameSimulation::~GameSimulation()
{
}

void GameSimulation::simulate(float dt)
{
	std::cout << "Simulation Begun.... \n";
	simulateAI();
	simulatePlayers();
	simulatePhysics(dt);
	simulateAnimation();
	updateObjects(dt);
	std::cout << "Simulation Ended.... \n";
}


void GameSimulation::setupBasicGameWorldObjects() {
	Model *model = new ObjModel("Assets/Models/Stormtrooper.obj");
	VAO *vao = new VAO(model);
	GameObject *obj = new GameObject(vao, model);
	world->addGameObject(obj);
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
	upd1->addObjectUpdater(new ObjectPositionUpdater(world->getGameObjects()->at(0), glm::vec3(0, 0.5, 0), 1000));
	upd1->addObjectUpdater(new ObjectPositionUpdater(world->getGameObjects()->at(0), glm::vec3(0, -1, 0), 2000));
	upd1->addObjectUpdater(new ObjectPositionUpdater(world->getGameObjects()->at(0), glm::vec3(0, 0.5, 0), 1000));

	ObjectUpdaterParallel *upd = new ObjectUpdaterParallel(ObjectUpdaterSequence::TYPE_INFINITE);
	upd->addObjectUpdater(upd1);
	upd->addObjectUpdater(new ObjectRotationUpdater(world->getGameObjects()->at(0), glm::vec3(0, 180, 0), 1000, ObjectRotationUpdater::ANGLE_TYPE_DEGREES));
	updaters.push_back(upd);
	*/
}

