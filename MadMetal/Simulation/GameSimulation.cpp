#include "GameSimulation.h"


void GameSimulation::simulatePhysics()
{
	audio->update();

}

void GameSimulation::simulateAnimation()
{
}

void GameSimulation::simulateAI()
{
}

void GameSimulation::simulatePlayers()
{
}

void GameSimulation::updateObjects(double dt) {

	for (unsigned int i = 0; i < updaters.size(); i++) {
		updaters.at(i)->update(dt);
	}

}

void GameSimulation::initialize() {
	setupBasicGameWorldObjects();
}

GameSimulation::GameSimulation()
{
}
GameSimulation::~GameSimulation()
{
}

void GameSimulation::simulate(double dt)
{
	simulateAI();
	simulatePlayers();
	simulatePhysics();
	simulateAnimation();
	updateObjects(dt);
}


void GameSimulation::setupBasicGameWorldObjects() {
	ObjModelLoader *loader = new ObjModelLoader();
	RenderableObject *obj = new RenderableObject();
	obj->model = loader->loadFromFile("Assets/Models/Stormtrooper.obj");
	world->addGameObject(obj);
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
	
	ObjectUpdaterSequence *upd1 = new ObjectUpdaterSequence(ObjectUpdaterSequence::TYPE_ONCE);
	upd1->addObjectUpdater(new ObjectPositionUpdater(obj, glm::vec3(0, 0.5, 0), 1000));
	upd1->addObjectUpdater(new ObjectPositionUpdater(obj, glm::vec3(0, -1, 0), 2000));
	upd1->addObjectUpdater(new ObjectPositionUpdater(obj, glm::vec3(0, 0.5, 0), 1000));

	ObjectUpdaterParallel *upd = new ObjectUpdaterParallel(ObjectUpdaterSequence::TYPE_INFINITE);
	upd->addObjectUpdater(upd1);
	upd->addObjectUpdater(new ObjectRotationUpdater(obj, glm::vec3(0, 180, 0), 1000, ObjectRotationUpdater::ANGLE_TYPE_DEGREES));
	updaters.push_back(upd);
	
}