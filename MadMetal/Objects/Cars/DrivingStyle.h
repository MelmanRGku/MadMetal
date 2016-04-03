#pragma once
#include "Simulation\PhysicsManager.h"

class DrivingStyle
{
public:
	DrivingStyle() {};
	virtual ~DrivingStyle() {};

	float getChassisMass();
	PxVec3 getChassisDimensions();
	PxVec3 getChassisMOI();
	PxVec3 getChassisCenterOfMassOffsset();
	float getWheelMass();
	float getWheelRadius();
	float getWheelWidth();
	float getWheelMOI();
	float getNbWheels();
	PxMaterial *getChassisMaterial();
	PxMaterial *getWheelMaterial();
	float getMaxSpeed();
	PxReal getMaxBrakeTorque();
	PxReal getMaxHandBrakeTorque();
	PxReal getFrontWheelsMaxSteer();
	PxReal getEnginePeakTorque();
	PxReal getEngineMaxOmega();
	PxReal getGearsSwitchTime();
	PxReal getClutchStrength();
	PxReal getSuspensionSpringStrength();
	PxReal getSuspensionSpringDamperRate();
	PxReal getSuspensionMaxCompression();
	PxReal getSuspensionMaxDroop();
	PxReal getSuspensionCamberAngleAtRest();
	PxReal getSuspensionCamberAngleAtMaxDroop();
	PxReal getSuspensionCamberAngleAtMaxCompression();

protected: //members
	float m_chassisMass;
	PxVec3 m_chassisDims;
	PxVec3 m_chassisMOI;
	PxVec3 m_chassisCMOffset;
	float m_wheelMass;
	float m_wheelRadius;
	float m_wheelWidth;
	float m_wheelMOI;
	float m_nbWheels;
	float m_maxSpeed;
	PxMaterial* m_chassisMaterial;
	PxMaterial* m_wheelMaterial;
	PxReal m_maxBrakeTorque;
	PxReal m_maxHandBrakeTorque;
	PxReal m_frontWheelsMaxSteer;
	PxReal m_enginePeakTorque;
	PxReal m_engineMaxOmega;
	PxReal m_gearsSwitchTime;
	PxReal m_clutchStrength;
	PxReal m_suspensionSpringStrength;
	PxReal m_suspensionSpringDamperRate;
	PxReal m_suspensionMaxCompression;
	PxReal m_suspensionMaxDroop;
	PxReal m_suspensionCamberAngleAtRest;
	PxReal m_suspensionCamberAngleAtMaxDroop;
	PxReal m_suspensionCamberAngleAtMaxCompression;

};

