#pragma once

#include "PhysicsManager.h"
#include "PxDefaultAllocator.h"
#include "PxDefaultErrorCallback.h"
#include "PxTolerancesScale.h"
#include "iostream"
#include "PxDefaultSimulationFilterShader.h"
#include "GameWorld.h"


PhysicsManager::PhysicsManager(GameWorld & world)
	: world_(world)
{
	defaultAllocator_ = new PxDefaultAllocator();
	defaultErrorCallback_ = new PxDefaultErrorCallback();
	initPhysicsSimulation();
}

//PhysicsManager::PhysicsManager()
//{
//	defaultAllocator_ = new PxDefaultAllocator();
//	defaultErrorCallback_ = new PxDefaultErrorCallback();
//	initPhysicsSimulation();
//}

PhysicsManager::~PhysicsManager()
{
	shutdownPhysicsSimualtion();
}

void PhysicsManager::initPhysicsSimulation()
{
	PxTolerancesScale scale;

	physicsFoundation_ = PxCreateFoundation(PX_PHYSICS_VERSION, *defaultAllocator_, *defaultErrorCallback_);
	if (!physicsFoundation_)
	{
		std::cout << "PxCreateFoundation failed! This is a major issue. ERROR CODE: PX0001" << std::endl;
	}

	topLevelPhysics_ = PxCreateBasePhysics(PX_PHYSICS_VERSION, *physicsFoundation_, scale, false);
	if (!topLevelPhysics_)
	{
		std::cout << "PxCreatePhysics failed! This is a major issue. ERROR CODE:PX0002" << std::endl;
	}
	/*
	if (!PxInitExtensions(*topLevelPhysics_))
		std::cout << "PxInitExtensions failed! This is a major issue. ERROR CODE:PX0003" << std::endl;
		*/

	PxSceneDesc sceneDesc(scale);
	//sceneDesc = new PxSceneDesc(topLevelPhysics_->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, 0.0f, 0.0f);
	//customizeSceneDesc(sceneDesc);

	if (!sceneDesc.cpuDispatcher)
	{
		mCpuDispatcher = PxDefaultCpuDispatcherCreate(8);
		if (!mCpuDispatcher)
		{
			std::cout << "mCpuDispatcher thing failed. ERROR CODE: PX0004" << std::endl;
		}
		sceneDesc.cpuDispatcher = mCpuDispatcher;
	}
	if (!sceneDesc.filterShader)
	{
		sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	}

	/*
#ifdef PX_WINDOWS
	if (!sceneDesc.gpuDispatcher && mCudaContextManager)
	{
		sceneDesc.gpuDispatcher = mCudaContextManager->getGpuDispatcher();
	}
	
#endif
	*/
	mScene = topLevelPhysics_->createScene(sceneDesc);
	if (!mScene)
	{
		std::cout << "The scene is a lie. ERROR CODE: PX0005" << std::endl;
	}

	PxMaterial* mMaterial;

	mMaterial = topLevelPhysics_->createMaterial(0.5f, 0.5f, 0.1f);    //static friction, dynamic friction, restitution
	if (!mMaterial)
	{
		std::cout << "Material failed to create. ERROR CODE: PX0006" << std::endl;
	}

	PxRigidDynamic* aSphereActor = topLevelPhysics_->createRigidDynamic(PxTransform(PxVec3(PxReal(0.0), PxReal(0.0), PxReal(0.0))));
	PxShape* aSphereShape = aSphereActor->createShape(PxSphereGeometry(0.2), *mMaterial);

	PxRigidBodyExt::updateMassAndInertia(*aSphereActor, 0.5);

	aSphereActor->setLinearVelocity(PxVec3(PxReal(0.0), PxReal(0.0001), PxReal(0.0)));

	mScene->addActor(*aSphereActor);
	world_.getGameObjects()->at(0)->setPhysxActor(aSphereActor);
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
	mScene->fetchResults(true);

}