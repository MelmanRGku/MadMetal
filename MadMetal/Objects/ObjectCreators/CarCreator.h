#pragma once

#include "Simulation\PhysicsManager.h"
#include "PxVehicleSDK.h"
#include "PxVehicleDrive4W.h"
#include "PxVehicleUpdate.h"
#include "PxVehicleTireFriction.h"
#include "PxVehicleUtilSetup.h"


class CarCreator
{
private:
	enum
	{
		TIRE_TYPE_WETS = 0,
		TIRE_TYPE_SLICKS,
		TIRE_TYPE_ICE,
		TIRE_TYPE_MUD,
		MAX_NUM_TIRE_TYPES
	};

	enum 
	{
		SURFACE_GROUND = 0,
		SURFACE_GRASS,
		MAX_NUM_SURFACE_TYPES
	};

	//Collision types and flags describing collision interactions of each collision type.
	enum
	{
		COLLISION_FLAG_GROUND = 1 << 0,
		COLLISION_FLAG_WHEEL = 1 << 1,
		COLLISION_FLAG_CHASSIS = 1 << 2,
		COLLISION_FLAG_OBSTACLE = 1 << 3,
		COLLISION_FLAG_DRIVABLE_OBSTACLE = 1 << 4,

		COLLISION_FLAG_GROUND_AGAINST = COLLISION_FLAG_CHASSIS | COLLISION_FLAG_OBSTACLE | COLLISION_FLAG_DRIVABLE_OBSTACLE,
		COLLISION_FLAG_WHEEL_AGAINST = COLLISION_FLAG_WHEEL | COLLISION_FLAG_CHASSIS | COLLISION_FLAG_OBSTACLE,
		COLLISION_FLAG_CHASSIS_AGAINST = COLLISION_FLAG_GROUND | COLLISION_FLAG_WHEEL | COLLISION_FLAG_CHASSIS | COLLISION_FLAG_OBSTACLE | COLLISION_FLAG_DRIVABLE_OBSTACLE,
		COLLISION_FLAG_OBSTACLE_AGAINST = COLLISION_FLAG_GROUND | COLLISION_FLAG_WHEEL | COLLISION_FLAG_CHASSIS | COLLISION_FLAG_OBSTACLE | COLLISION_FLAG_DRIVABLE_OBSTACLE,
		COLLISION_FLAG_DRIVABLE_OBSTACLE_AGAINST = COLLISION_FLAG_GROUND | COLLISION_FLAG_CHASSIS | COLLISION_FLAG_OBSTACLE | COLLISION_FLAG_DRIVABLE_OBSTACLE,
	};

	enum
	{
		SAMPLEVEHICLE_DRIVABLE_SURFACE = 0xffff0000,
		SAMPLEVEHICLE_UNDRIVABLE_SURFACE = 0x0000ffff
	};

	PxReal gTireFrictionMultipliers[MAX_NUM_SURFACE_TYPES][MAX_NUM_TIRE_TYPES] = { { 0.5, 0.5, 0.5, 0.5 },
																					{ 0.5, 0.5, 0.5, 0.5 } };

	PxU32 MAX_NUM_4W_VEHICLES = 20;
	PxF32 gChassisMass = 5;
	PxVec3 gWheelCentreOffsets4 = PxVec3(0, 0, 0);
	PxConvexMesh *gChassisConvexMesh = new P();

	PxVehicleDrivableSurfaceToTireFrictionPairs* mSurfaceTirePairs;
public:
	CarCreator();
	~CarCreator();
	PxVehicleDrive4W *createCar(PxPhysics& topLevelPhysics, PxCooking& cooking, PxScene& scene, PxMaterial& mat);

	void createVehicle4WSimulationData
		(const PxF32 chassisMass, PxConvexMesh* chassisConvexMesh,
		const PxF32 wheelMass, PxConvexMesh** wheelConvexMeshes, const PxVec3* wheelCentreOffsets,
		PxVehicleWheelsSimData& wheelsData, PxVehicleDriveSimData4W& driveData, PxVehicleChassisData& chassisData);

	PxVec3 computeChassisAABBDimensions(const PxConvexMesh* chassisConvexMesh);

	void computeWheelWidthsAndRadii(PxConvexMesh** wheelConvexMeshes, PxF32* wheelWidths, PxF32* wheelRadii);

	PxRigidDynamic* createVehicleActor4W
		(const PxVehicleChassisData& chassisData,
		PxConvexMesh** wheelConvexMeshes, PxConvexMesh* chassisConvexMesh,
		PxScene& scene, PxPhysics& physics, const PxMaterial& material);

	void setupActor
		(PxRigidDynamic* vehActor,
		const PxFilterData& vehQryFilterData,
		const PxGeometry** wheelGeometries, const PxTransform* wheelLocalPoses, const PxU32 numWheelGeometries, const PxMaterial* wheelMaterial, const PxFilterData& wheelCollFilterData,
		const PxGeometry** chassisGeometries, const PxTransform* chassisLocalPoses, const PxU32 numChassisGeometries, const PxMaterial* chassisMaterial, const PxFilterData& chassisCollFilterData,
		const PxVehicleChassisData& chassisData,
		PxPhysics* physics);

	void SampleVehicleSetupVehicleShapeQueryFilterData(PxFilterData* qryFilterData);

	PxVehicleDrive4W *create4WVehicle
		(PxScene& scene, PxPhysics& physics, PxCooking& cooking, const PxMaterial& material,
		const PxF32 chassisMass, const PxVec3* wheelCentreOffsets4, PxConvexMesh* chassisConvexMesh, PxConvexMesh** wheelConvexMeshes4,
		const PxTransform& startTransform, const bool useAutoGearFlag);


	static PxConvexMesh* CreateConvexMesh(const PxVec3* verts, const PxU32 numVerts, PxPhysics* physics, PxCooking* cooking);

	void init(PxPhysics& physics, const PxMaterial** drivableSurfaceMaterials, const PxVehicleDrivableSurfaceType* drivableSurfaceTypes);
};

