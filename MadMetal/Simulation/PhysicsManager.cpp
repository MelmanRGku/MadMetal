#pragma once

#include "PhysicsManager.h"
#include "PxDefaultAllocator.h"
#include "PxDefaultErrorCallback.h"
#include "PxTolerancesScale.h"
#include "iostream"
#include "PxDefaultSimulationFilterShader.h"

PhysicsManager::PhysicsManager()
{
	defaultAllocator_ = new PxDefaultAllocator();
	defaultErrorCallback_ = new PxDefaultErrorCallback();
	initPhysicsSimulation();
}

PhysicsManager::~PhysicsManager()
{
	shutdownPhysicsSimualtion();
}

void PhysicsManager::initPhysicsSimulation()
{
	PxTolerancesScale scale;

	physicsFoundation_ = PxCreateFoundation(PX_PHYSICS_VERSION, *defaultAllocator_, *defaultErrorCallback_);
	if (!physicsFoundation_)
		std::cout << "PxCreateFoundation failed! This is a major issue. ERROR CODE: PX0001" << std::endl;

	topLevelPhysics_ = PxCreateBasePhysics(PX_PHYSICS_VERSION, *physicsFoundation_, scale, false);
	if (!topLevelPhysics_)
		std::cout << "PxCreatePhysics failed! This is a major issue. ERROR CODE:PX0002" << std::endl;

	if (!PxInitExtensions(*topLevelPhysics_))
		std::cout << "PxInitExtensions failed! This is a major issue. ERROR CODE:PX0003" << std::endl;

	//static PxDefaultSimulationFilterShader gDefaultFilterShader;



	sceneDesc = new PxSceneDesc(topLevelPhysics_->getTolerancesScale());
	sceneDesc->gravity = PxVec3(0.0f, -9.81f, 0.0f);
	//customizeSceneDesc(sceneDesc);

	if (!sceneDesc->cpuDispatcher)
	{
		mCpuDispatcher = PxDefaultCpuDispatcherCreate(8);
		if (!mCpuDispatcher)
			//fatalError("PxDefaultCpuDispatcherCreate failed!");
		sceneDesc->cpuDispatcher = mCpuDispatcher;
	}
//	if (!sceneDesc.filterShader)
//		sceneDesc.filterShader = &gDefaultFilterShader;

	/*
#ifdef PX_WINDOWS
	if (!sceneDesc.gpuDispatcher && mCudaContextManager)
	{
		sceneDesc.gpuDispatcher = mCudaContextManager->getGpuDispatcher();
	}
	
#endif
	*/
	mScene = topLevelPhysics_->createScene(*sceneDesc);
//	if (!mScene)
		//fatalError("createScene failed!");



}

void PhysicsManager::shutdownPhysicsSimualtion()
{
	topLevelPhysics_->release();
	physicsFoundation_->release();
	delete defaultErrorCallback_;
	delete defaultAllocator_;
}

void PhysicsManager::updatePhysics(float dt)
{
	mScene->simulate(dt);
}