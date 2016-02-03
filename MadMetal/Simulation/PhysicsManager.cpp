#pragma once

#include "PhysicsManager.h"
#include "PxDefaultAllocator.h"
#include "PxDefaultErrorCallback.h"
#include "PxTolerancesScale.h"

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

	topLevelPhysics_ = PxCreateBasePhysics(PX_PHYSICS_VERSION, *physicsFoundation_, scale, false);

}

void PhysicsManager::shutdownPhysicsSimualtion()
{
	topLevelPhysics_->release();
	physicsFoundation_->release();
	delete defaultErrorCallback_;
	delete defaultAllocator_;
}
