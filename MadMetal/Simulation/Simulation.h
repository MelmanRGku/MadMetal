#pragma once
#include <iostream>
#include "../Audio/Audio.h"
#include "GameWorld.h"
#include "../Objects/GameObject.h"
#include "../Objects/Model.h"
#include "../Renderer/VAO.h"


class Simulation{
private:

	GameWorld * gw;
	Audio a;

	

	void simulatePhysics()
	{
		std::cout << "Physics Simulated \n";
		a.update();
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

public:
	Simulation()
	{
		gw = new GameWorld();
	}
	~Simulation()
	{
		delete gw;
	}

	void simulate()
	{
		std::cout << "Simulation Begun.... \n";
		simulateAI();
		simulatePlayers();
		simulatePhysics();
		simulateAnimation();
		std::cout << "Simulation Ended.... \n";
	}

	GameWorld * getGameWorld() { return gw; }


	void setupBasicGameWorldObjects() {
		Model *model = new ObjModel("..\Assets/Models/Stormtrooper.obj");
		VAO *vao = new VAO(model);
		GameObject *obj = new GameObject(vao, model);
		gw->addGameObject(obj);
	}
	
};