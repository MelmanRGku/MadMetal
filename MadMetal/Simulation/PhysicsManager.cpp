#pragma once

#include "PhysicsManager.h"
#include "PxDefaultAllocator.h"
#include "PxDefaultErrorCallback.h"
#include "PxTolerancesScale.h"
#include "iostream"
#include "PxDefaultSimulationFilterShader.h"
#include "World.h"

bool PhysicsManager::initialized = false; 
PxFoundation* PhysicsManager::physicsFoundation_ = NULL;
PxDefaultAllocator* PhysicsManager::defaultAllocator_ = NULL;
PxDefaultErrorCallback* PhysicsManager::defaultErrorCallback_ = NULL;
PxPhysics* PhysicsManager::topLevelPhysics_ = NULL;
PxCooking* PhysicsManager::m_cooking = NULL;
PxDefaultCpuDispatcher* PhysicsManager::mCpuDispatcher = NULL;
PxTolerancesScale *PhysicsManager::m_scale = NULL;
PxDefaultCpuDispatcher *PhysicsManager::cpuDispatcher;

PhysicsManager::PhysicsManager()
{
	
}

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::release() {
	shutdownPhysicsSimualtion();
}

void PhysicsManager::init() {
	if (initialized)
		return;

	defaultAllocator_ = new PxDefaultAllocator();
	defaultErrorCallback_ = new PxDefaultErrorCallback();
	m_scale = new PxTolerancesScale();
	initPhysicsSimulation();

	initialized = true;
}

void PhysicsManager::initPhysicsSimulation()
{

	physicsFoundation_ = PxCreateFoundation(PX_PHYSICS_VERSION, *defaultAllocator_, *defaultErrorCallback_);
	if (!physicsFoundation_)
	{
		std::cout << "PxCreateFoundation failed! This is a major issue. ERROR CODE: PX0001" << std::endl;
	}

	topLevelPhysics_ = PxCreateBasePhysics(PX_PHYSICS_VERSION, *physicsFoundation_, *m_scale, false);
	if (!topLevelPhysics_)
	{
		std::cout << "PxCreatePhysics failed! This is a major issue. ERROR CODE:PX0002" << std::endl;
	}

	m_cooking = PxCreateCooking(PX_PHYSICS_VERSION, *physicsFoundation_, PxCookingParams(PxTolerancesScale()));
	if (!m_cooking)
	{
		std::cout << "A fatal error has occured. ERROR CODE PX0007" << std::endl;
	}

	cpuDispatcher = PxDefaultCpuDispatcherCreate(8);
}

/*word 0 = id of actor
word 1 = what actor cares about hitting
word 2 = actor dependant, but information relevent to actor. 
	-index of player in array,
	-owner of projectile (index of player in array)
	-index of waypoint in array
	-etc
word 3 = also actor dependant, first thoughts would be:
	- damage of projectile
	- "Hello World" lol... jk
*/
void PhysicsManager::setupFiltering(PxRigidActor * actor, unsigned int actorId, unsigned int filterTarget, unsigned int extraActorInfo = 0, unsigned int extraInteractionInfo = 0)
{
	const PxU32 numShapes = actor->getNbShapes();
	PxShape** shapes = (PxShape**)malloc(sizeof(PxShape*)*numShapes);
	actor->getShapes(shapes, numShapes);
	PxFilterData data;
	data.word0 = actorId;
	data.word1 = filterTarget;
	data.word2 = extraActorInfo;
	data.word3 = extraInteractionInfo;
	shapes[0]->setSimulationFilterData(data);
	free(shapes);
}

void PhysicsManager::initCarPhysics() {
	PxInitVehicleSDK(*topLevelPhysics_);
	PxVehicleSetBasisVectors(PxVec3(0, 1, 0), PxVec3(0, 0, 1));			//coordinate system defined here. positive y is up, positive z is forward
	PxVehicleSetUpdateMode(PxVehicleUpdateMode::eACCELERATION);
}

void PhysicsManager::shutdownPhysicsSimualtion()
{
	cpuDispatcher->release();
	PxCloseVehicleSDK();
	m_cooking->release();
	topLevelPhysics_->release();
	physicsFoundation_->release();
	delete m_scale;
	delete defaultErrorCallback_;
	delete defaultAllocator_;
}

/*void PhysicsManager::updatePhysics(float dt)
{
	mScene->simulate(dt);
	mScene->fetchResults(true);

}*/

PxPhysics& PhysicsManager::getPhysicsInstance()
{
	return *topLevelPhysics_;
}

PxTolerancesScale& PhysicsManager::getScale()
{
	return *m_scale;
}

PxFoundation& PhysicsManager::getFoundation()
{
	return *physicsFoundation_;
}

PxCooking& PhysicsManager::getCookingInstance()
{
	return *m_cooking;
}

PxDefaultCpuDispatcher& PhysicsManager::getCpuDispatcher() {
	return *cpuDispatcher;
}