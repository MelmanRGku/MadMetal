#include "CarCreator.h"


CarCreator::CarCreator()
{
}


CarCreator::~CarCreator()
{
}

void CarCreator::computeWheelWidthsAndRadii(PxConvexMesh** wheelConvexMeshes, PxF32* wheelWidths, PxF32* wheelRadii)
{
	for (PxU32 i = 0; i<4; i++)
	{
		const PxU32 numWheelVerts = wheelConvexMeshes[i]->getNbVertices();
		const PxVec3* wheelVerts = wheelConvexMeshes[i]->getVertices();
		PxVec3 wheelMin(PX_MAX_F32, PX_MAX_F32, PX_MAX_F32);
		PxVec3 wheelMax(-PX_MAX_F32, -PX_MAX_F32, -PX_MAX_F32);
		for (PxU32 j = 0; j<numWheelVerts; j++)
		{
			wheelMin.x = PxMin(wheelMin.x, wheelVerts[j].x);
			wheelMin.y = PxMin(wheelMin.y, wheelVerts[j].y);
			wheelMin.z = PxMin(wheelMin.z, wheelVerts[j].z);
			wheelMax.x = PxMax(wheelMax.x, wheelVerts[j].x);
			wheelMax.y = PxMax(wheelMax.y, wheelVerts[j].y);
			wheelMax.z = PxMax(wheelMax.z, wheelVerts[j].z);
		}
		wheelWidths[i] = wheelMax.x - wheelMin.x;
		wheelRadii[i] = PxMax(wheelMax.y, wheelMax.z)*0.975f;
	}
}

PxVec3 CarCreator::computeChassisAABBDimensions(const PxConvexMesh* chassisConvexMesh)
{
	const PxU32 numChassisVerts = chassisConvexMesh->getNbVertices();
	const PxVec3* chassisVerts = chassisConvexMesh->getVertices();
	PxVec3 chassisMin(PX_MAX_F32, PX_MAX_F32, PX_MAX_F32);
	PxVec3 chassisMax(-PX_MAX_F32, -PX_MAX_F32, -PX_MAX_F32);
	for (PxU32 i = 0; i<numChassisVerts; i++)
	{
		chassisMin.x = PxMin(chassisMin.x, chassisVerts[i].x);
		chassisMin.y = PxMin(chassisMin.y, chassisVerts[i].y);
		chassisMin.z = PxMin(chassisMin.z, chassisVerts[i].z);
		chassisMax.x = PxMax(chassisMax.x, chassisVerts[i].x);
		chassisMax.y = PxMax(chassisMax.y, chassisVerts[i].y);
		chassisMax.z = PxMax(chassisMax.z, chassisVerts[i].z);
	}
	const PxVec3 chassisDims = chassisMax - chassisMin;
	return chassisDims;
}


