#include "DrivingStyleFast.h"	

	DrivingStyleFast::DrivingStyleFast()
	{
		//Set up the chassis mass, dimensions, moment of inertia, and center of mass offset.
		//The moment of inertia is just the moment of inertia of a cuboid but modified for easier steering.
		//Center of mass offset is 0.65m above the base of the chassis and 0.25m towards the front.
		m_chassisMass = 1500.0f;
		m_chassisDims = PxVec3(4.f, 2.0f, 7.0f);
		m_chassisMOI = PxVec3((m_chassisDims.y*m_chassisDims.y + m_chassisDims.z*m_chassisDims.z)*m_chassisMass / 12.0f,
			                  (m_chassisDims.x*m_chassisDims.x + m_chassisDims.z*m_chassisDims.z)*0.8f*m_chassisMass / 12.0f,
			                  (m_chassisDims.x*m_chassisDims.x + m_chassisDims.y*m_chassisDims.y)*m_chassisMass / 12.0f);
		m_chassisCMOffset = PxVec3(0.0f, -m_chassisDims.y*0.5f, 0.0f);

		//Set up the wheel mass, radius, width, moment of inertia, and number of wheels.
		//Moment of inertia is just the moment of inertia of a cylinder.
		m_wheelMass = 20.0f;
		m_wheelRadius = 0.7f;
		m_wheelWidth = 0.6f;
		m_wheelMOI = 0.5f*m_wheelMass*m_wheelRadius*m_wheelRadius;
		m_nbWheels = 4;
	}

	DrivingStyleFast::~DrivingStyleFast()
	{
		
	}

	void DrivingStyleFast::setChassisMass(float mass)
	{
		m_chassisMass = mass;	
	}
	float DrivingStyleFast::getChassisMass()
	{
		return m_chassisMass;
	}
	void DrivingStyleFast::setChassisDimensions(PxVec3 dimensions)
	{
		m_chassisDims = dimensions;
	}
	PxVec3 DrivingStyleFast::getChassisDimensions()
	{
		return m_chassisDims;
	}
	void DrivingStyleFast::setChassisMOI(PxVec3 moi)
	{
		m_chassisMOI = moi;
	}
	PxVec3 DrivingStyleFast::getChassisMOI()
	{
		return m_chassisMOI;
	}
	void DrivingStyleFast::setChassisCenterOfMassOffsset(PxVec3 mass)
	{
		m_chassisCMOffset = mass;
	}
	PxVec3 DrivingStyleFast::getChassisCenterOfMassOffsset()
	{
		return m_chassisCMOffset;
	}
	void DrivingStyleFast::setWheelMass(float mass)
	{
		m_wheelMass = mass;
	}
	float DrivingStyleFast::getWheelMass()
	{
		return m_wheelMass;
	}
	void DrivingStyleFast::setWheelRadius(float radius)
	{
		m_wheelRadius = radius;
	}
	float DrivingStyleFast::getWheelRadius()
	{
		return m_wheelRadius;
	}
	void DrivingStyleFast::setWheelWidth(float width)
	{
		m_wheelWidth = width;
	}
	float DrivingStyleFast::getWheelWidth()
	{
		return m_wheelWidth;
	}
	void DrivingStyleFast::setWheelMOI(float wheelMOI)
	{
		m_wheelMOI = wheelMOI;
	}
	float DrivingStyleFast::getWheelMOI()
	{
		return m_wheelMOI;
	}
	void DrivingStyleFast::setNbWheels(float numberOfWheels)
	{
		m_nbWheels = numberOfWheels;
	}
	float DrivingStyleFast::getNbWheels()
	{
		return m_nbWheels;
	}
