#include "DrivingStyleMeowMix.h"	

DrivingStyleMeowMix::DrivingStyleMeowMix()
{
	//Set up the chassis mass, dimensions, moment of inertia, and center of mass offset.
	//The moment of inertia is just the moment of inertia of a cuboid but modified for easier steering.
	//Center of mass offset is 0.65m above the base of the chassis and 0.25m towards the front.

	//For the record, MeowMix has high maneuverability, standard speed, and low health
	m_chassisMass = 1500.0f;
	m_chassisDims = PxVec3(5.0f, 7.0f, 7.0f);
	m_chassisMOI = PxVec3(0,
		(m_chassisDims.x*m_chassisDims.x + m_chassisDims.z*m_chassisDims.z)*m_chassisMass / 12.0f,
		0);
	m_chassisCMOffset = PxVec3(0.0f, -m_chassisDims.y*0.5f, 0.0f);
	m_chassisMaterial = PhysicsManager::createMaterial(0.5f, 0.3f, 0.1f);

	//Set up the wheel mass, radius, width, moment of inertia, and number of wheels.
	//Moment of inertia is just the moment of inertia of a cylinder.
	m_wheelMass = 20.0f;
	m_wheelRadius = 0.7f;
	m_wheelWidth = 0.6f;
	m_wheelMOI = 0.5f*m_wheelMass*m_wheelRadius*m_wheelRadius;
	m_backWheelMaterial = PhysicsManager::createMaterial(0.0f, 0.0f, 1.f);
	m_frontWheelMaterial = PhysicsManager::createMaterial(0.5f, 0.3f, 0.3f);
	m_nbWheels = 4;

	//handling variables
	m_maxSpeed = 90;
	m_maxBrakeTorque = 1000.f;
	m_maxHandBrakeTorque = 100000.f;
	m_frontWheelsMaxSteer = PxPi*0.06666f;
	m_enginePeakTorque = 8000.0f;
	m_engineMaxOmega = 1500.0f;//approx 10000 rpm
	m_gearsSwitchTime = 0.1f;
	m_clutchStrength = 20.0f;
	m_suspensionSpringStrength = 300.0f; // !
	m_suspensionSpringDamperRate = 30000.0f;
	m_suspensionMaxCompression = 2.5f;
	m_suspensionMaxDroop = 3.0f;
	m_suspensionCamberAngleAtRest = 0.0;
	m_suspensionCamberAngleAtMaxDroop = 2.14;
	m_suspensionCamberAngleAtMaxCompression = -2.14;

	m_frontTireType = TIRE_TYPE_FRONT_MEOWMIX;
	m_backTireType = TIRE_TYPE_BACK_MEOWMIX;
}

DrivingStyleMeowMix::~DrivingStyleMeowMix()
{

}