void CarCreator::createVehicle4WSimulationData
(const PxF32 chassisMass, PxConvexMesh* chassisConvexMesh,
const PxF32 wheelMass, PxConvexMesh** wheelConvexMeshes, const PxVec3* wheelCentreOffsets,
PxVehicleWheelsSimData& wheelsData, PxVehicleDriveSimData4W& driveData, PxVehicleChassisData& chassisData) {
	//Extract the chassis AABB dimensions from the chassis convex mesh.
	const PxVec3 chassisDims = computeChassisAABBDimensions(chassisConvexMesh);

	//The origin is at the center of the chassis mesh.
	//Set the center of mass to be below this point and a little towards the front.
	const PxVec3 chassisCMOffset = PxVec3(0.0f, -chassisDims.y*0.5f + 0.65f, 0.25f);

	//Now compute the chassis mass and moment of inertia.
	//Use the moment of inertia of a cuboid as an approximate value for the chassis moi.
	PxVec3 chassisMOI
		((chassisDims.y*chassisDims.y + chassisDims.z*chassisDims.z)*chassisMass / 12.0f,
		(chassisDims.x*chassisDims.x + chassisDims.z*chassisDims.z)*chassisMass / 12.0f,
		(chassisDims.x*chassisDims.x + chassisDims.y*chassisDims.y)*chassisMass / 12.0f);
	//A bit of tweaking here.  The car will have more responsive turning if we reduce the
	//y-component of the chassis moment of inertia.
	chassisMOI.y *= 0.8f;

	//Let's set up the chassis data structure now.
	chassisData.mMass = chassisMass;
	chassisData.mMOI = chassisMOI;
	chassisData.mCMOffset = chassisCMOffset;

	//Compute the sprung masses of each suspension spring using a helper function.
	PxF32 suspSprungMasses[4];
	PxVehicleComputeSprungMasses(4, wheelCentreOffsets, chassisCMOffset, chassisMass, 1, suspSprungMasses);

	//Extract the wheel radius and width from the wheel convex meshes.
	PxF32 wheelWidths[4];
	PxF32 wheelRadii[4];
	computeWheelWidthsAndRadii(wheelConvexMeshes, wheelWidths, wheelRadii);

	//Now compute the wheel masses and inertias components around the axle's axis.
	//http://en.wikipedia.org/wiki/List_of_moments_of_inertia
	PxF32 wheelMOIs[4];
	for (PxU32 i = 0; i<4; i++)
	{
		wheelMOIs[i] = 0.5f*wheelMass*wheelRadii[i] * wheelRadii[i];
	}
	//Let's set up the wheel data structures now with radius, mass, and moi.
	PxVehicleWheelData wheels[4];
	for (PxU32 i = 0; i<4; i++)
	{
		wheels[i].mRadius = wheelRadii[i];
		wheels[i].mMass = wheelMass;
		wheels[i].mMOI = wheelMOIs[i];
		wheels[i].mWidth = wheelWidths[i];
	}
	//Disable the handbrake from the front wheels and enable for the rear wheels
	wheels[PxVehicleDrive4WWheelOrder::eFRONT_LEFT].mMaxHandBrakeTorque = 0.0f;
	wheels[PxVehicleDrive4WWheelOrder::eFRONT_RIGHT].mMaxHandBrakeTorque = 0.0f;
	wheels[PxVehicleDrive4WWheelOrder::eREAR_LEFT].mMaxHandBrakeTorque = 4000.0f;
	wheels[PxVehicleDrive4WWheelOrder::eREAR_RIGHT].mMaxHandBrakeTorque = 4000.0f;
	//Enable steering for the front wheels and disable for the front wheels.
	wheels[PxVehicleDrive4WWheelOrder::eFRONT_LEFT].mMaxSteer = PxPi*0.3333f;
	wheels[PxVehicleDrive4WWheelOrder::eFRONT_RIGHT].mMaxSteer = PxPi*0.3333f;
	wheels[PxVehicleDrive4WWheelOrder::eREAR_LEFT].mMaxSteer = 0.0f;
	wheels[PxVehicleDrive4WWheelOrder::eREAR_RIGHT].mMaxSteer = 0.0f;

	//Let's set up the tire data structures now.
	//Put slicks on the front tires and wets on the rear tires.
	PxVehicleTireData tires[4];
	tires[PxVehicleDrive4WWheelOrder::eFRONT_LEFT].mType = TIRE_TYPE_SLICKS;
	tires[PxVehicleDrive4WWheelOrder::eFRONT_RIGHT].mType = TIRE_TYPE_SLICKS;
	tires[PxVehicleDrive4WWheelOrder::eREAR_LEFT].mType = TIRE_TYPE_WETS;
	tires[PxVehicleDrive4WWheelOrder::eREAR_RIGHT].mType = TIRE_TYPE_WETS;

	//Let's set up the suspension data structures now.
	PxVehicleSuspensionData susps[4];
	for (PxU32 i = 0; i<4; i++)
	{
		susps[i].mMaxCompression = 0.3f;
		susps[i].mMaxDroop = 0.1f;
		susps[i].mSpringStrength = 35000.0f;
		susps[i].mSpringDamperRate = 4500.0f;
	}
	susps[PxVehicleDrive4WWheelOrder::eFRONT_LEFT].mSprungMass = suspSprungMasses[PxVehicleDrive4WWheelOrder::eFRONT_LEFT];
	susps[PxVehicleDrive4WWheelOrder::eFRONT_RIGHT].mSprungMass = suspSprungMasses[PxVehicleDrive4WWheelOrder::eFRONT_RIGHT];
	susps[PxVehicleDrive4WWheelOrder::eREAR_LEFT].mSprungMass = suspSprungMasses[PxVehicleDrive4WWheelOrder::eREAR_LEFT];
	susps[PxVehicleDrive4WWheelOrder::eREAR_RIGHT].mSprungMass = suspSprungMasses[PxVehicleDrive4WWheelOrder::eREAR_RIGHT];

	//Set up the camber.
	//Remember that the left and right wheels need opposite camber so that the car preserves symmetry about the forward direction.
	//Set the camber to 0.0f when the spring is neither compressed or elongated.
	const PxF32 camberAngleAtRest = 0.0;
	susps[PxVehicleDrive4WWheelOrder::eFRONT_LEFT].mCamberAtRest = camberAngleAtRest;
	susps[PxVehicleDrive4WWheelOrder::eFRONT_RIGHT].mCamberAtRest = -camberAngleAtRest;
	susps[PxVehicleDrive4WWheelOrder::eREAR_LEFT].mCamberAtRest = camberAngleAtRest;
	susps[PxVehicleDrive4WWheelOrder::eREAR_RIGHT].mCamberAtRest = -camberAngleAtRest;
	//Set the wheels to camber inwards at maximum droop (the left and right wheels almost form a V shape)
	const PxF32 camberAngleAtMaxDroop = 0.1f;
	susps[PxVehicleDrive4WWheelOrder::eFRONT_LEFT].mCamberAtMaxDroop = camberAngleAtMaxDroop;
	susps[PxVehicleDrive4WWheelOrder::eFRONT_RIGHT].mCamberAtMaxDroop = -camberAngleAtMaxDroop;
	susps[PxVehicleDrive4WWheelOrder::eREAR_LEFT].mCamberAtMaxDroop = camberAngleAtMaxDroop;
	susps[PxVehicleDrive4WWheelOrder::eREAR_RIGHT].mCamberAtMaxDroop = -camberAngleAtMaxDroop;
	//Set the wheels to camber outwards at maximum compression (the left and right wheels almost form a A shape).
	const PxF32 camberAngleAtMaxCompression = -0.1f;
	susps[PxVehicleDrive4WWheelOrder::eFRONT_LEFT].mCamberAtMaxCompression = camberAngleAtMaxCompression;
	susps[PxVehicleDrive4WWheelOrder::eFRONT_RIGHT].mCamberAtMaxCompression = -camberAngleAtMaxCompression;
	susps[PxVehicleDrive4WWheelOrder::eREAR_LEFT].mCamberAtMaxCompression = camberAngleAtMaxCompression;
	susps[PxVehicleDrive4WWheelOrder::eREAR_RIGHT].mCamberAtMaxCompression = -camberAngleAtMaxCompression;

	//We need to set up geometry data for the suspension, wheels, and tires.
	//We already know the wheel centers described as offsets from the actor center and the center of mass offset from actor center.
	//From here we can approximate application points for the tire and suspension forces.
	//Lets assume that the suspension travel directions are absolutely vertical.
	//Also assume that we apply the tire and suspension forces 30cm below the center of mass.
	PxVec3 suspTravelDirections[4] = { PxVec3(0, -1, 0), PxVec3(0, -1, 0), PxVec3(0, -1, 0), PxVec3(0, -1, 0) };
	PxVec3 wheelCentreCMOffsets[4];
	PxVec3 suspForceAppCMOffsets[4];
	PxVec3 tireForceAppCMOffsets[4];
	for (PxU32 i = 0; i<4; i++)
	{
		wheelCentreCMOffsets[i] = wheelCentreOffsets[i] - chassisCMOffset;
		suspForceAppCMOffsets[i] = PxVec3(wheelCentreCMOffsets[i].x, -0.3f, wheelCentreCMOffsets[i].z);
		tireForceAppCMOffsets[i] = PxVec3(wheelCentreCMOffsets[i].x, -0.3f, wheelCentreCMOffsets[i].z);
	}

	//Now add the wheel, tire and suspension data.
	for (PxU32 i = 0; i<4; i++)
	{
		wheelsData.setWheelData(i, wheels[i]);
		wheelsData.setTireData(i, tires[i]);
		wheelsData.setSuspensionData(i, susps[i]);
		wheelsData.setSuspTravelDirection(i, suspTravelDirections[i]);
		wheelsData.setWheelCentreOffset(i, wheelCentreCMOffsets[i]);
		wheelsData.setSuspForceAppPointOffset(i, suspForceAppCMOffsets[i]);
		wheelsData.setTireForceAppPointOffset(i, tireForceAppCMOffsets[i]);
	}

	//Set the car to perform 3 sub-steps when it moves with a forwards speed of less than 5.0
	//and with a single step when it moves at speed greater than or equal to 5.0.
	wheelsData.setSubStepCount(5.0f, 3, 1);


	//Now set up the differential, engine, gears, clutch, and Ackermann steering.

	//Diff
	PxVehicleDifferential4WData diff;
	diff.mType = PxVehicleDifferential4WData::eDIFF_TYPE_LS_4WD;
	driveData.setDiffData(diff);

	//Engine
	PxVehicleEngineData engine;
	engine.mPeakTorque = 500.0f;
	engine.mMaxOmega = 600.0f;//approx 6000 rpm
	driveData.setEngineData(engine);

	//Gears
	PxVehicleGearsData gears;
	gears.mSwitchTime = 0.5f;
	driveData.setGearsData(gears);

	//Clutch
	PxVehicleClutchData clutch;
	clutch.mStrength = 10.0f;
	driveData.setClutchData(clutch);

	//Ackermann steering accuracy
	PxVehicleAckermannGeometryData ackermann;
	ackermann.mAccuracy = 1.0f;
	ackermann.mAxleSeparation = wheelCentreOffsets[PxVehicleDrive4WWheelOrder::eFRONT_LEFT].z
		- wheelCentreOffsets[PxVehicleDrive4WWheelOrder::eREAR_LEFT].z;
	ackermann.mFrontWidth = wheelCentreOffsets[PxVehicleDrive4WWheelOrder::eFRONT_RIGHT].x
		- wheelCentreOffsets[PxVehicleDrive4WWheelOrder::eFRONT_LEFT].x;
	ackermann.mRearWidth = wheelCentreOffsets[PxVehicleDrive4WWheelOrder::eREAR_RIGHT].x
		- wheelCentreOffsets[PxVehicleDrive4WWheelOrder::eREAR_LEFT].x;
	driveData.setAckermannGeometryData(ackermann);
}

