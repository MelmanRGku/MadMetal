#include "VehicleCreator.h"


VehicleCreator::VehicleCreator(PxPhysics *physics, PxCooking *cooking)
{
	this->physics = physics;
	this->cooking = cooking;
}


VehicleCreator::~VehicleCreator()
{
}

PxVehicleDrive4W* VehicleCreator::create(DrivingStyle* style)
{
	const PxVec3 chassisDims = style->getChassisDimensions();
	const PxF32 wheelWidth = style->getWheelWidth();
	const PxF32 wheelRadius = style->getWheelRadius();
	const PxU32 numWheels = style->getNbWheels();

	//Construct a physx actor with shapes for the chassis and wheels.
	//Set the rigid body mass, moment of inertia, and center of mass offset.
	PxRigidDynamic* veh4WActor = NULL;
	{

		PhysicsObjectCreator *physicsObjectCreator = new PhysicsObjectCreator(physics, cooking);

		//Construct a convex mesh for a cylindrical wheel.
		PxConvexMesh* wheelMesh = physicsObjectCreator->createWheelMesh(wheelWidth, wheelRadius);
		//Assume all wheels are identical for simplicity.
		PxConvexMesh* wheelConvexMeshes[PX_MAX_NB_WHEELS];
		PxMaterial* wheelMaterials[PX_MAX_NB_WHEELS];

		//Set the meshes and materials for the driven wheels.
		for (PxU32 i = PxVehicleDrive4WWheelOrder::eFRONT_LEFT; i <= PxVehicleDrive4WWheelOrder::eREAR_RIGHT; i++)
		{
			wheelConvexMeshes[i] = wheelMesh;
			wheelMaterials[i] = style->getWheelMaterial();
		}
		//Set the meshes and materials for the non-driven wheels
		for (PxU32 i = PxVehicleDrive4WWheelOrder::eREAR_RIGHT + 1; i < numWheels; i++)
		{
			wheelConvexMeshes[i] = wheelMesh;
			wheelMaterials[i] = style->getWheelMaterial();
		}

		//Chassis just has a single convex shape for simplicity.
		PxConvexMesh* chassisConvexMesh = physicsObjectCreator->createChassisMesh(chassisDims);
		PxConvexMesh* chassisConvexMeshes[1] = { chassisConvexMesh };
		PxMaterial* chassisMaterials[1] = { style->getChassisMaterial() };

		//Rigid body data.
		PxVehicleChassisData rigidBodyData;
		rigidBodyData.mMOI = style->getChassisMOI();
		rigidBodyData.mMass = style->getChassisMass();
		rigidBodyData.mCMOffset = style->getChassisCenterOfMassOffsset();

		veh4WActor = physicsObjectCreator->createVehicleActor
			(rigidBodyData,
			wheelMaterials, wheelConvexMeshes, numWheels,
			chassisMaterials, chassisConvexMeshes, 1);
	}

	//Set up the sim data for the wheels.
	PxVehicleWheelsSimData* wheelsSimData = PxVehicleWheelsSimData::allocate(numWheels);
	{
		//Compute the wheel center offsets from the origin.
		PxVec3 wheelCenterActorOffsets[PX_MAX_NB_WHEELS];
		const PxF32 frontZ = chassisDims.z*0.3f;
		const PxF32 rearZ = -chassisDims.z*0.3f;
		computeWheelCenterActorOffsets4W(style, frontZ, rearZ, wheelCenterActorOffsets);

		//Set up the simulation data for all wheels.
		setupWheelsSimulationData(style, wheelCenterActorOffsets, wheelsSimData);
	}

	//Set up the sim data for the vehicle drive model.
	PxVehicleDriveSimData4W driveSimData;
	{
		//Diff
		PxVehicleDifferential4WData diff;
		diff.mType = PxVehicleDifferential4WData::eDIFF_TYPE_LS_4WD;
		driveSimData.setDiffData(diff);

		//Engine
		PxVehicleEngineData engine;
		engine.mPeakTorque = 7000.0f;
		engine.mMaxOmega = 1000.0f;//approx 10000 rpm
		driveSimData.setEngineData(engine);

		//Gears
		PxVehicleGearsData gears;
		gears.mSwitchTime = 0.5f;
		driveSimData.setGearsData(gears);

		//Clutch
		PxVehicleClutchData clutch;
		clutch.mStrength = 10.0f;
		driveSimData.setClutchData(clutch);

		//Ackermann steer accuracy
		PxVehicleAckermannGeometryData ackermann;
		ackermann.mAccuracy = 1.0f;
		ackermann.mAxleSeparation =
			wheelsSimData->getWheelCentreOffset(PxVehicleDrive4WWheelOrder::eFRONT_LEFT).z -
			wheelsSimData->getWheelCentreOffset(PxVehicleDrive4WWheelOrder::eREAR_LEFT).z;
		ackermann.mFrontWidth =
			wheelsSimData->getWheelCentreOffset(PxVehicleDrive4WWheelOrder::eFRONT_RIGHT).x -
			wheelsSimData->getWheelCentreOffset(PxVehicleDrive4WWheelOrder::eFRONT_LEFT).x;
		ackermann.mRearWidth =
			wheelsSimData->getWheelCentreOffset(PxVehicleDrive4WWheelOrder::eREAR_RIGHT).x -
			wheelsSimData->getWheelCentreOffset(PxVehicleDrive4WWheelOrder::eREAR_LEFT).x;
		driveSimData.setAckermannGeometryData(ackermann);
	}

	//Create a vehicle from the wheels and drive sim data.
	PxVehicleDrive4W* vehDrive4W = PxVehicleDrive4W::allocate(numWheels);
	vehDrive4W->setup(physics, veh4WActor, *wheelsSimData, driveSimData, numWheels - 4);

	//Free the sim data because we don't need that any more.
	wheelsSimData->free();

	return vehDrive4W;
}

