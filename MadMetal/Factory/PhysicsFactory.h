#pragma once 
#include "Simulation\PhysicsManager.h"

class PhysicsFactory
{
public:
	PhysicsFactory(PhysicsManager &manager) : m_physicsManager(manager) {}
	~PhysicsFactory(){}

	/*
	PxRigidActor * makePhysicsActor(Enum actorToMake)
	{
		Big switch statement utilizing the enum physics types
	}
	*/
private: //members
	PhysicsManager & m_physicsManager;
	//enum of physics objects to make


};