PxRigidDynamic* CarCreator::createVehicleActor4W
(const PxVehicleChassisData& chassisData,
PxConvexMesh** wheelConvexMeshes, PxConvexMesh* chassisConvexMesh,
PxScene& scene, PxPhysics& physics, const PxMaterial& material)
{
	//We need a rigid body actor for the vehicle.
	//Don't forget to add the actor the scene after setting up the associated vehicle.
	PxRigidDynamic* vehActor = physics.createRigidDynamic(PxTransform::createIdentity());

	//We need to add wheel collision shapes, their local poses, a material for the wheels, and a simulation filter for the wheels.
	PxConvexMeshGeometry frontLeftWheelGeom(wheelConvexMeshes[0]);
	PxConvexMeshGeometry frontRightWheelGeom(wheelConvexMeshes[1]);
	PxConvexMeshGeometry rearLeftWheelGeom(wheelConvexMeshes[2]);
	PxConvexMeshGeometry rearRightWheelGeom(wheelConvexMeshes[3]);
	const PxGeometry* wheelGeometries[4] = { &frontLeftWheelGeom, &frontRightWheelGeom, &rearLeftWheelGeom, &rearRightWheelGeom };
	const PxTransform wheelLocalPoses[4] = { PxTransform::createIdentity(), PxTransform::createIdentity(), PxTransform::createIdentity(), PxTransform::createIdentity() };
	const PxMaterial& wheelMaterial = material;
	PxFilterData wheelCollFilterData;
	wheelCollFilterData.word0 = COLLISION_FLAG_WHEEL;
	wheelCollFilterData.word1 = COLLISION_FLAG_WHEEL_AGAINST;

	//We need to add chassis collision shapes, their local poses, a material for the chassis, and a simulation filter for the chassis.
	PxConvexMeshGeometry chassisConvexGeom(chassisConvexMesh);
	const PxGeometry* chassisGeoms[1] = { &chassisConvexGeom };
	const PxTransform chassisLocalPoses[1] = { PxTransform::createIdentity() };
	const PxMaterial& chassisMaterial = material;
	PxFilterData chassisCollFilterData;
	chassisCollFilterData.word0 = COLLISION_FLAG_CHASSIS;
	chassisCollFilterData.word1 = COLLISION_FLAG_CHASSIS_AGAINST;

	//Create a query filter data for the car to ensure that cars
	//do not attempt to drive on themselves.
	PxFilterData vehQryFilterData;
	SampleVehicleSetupVehicleShapeQueryFilterData(&vehQryFilterData);

	//Set up the physx rigid body actor with shapes, local poses, and filters.
	setupActor
		(vehActor,
		vehQryFilterData,
		wheelGeometries, wheelLocalPoses, 4, &wheelMaterial, wheelCollFilterData,
		chassisGeoms, chassisLocalPoses, 1, &chassisMaterial, chassisCollFilterData,
		chassisData,
		&physics);

	return vehActor;
}