void VehicleCreator::setupWheelsSimulationData(DrivingStyle* style, const PxVec3* wheelCenterActorOffsets, PxVehicleWheelsSimData* wheelsSimData)
{
	//Set up the wheels.
	PxVehicleWheelData wheels[PX_MAX_NB_WHEELS];
	{
		//Set up the wheel data structures with mass, moi, radius, width.
		for (PxU32 i = 0; i < style->getNbWheels(); i++)
		{
			wheels[i].mMass = style->getWheelMass();
			wheels[i].mMOI = style->getWheelMOI();
			wheels[i].mRadius = style->getWheelRadius();
			wheels[i].mWidth = style->getWheelWidth();
		
		}

		//Enable the handbrake for the rear wheels only.
		wheels[PxVehicleDrive4WWheelOrder::eREAR_LEFT].mMaxHandBrakeTorque = 25000.0f;
		wheels[PxVehicleDrive4WWheelOrder::eREAR_RIGHT].mMaxHandBrakeTorque = 25000.0f;
		//Enable steering for the front wheels only.
		wheels[PxVehicleDrive4WWheelOrder::eFRONT_LEFT].mMaxSteer = PxPi*0.06666f / 2;
		wheels[PxVehicleDrive4WWheelOrder::eFRONT_RIGHT].mMaxSteer = PxPi*0.06666f /2;
		wheels[PxVehicleDrive4WWheelOrder::eREAR_LEFT].mMaxSteer = 0;
		wheels[PxVehicleDrive4WWheelOrder::eREAR_RIGHT].mMaxSteer = 0;
		//wheels[PxVehicleDrive4WWheelOrder::eFRONT_LEFT].mToeAngle = -1.0 / (2 * 3.14);
		//wheels[PxVehicleDrive4WWheelOrder::eFRONT_RIGHT].mToeAngle = 1.0 / (2 * 3.14);
	}

	//Set up the tires.
	PxVehicleTireData tires[PX_MAX_NB_WHEELS];
	{
		//Set up the tires.
		for (PxU32 i = 0; i < style->getNbWheels(); i++)
		{
			tires[i].mType = TIRE_TYPE_NORMAL;
		}
	}

	//Set up the suspensions
	PxVehicleSuspensionData suspensions[PX_MAX_NB_WHEELS];
	{
		//Compute the mass supported by each suspension spring.
		PxF32 suspSprungMasses[PX_MAX_NB_WHEELS];
		PxVehicleComputeSprungMasses
			(style->getNbWheels(), wheelCenterActorOffsets,
			style->getChassisCenterOfMassOffsset(), style->getChassisMass(), 1, suspSprungMasses);

		//Set the suspension data.
		for (PxU32 i = 0; i < style->getNbWheels(); i++)
		{
			suspensions[i].mMaxCompression = 0.1f;
			suspensions[i].mMaxDroop = 0.1f;
			suspensions[i].mSpringStrength = 150000.0f;
			suspensions[i].mSpringDamperRate = 20000.0f;
			suspensions[i].mSprungMass = suspSprungMasses[i];
		}

		//Set the camber angles.
		const PxF32 camberAngleAtRest = 0.0;
		const PxF32 camberAngleAtMaxDroop = 2.14;
		const PxF32 camberAngleAtMaxCompression = -2.14;
		for (PxU32 i = 0; i < style->getNbWheels(); i += 2)
		{
			suspensions[i + 0].mCamberAtRest = camberAngleAtRest;
			suspensions[i + 1].mCamberAtRest = -camberAngleAtRest;
			suspensions[i + 0].mCamberAtMaxDroop = camberAngleAtMaxDroop;
			suspensions[i + 1].mCamberAtMaxDroop = -camberAngleAtMaxDroop;
			suspensions[i + 0].mCamberAtMaxCompression = camberAngleAtMaxCompression;
			suspensions[i + 1].mCamberAtMaxCompression = -camberAngleAtMaxCompression;
		}
	}

	//Set up the wheel geometry.
	PxVec3 suspTravelDirections[PX_MAX_NB_WHEELS];
	PxVec3 wheelCentreCMOffsets[PX_MAX_NB_WHEELS];
	PxVec3 suspForceAppCMOffsets[PX_MAX_NB_WHEELS];
	PxVec3 tireForceAppCMOffsets[PX_MAX_NB_WHEELS];
	{
		//Set the geometry data.
		for (PxU32 i = 0; i < style->getNbWheels(); i++)
		{

			//Wheel center offset is offset from rigid body center of mass.
			wheelCentreCMOffsets[i] =
				wheelCenterActorOffsets[i] - style->getChassisCenterOfMassOffsset();

			//Suspension force application point 0.3 metres below 
			//rigid body center of mass.
			suspForceAppCMOffsets[i] =
				PxVec3(wheelCentreCMOffsets[i].x, -0.3f, wheelCentreCMOffsets[i].z);	

			//Tire force application point 0.3 metres below 
			//rigid body center of mass.
			tireForceAppCMOffsets[i] =
				PxVec3(wheelCentreCMOffsets[i].x, -0.3f, wheelCentreCMOffsets[i].z);
		}
#define WHEEL_Z_ROTATION 0.15
		//Vertical suspension travel.
		suspTravelDirections[PxVehicleDrive4WWheelOrder::eREAR_LEFT] = PxVec3(-WHEEL_Z_ROTATION, -1, 0).getNormalized();
		suspTravelDirections[PxVehicleDrive4WWheelOrder::eREAR_RIGHT] = PxVec3(WHEEL_Z_ROTATION, -1, 0).getNormalized();
		suspTravelDirections[PxVehicleDrive4WWheelOrder::eFRONT_LEFT] = PxVec3(-WHEEL_Z_ROTATION, -1, 0).getNormalized();
		suspTravelDirections[PxVehicleDrive4WWheelOrder::eFRONT_RIGHT] = PxVec3(WHEEL_Z_ROTATION, -1, 0).getNormalized();
	}

	//Set up the filter data of the raycast that will be issued by each suspension.
	PxFilterData qryFilterData;
	setupNonDrivableSurface(qryFilterData);

	//Set the wheel, tire and suspension data.
	//Set the geometry data.
	//Set the query filter data
	for (PxU32 i = 0; i < style->getNbWheels(); i++)
	{
		wheelsSimData->setWheelData(i, wheels[i]);
		wheelsSimData->setTireData(i, tires[i]);
		wheelsSimData->setSuspensionData(i, suspensions[i]);
		wheelsSimData->setSuspTravelDirection(i, suspTravelDirections[i]);
		wheelsSimData->setWheelCentreOffset(i, wheelCentreCMOffsets[i]);
		wheelsSimData->setSuspForceAppPointOffset(i, suspForceAppCMOffsets[i]);
		wheelsSimData->setTireForceAppPointOffset(i, tireForceAppCMOffsets[i]);
		wheelsSimData->setSceneQueryFilterData(i, qryFilterData);
		wheelsSimData->setWheelShapeMapping(i, i);
	}
}


