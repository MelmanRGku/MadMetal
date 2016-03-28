#include "DrivingStyle.h"

void DrivingStyle::setMaxSpeed(float maxSpeed)
{
	m_maxSpeed = maxSpeed;
}

float DrivingStyle::getMaxSpeed()
{
	return m_maxSpeed;
}

void DrivingStyle::setChassisMass(float mass)
{
	m_chassisMass = mass;
}


float DrivingStyle::getChassisMass()
{
	return m_chassisMass;
}


void DrivingStyle::setChassisDimensions(PxVec3 dimensions)
{
	m_chassisDims = dimensions;
}


PxVec3 DrivingStyle::getChassisDimensions()
{
	return m_chassisDims;
}


void DrivingStyle::setChassisMOI(PxVec3 moi)
{
	m_chassisMOI = moi;
}


PxVec3 DrivingStyle::getChassisMOI()
{
	return m_chassisMOI;
}


void DrivingStyle::setChassisCenterOfMassOffsset(PxVec3 mass)
{
	m_chassisCMOffset = mass;
}


PxVec3 DrivingStyle::getChassisCenterOfMassOffsset()
{
	return m_chassisCMOffset;
}


void DrivingStyle::setWheelMass(float mass)
{
	m_wheelMass = mass;
}


float DrivingStyle::getWheelMass()
{
	return m_wheelMass;
}


void DrivingStyle::setWheelRadius(float radius)
{
	m_wheelRadius = radius;
}


float DrivingStyle::getWheelRadius()
{
	return m_wheelRadius;
}


void DrivingStyle::setWheelWidth(float width)
{
	m_wheelWidth = width;
}


float DrivingStyle::getWheelWidth()
{
	return m_wheelWidth;
}


void DrivingStyle::setWheelMOI(float wheelMOI)
{
	m_wheelMOI = wheelMOI;
}


float DrivingStyle::getWheelMOI()
{
	return m_wheelMOI;
}


void DrivingStyle::setNbWheels(float numberOfWheels)
{
	m_nbWheels = numberOfWheels;
}


float DrivingStyle::getNbWheels()
{
	return m_nbWheels;
}


void DrivingStyle::setChassisMaterial(PxMaterial *material) 
{
	m_chassisMaterial = material;
}


PxMaterial *DrivingStyle::getChassisMaterial() 
{
	return m_chassisMaterial;
}


void DrivingStyle::setWheelMaterial(PxMaterial *material) 
{
	m_wheelMaterial = material;
}


PxMaterial *DrivingStyle::getWheelMaterial()
{
	return m_wheelMaterial;
}