void CarCreator::SampleVehicleSetupVehicleShapeQueryFilterData(PxFilterData* qryFilterData)
{
	//CHECK_MSG(0 == qryFilterData->word3, "word3 is reserved for filter data for vehicle raycast queries");
	qryFilterData->word3 = (PxU32)SAMPLEVEHICLE_UNDRIVABLE_SURFACE;
}

void CarCreator::setupActor
(PxRigidDynamic* vehActor,
const PxFilterData& vehQryFilterData,
const PxGeometry** wheelGeometries, const PxTransform* wheelLocalPoses, const PxU32 numWheelGeometries, const PxMaterial* wheelMaterial, const PxFilterData& wheelCollFilterData,
const PxGeometry** chassisGeometries, const PxTransform* chassisLocalPoses, const PxU32 numChassisGeometries, const PxMaterial* chassisMaterial, const PxFilterData& chassisCollFilterData,
const PxVehicleChassisData& chassisData,
PxPhysics* physics)
{
	//Add all the wheel shapes to the actor.
	for (PxU32 i = 0; i<numWheelGeometries; i++)
	{
		PxShape* wheelShape = vehActor->createShape(*wheelGeometries[i], *wheelMaterial);
		wheelShape->setQueryFilterData(vehQryFilterData);
		wheelShape->setSimulationFilterData(wheelCollFilterData);
		wheelShape->setLocalPose(wheelLocalPoses[i]);
	}

	//Add the chassis shapes to the actor.
	for (PxU32 i = 0; i<numChassisGeometries; i++)
	{
		PxShape* chassisShape = vehActor->createShape(*chassisGeometries[i], *chassisMaterial);
		chassisShape->setQueryFilterData(vehQryFilterData);
		chassisShape->setSimulationFilterData(chassisCollFilterData);
		chassisShape->setLocalPose(chassisLocalPoses[i]);
	}

	vehActor->setMass(chassisData.mMass);
	vehActor->setMassSpaceInertiaTensor(chassisData.mMOI);
	vehActor->setCMassLocalPose(PxTransform(chassisData.mCMOffset, PxQuat::createIdentity()));
}