void VehicleCreator::computeWheelCenterActorOffsets4W(DrivingStyle *style, const PxF32 wheelFrontZ, const PxF32 wheelRearZ, PxVec3* wheelCentreOffsets)
{
	//chassisDims.z is the distance from the rear of the chassis to the front of the chassis.
	//The front has z = 0.5*chassisDims.z and the rear has z = -0.5*chassisDims.z.
	//Compute a position for the front wheel and the rear wheel along the z-axis.
	//Compute the separation between each wheel along the z-axis.
	const PxF32 numLeftWheels = style->getNbWheels() / 2.0f;
	const PxF32 deltaZ = (wheelFrontZ - wheelRearZ) / (numLeftWheels - 1.0f);
	//Set the outside of the left and right wheels to be flush with the chassis.
	//Set the top of the wheel to be just touching the underside of the chassis.
	//Begin by setting the rear-left/rear-right/front-left,front-right wheels.
	wheelCentreOffsets[PxVehicleDrive4WWheelOrder::eREAR_LEFT] = PxVec3((-style->getChassisDimensions().x + style->getWheelWidth())*0.5f, -(style->getChassisDimensions().y / 2 + style->getWheelRadius()), wheelRearZ + 0 * deltaZ*0.5f);
	wheelCentreOffsets[PxVehicleDrive4WWheelOrder::eREAR_RIGHT] = PxVec3((+style->getChassisDimensions().x - style->getWheelWidth())*0.5f, -(style->getChassisDimensions().y / 2 + style->getWheelRadius()), wheelRearZ + 0 * deltaZ*0.5f);
	wheelCentreOffsets[PxVehicleDrive4WWheelOrder::eFRONT_LEFT] = PxVec3((-style->getChassisDimensions().x + style->getWheelWidth())*0.5f, -(style->getChassisDimensions().y / 2 + style->getWheelRadius()), wheelRearZ + (numLeftWheels - 1)*deltaZ);
	wheelCentreOffsets[PxVehicleDrive4WWheelOrder::eFRONT_RIGHT] = PxVec3((+style->getChassisDimensions().x - style->getWheelWidth())*0.5f, -(style->getChassisDimensions().y / 2 + style->getWheelRadius()), wheelRearZ + (numLeftWheels - 1)*deltaZ);
	//Set the remaining wheels.
	for (PxU32 i = 2, wheelCount = 4; i < style->getNbWheels() - 2; i += 2, wheelCount += 2)
	{
		wheelCentreOffsets[wheelCount + 0] = PxVec3((-style->getChassisDimensions().x + style->getWheelWidth())*0.5f, -(style->getChassisDimensions().y / 2 + style->getWheelRadius()), wheelRearZ + i*deltaZ*0.5f);
		wheelCentreOffsets[wheelCount + 1] = PxVec3((+style->getChassisDimensions().x - style->getWheelWidth())*0.5f, -(style->getChassisDimensions().y / 2 + style->getWheelRadius()), wheelRearZ + i*deltaZ*0.5f);
	}
}