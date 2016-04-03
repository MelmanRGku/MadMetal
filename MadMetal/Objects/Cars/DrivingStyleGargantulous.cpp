#include "DrivingStyleGargantulous.h"	

DrivingStyleGargantulous::DrivingStyleGargantulous(PxMaterial *chassisMaterial, PxMaterial *wheelMaterial)
{
	//Set up the chassis mass, dimensions, moment of inertia, and center of mass offset.
	//The moment of inertia is just the moment of inertia of a cuboid but modified for easier steering.
	//Center of mass offset is 0.65m above the base of the chassis and 0.25m towards the front.

	// For the record, Gargantulous has high health, standard speed, and low maneuvrebility
	m_chassisMass = 2500.0f;
	m_chassisDims = PxVec3(10.f, 5.0f, 10.0f);
	m_chassisMOI = PxVec3((m_chassisDims.y*m_chassisDims.y + m_chassisDims.z*m_chassisDims.z)*m_chassisMass / 12.0f,
		(m_chassisDims.x*m_chassisDims.x + m_chassisDims.z*m_chassisDims.z)*0.8f*m_chassisMass / 12.0f,
		(m_chassisDims.x*m_chassisDims.x + m_chassisDims.y*m_chassisDims.y)*m_chassisMass / 12.0f);
	m_chassisMOI.x *= 1.1;
	m_chassisMOI.z *= 1.2;
	m_chassisCMOffset = PxVec3(0.0f, -m_chassisDims.y*2.f, 0.0f);
	m_chassisMaterial = chassisMaterial;

	//Set up the wheel mass, radius, width, moment of inertia, and number of wheels.
	//Moment of inertia is just the moment of inertia of a cylinder.
	m_wheelMass = 20.0f;
	m_wheelRadius = 0.7f;
	m_wheelWidth = 0.6f;
	m_wheelMOI = 0.5f*m_wheelMass*m_wheelRadius*m_wheelRadius;
	m_wheelMaterial = wheelMaterial;
	m_nbWheels = 4;

	//handling variables
	m_maxSpeed = 100;
	m_maxBrakeTorque = 100000.f;
	m_maxHandBrakeTorque = 10000000.f;
	m_frontWheelsMaxSteer = PxPi*0.06666f;
	m_enginePeakTorque = 7000.0f;
	m_engineMaxOmega = 1000.0f;//approx 10000 rpm
	m_gearsSwitchTime = 0.1f;
	m_clutchStrength = 1000.0f;
	m_suspensionSpringStrength = 100000.0f;
	m_suspensionSpringDamperRate = 20000.0f;
	m_suspensionMaxCompression = 0.01f;
	m_suspensionMaxDroop = 0.1f;
	m_suspensionCamberAngleAtRest = 0.0;
	m_suspensionCamberAngleAtMaxDroop = 2.14;
	m_suspensionCamberAngleAtMaxCompression = -2.14;
}

DrivingStyleGargantulous::~DrivingStyleGargantulous()
{

}