PxVehicleDrive4W *CarCreator::create4WVehicle
(PxScene& scene, PxPhysics& physics, PxCooking& cooking, const PxMaterial& material,
const PxF32 chassisMass, const PxVec3* wheelCentreOffsets4, PxConvexMesh* chassisConvexMesh, PxConvexMesh** wheelConvexMeshes4,
const PxTransform& startTransform, const bool useAutoGearFlag)
{
	PX_ASSERT(mNumVehicles<MAX_NUM_4W_VEHICLES);

	PxVehicleWheelsSimData* wheelsSimData = PxVehicleWheelsSimData::allocate(4);
	PxVehicleDriveSimData4W driveSimData;
	PxVehicleChassisData chassisData;
	createVehicle4WSimulationData
		(chassisMass, chassisConvexMesh,
		20.0f, wheelConvexMeshes4, wheelCentreOffsets4,
		*wheelsSimData, driveSimData, chassisData);

	//Instantiate and finalize the vehicle using physx.
	PxRigidDynamic* vehActor = createVehicleActor4W(chassisData, wheelConvexMeshes4, chassisConvexMesh, scene, physics, material);

	//Create a car.
	PxVehicleDrive4W* car = PxVehicleDrive4W::allocate(4);
	car->setup(&physics, vehActor, *wheelsSimData, driveSimData, 0);

	//Free the sim data because we don't need that any more.
	wheelsSimData->free();

	//Don't forget to add the actor to the scene.
	scene.addActor(*vehActor);

	//Set the transform and the instantiated car and set it be to be at rest.
	//resetNWCar(startTransform, car);
	
	//Set the autogear mode of the instantiate car.
	car->mDriveDynData.setUseAutoGears(useAutoGearFlag);

	return car;
}

