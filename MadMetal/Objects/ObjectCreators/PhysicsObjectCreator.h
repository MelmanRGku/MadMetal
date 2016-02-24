#pragma once

#include <new>
#include "SnippetVehicleCreate.h"
#include "SnippetVehicleRaycast.h"
#include "SnippetVehicleFilterShader.h"
#include "SnippetVehicleTireFriction.h"
#include "PxPhysicsAPI.h"

class PhysicsObjectCreator
{
private:
	PxPhysics *physics;
	PxCooking *cooking;

	void customizeVehicleToLengthScale(const PxReal lengthScale, PxRigidDynamic* rigidDynamic, PxVehicleWheelsSimData* wheelsSimData, PxVehicleDriveSimData* driveSimData);
	void customizeVehicleToLengthScale(const PxReal lengthScale, PxRigidDynamic* rigidDynamic, PxVehicleWheelsSimData* wheelsSimData, PxVehicleDriveSimData4W* driveSimData);
public:
	PhysicsObjectCreator(PxPhysics *physics, PxCooking *cooking);
	~PhysicsObjectCreator();

	/* Use this function to create a drivable box. Note: any object that is not drivable will NOT allow a car to drive on it!
	Any object that is collidable, but should not be driven on (like walls) should not use this function.
	Arguments:	Material - the usual material is fine, but this will be the material of the object.
		Position - The location the new object will be placed at
		PxBoxGeometry - The geometry of the new object
	*/
	PxRigidStatic* createDrivingBox(physx::PxMaterial* material, PxTransform position, PxBoxGeometry box);
	PxRigidStatic* createDrivablePlane(physx::PxMaterial* material);
	PxConvexMesh* createConvexMesh(const PxVec3* verts, const PxU32 numVerts);
	PxConvexMesh* createChassisMesh(const PxVec3 dims);
	PxConvexMesh* createWheelMesh(const PxF32 width, const PxF32 radius);
	PxRigidDynamic* createVehicleActor (const PxVehicleChassisData& chassisData,
		PxMaterial** wheelMaterials, PxConvexMesh** wheelConvexMeshes, const PxU32 numWheels,
		PxMaterial** chassisMaterials, PxConvexMesh** chassisConvexMeshes, const PxU32 numChassisMeshes);
};

