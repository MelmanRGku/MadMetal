#pragma once
#include <iostream>
#include "Audio/Audio.h"
#include "GameWorld.h"
#include "Objects/GameObject.h"
#include "Objects/Model.h"
#include "Renderer/VAO.h"
#include "PhysicsManager.h"
#include "Objects/ObjectUpdaters/ObjectPositionUpdater.h"
#include "Objects/ObjectUpdaters/ObjectRotationUpdater.h"
#include "Objects/ObjectUpdaters/ObjectUpdaterSequence.h"
#include "Objects/ObjectUpdaters/ObjectUpdaterParallel.h"


class Simulation{
private:

	GameWorld * gw;
	Audio a;
	std::vector<ObjectUpdater *> updaters;
	PhysicsManager * pm;

	void simulatePhysics()
	{
		std::cout << "Physics Simulated \n";
		//a.update();
		//NOTE: a.update() doesn't belong here. Replace with some function that registers stuff to do with the audio engine
		//a.playNewSound(0);
		

	}

	void simulateAnimation()
	{
		std::cout << "Animation Simulated \n";
	}

	void simulateAI()
	{
		std::cout << "AI Simulated \n";
	}

	void simulatePlayers()
	{
		std::cout << "Players Simulated \n";
	}

	void updateObjects(long dt) {
	
		for (unsigned int i = 0; i < updaters.size(); i++) {
			updaters.at(i)->update(dt);
		}

	}

public:
	Simulation()
	{
		gw = new GameWorld();
		pm = new PhysicsManager();
	}
	~Simulation()
	{
		delete gw;
	}

	void simulate(long dt)
	{
		std::cout << "Simulation Begun.... \n";
		simulateAI();
		simulatePlayers();
		simulatePhysics();
		simulateAnimation();
		updateObjects(dt);
		std::cout << "Simulation Ended.... \n";
	}

	GameWorld * getGameWorld() { return gw; }


	void setupBasicGameWorldObjects() {
		Model *model = new ObjModel("Assets/Models/Stormtrooper.obj");
		VAO *vao = new VAO(model);
		GameObject *obj = new GameObject(vao, model);
		gw->addGameObject(obj);
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
		upd1->addObjectUpdater(new ObjectPositionUpdater(gw->getGameObjects()->at(0), glm::vec3(0, 0.5, 0), 1000)); //Note: this only works because we know the stormtrooper is index 0
		upd1->addObjectUpdater(new ObjectPositionUpdater(gw->getGameObjects()->at(0), glm::vec3(0, -1, 0), 2000));
		upd1->addObjectUpdater(new ObjectPositionUpdater(gw->getGameObjects()->at(0), glm::vec3(0, 0.5, 0), 1000));

		ObjectUpdaterParallel *upd = new ObjectUpdaterParallel(ObjectUpdaterSequence::TYPE_INFINITE);
		upd->addObjectUpdater(upd1);
		upd->addObjectUpdater(new ObjectRotationUpdater(gw->getGameObjects()->at(0), glm::vec3(0, 180, 0), 1000, ObjectRotationUpdater::ANGLE_TYPE_DEGREES));
		updaters.push_back(upd);
		
	}
	
};