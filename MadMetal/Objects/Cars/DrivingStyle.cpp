#include "DrivingStyle.h"

float DrivingStyle::getMaxSpeed()
{
	return m_maxSpeed;
}


float DrivingStyle::getChassisMass()
{
	return m_chassisMass;
}


PxVec3 DrivingStyle::getChassisDimensions()
{
	return m_chassisDims;
}


PxVec3 DrivingStyle::getChassisMOI()
{
	return m_chassisMOI;
}


PxVec3 DrivingStyle::getChassisCenterOfMassOffsset()
{
	return m_chassisCMOffset;
}


float DrivingStyle::getWheelMass()
{
	return m_wheelMass;
}


float DrivingStyle::getWheelRadius()
{
	return m_wheelRadius;
}


float DrivingStyle::getWheelWidth()
{
	return m_wheelWidth;
}


float DrivingStyle::getWheelMOI()
{
	return m_wheelMOI;
}


float DrivingStyle::getNbWheels()
{
	return m_nbWheels;
}


PxMaterial *DrivingStyle::getChassisMaterial() 
{
	return m_chassisMaterial;
}


PxMaterial *DrivingStyle::getWheelMaterial()
{
	return m_wheelMaterial;
}


PxReal DrivingStyle::getMaxBrakeTorque() {
	return m_maxBrakeTorque;
}


PxReal DrivingStyle::getMaxHandBrakeTorque() {
	return m_maxHandBrakeTorque;
}


PxReal DrivingStyle::getFrontWheelsMaxSteer() {
	return m_frontWheelsMaxSteer;
}


PxReal DrivingStyle::getEnginePeakTorque() {
	return m_enginePeakTorque;
}


PxReal DrivingStyle::getEngineMaxOmega() {
	return m_engineMaxOmega;
}


PxReal DrivingStyle::getGearsSwitchTime() {
	return m_gearsSwitchTime;
}


PxReal DrivingStyle::getClutchStrength() {
	return m_clutchStrength;
}


PxReal DrivingStyle::getSuspensionSpringStrength() {
	return m_suspensionSpringStrength;
}


PxReal DrivingStyle::getSuspensionSpringDamperRate() {
	return m_suspensionSpringDamperRate;
}


PxReal DrivingStyle::getSuspensionMaxCompression() {
	return m_suspensionMaxCompression;
}


PxReal DrivingStyle::getSuspensionMaxDroop() {
	return m_suspensionMaxDroop;
}


PxReal DrivingStyle::getSuspensionCamberAngleAtRest() {
	return m_suspensionCamberAngleAtRest;
}


PxReal DrivingStyle::getSuspensionCamberAngleAtMaxDroop() {
	return m_suspensionCamberAngleAtMaxDroop;
}

PxReal DrivingStyle::getSuspensionCamberAngleAtMaxCompression() {
	return m_suspensionCamberAngleAtMaxCompression;
}