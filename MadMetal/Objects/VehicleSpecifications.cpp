#include "VehicleSpecifications.h"

void VehicleSpecifications::setChassisMass(float mass)
{
	m_chassisMass = mass;
}


float VehicleSpecifications::getChassisMass()
{
	return m_chassisMass;
}


void VehicleSpecifications::setChassisDimensions(PxVec3 dimensions)
{
	m_chassisDims = dimensions;
}


PxVec3 VehicleSpecifications::getChassisDimensions()
{
	return m_chassisDims;
}


void VehicleSpecifications::setChassisMOI(PxVec3 moi)
{
	m_chassisMOI = moi;
}


PxVec3 VehicleSpecifications::getChassisMOI()
{
	return m_chassisMOI;
}


void VehicleSpecifications::setChassisCenterOfMassOffsset(PxVec3 mass)
{
	m_chassisCMOffset = mass;
}


PxVec3 VehicleSpecifications::getChassisCenterOfMassOffsset()
{
	return m_chassisCMOffset;
}


void VehicleSpecifications::setWheelMass(float mass)
{
	m_wheelMass = mass;
}


float VehicleSpecifications::getWheelMass()
{
	return m_wheelMass;
}


void VehicleSpecifications::setWheelRadius(float radius)
{
	m_wheelRadius = radius;
}


float VehicleSpecifications::getWheelRadius()
{
	return m_wheelRadius;
}


void VehicleSpecifications::setWheelWidth(float width)
{
	m_wheelWidth = width;
}


float VehicleSpecifications::getWheelWidth()
{
	return m_wheelWidth;
}


void VehicleSpecifications::setWheelMOI(float wheelMOI)
{
	m_wheelMOI = wheelMOI;
}


float VehicleSpecifications::getWheelMOI()
{
	return m_wheelMOI;
}


void VehicleSpecifications::setNbWheels(float numberOfWheels)
{
	m_nbWheels = numberOfWheels;
}


float VehicleSpecifications::getNbWheels()
{
	return m_nbWheels;
}


void VehicleSpecifications::setChassisMaterial(PxMaterial *material) 
{
	m_chassisMaterial = material;
}


PxMaterial *VehicleSpecifications::getChassisMaterial() 
{
	return m_chassisMaterial;
}


void VehicleSpecifications::setWheelMaterial(PxMaterial *material) 
{
	m_wheelMaterial = material;
}


PxMaterial *VehicleSpecifications::getWheelMaterial()
{
	return m_wheelMaterial;
}