void CarCreator::init(PxPhysics& physics, const PxMaterial** drivableSurfaceMaterials, const PxVehicleDrivableSurfaceType* drivableSurfaceTypes)
{
	//Initialise the sdk.
	PxInitVehicleSDK(physics);

	//Scene query data for to allow raycasts for all suspensions of all vehicles.
	//mSqData = SampleVehicleSceneQueryData::allocate(MAX_NUM_4W_VEHICLES * 4);

	//Set up the friction values arising from combinations of tire type and surface type.
	mSurfaceTirePairs = new PxVehicleDrivableSurfaceToTireFrictionPairs();
	mSurfaceTirePairs -> setup(MAX_NUM_TIRE_TYPES, MAX_NUM_SURFACE_TYPES, drivableSurfaceMaterials, drivableSurfaceTypes);
	for (PxU32 i = 0; i<MAX_NUM_SURFACE_TYPES; i++)
	{
		for (PxU32 j = 0; j<MAX_NUM_TIRE_TYPES; j++)
		{
			mSurfaceTirePairs->setTypePairFriction(i, j, gTireFrictionMultipliers[i][j]);
		}
	}

#ifdef PX_PS3 
	setSpuRaycastShader(mSqData);
#endif
}


static PxConvexMesh* CreateConvexMesh(const PxVec3* verts, const PxU32 numVerts, PxPhysics* physics, PxCooking* cooking) {
	// Create descriptor for convex mesh
	PxConvexMeshDesc convexDesc;
	convexDesc.points.count = numVerts;
	convexDesc.points.stride = sizeof(PxVec3);
	convexDesc.points.data = verts;
	convexDesc.flags = PxConvexFlag::eCOMPUTE_CONVEX | PxConvexFlag::eINFLATE_CONVEX;

	PxConvexMesh* convexMesh = NULL;
	PxToolkit::MemoryWriteBuffer buf;
	if (cooking->cookConvexMesh(convexDesc, buf))
		convexMesh = physics->createConvexMesh(PxToolkit::MemoryReadBuffer(buf.data));

	return convexMesh;

}

PxVehicleDrive4W *CarCreator::createCar(PxPhysics& topLevelPhysics, PxCooking& cooking, PxScene& scene,
	PxMaterial& mat) {

	PxConvexMesh* chassisCovexMesh = CreateConvexMesh(verts, numVerts, &topLevelPhysics, &cooking)
	create4WVehicle(scene, topLevelPhysics, cooking, mat, gChassisMass, &gWheelCentreOffsets4, chassisConvexMesh, gWheelConvexMeshes4, gPlayerCarStartTransforms[0], true);

	PxVehicleWheelsSimData* wheelsSimData = PxVehicleWheelsSimData::allocate(4);
	PxVehicleDriveSimData4W driveSimData;
	PxVehicleChassisData chassisData;
	createVehicle4WSimulationData
		(chassisMass, chassisConvexMesh,
		20.0f, wheelConvexMeshes4, wheelCentreOffsets4,
		*wheelsSimData, driveSimData, chassisData);
	PxRigidDynamic* vehActor = createVehicleActor4W(chassisData, wheelConvexMeshes4, chassisConvexMesh, scene, physics, material);
	PxVehicleDrive4W* car = PxVehicleDrive4W::allocate(4);
	car->setup(&physics, vehActor, *wheelsSimData, driveSimData, 0);
	car->mWheelsSimData.setWheelShapeMapping(0, 0);
	car->mWheelsSimData.setWheelShapeMapping(1, 1);
	car->mWheelsSimData.setWheelShapeMapping(2, 2);
	car->mWheelsSimData.setWheelShapeMapping(3, 3);

	PxFilterData vehQryFilterData;
	SampleVehicleSetupVehicleShapeQueryFilterData(&vehQryFilterData);
	car->mWheelsSimData.setSceneQueryFilterData(0, vehQryFilterData);
	car->mWheelsSimData.setSceneQueryFilterData(1, vehQryFilterData);
	car->mWheelsSimData.setSceneQueryFilterData(2, vehQryFilterData);
	car->mWheelsSimData.setSceneQueryFilterData(3, vehQryFilterData);

	return car;
}