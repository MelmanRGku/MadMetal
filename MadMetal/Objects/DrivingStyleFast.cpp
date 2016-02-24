#include "DrivingStyleFast.h"	

	DrivingStyleFast::DrivingStyleFast()
	{
		//Set up the chassis mass, dimensions, moment of inertia, and center of mass offset.
		//The moment of inertia is just the moment of inertia of a cuboid but modified for easier steering.
		//Center of mass offset is 0.65m above the base of the chassis and 0.25m towards the front.
		m_chassisMass = 500.0f;
		m_chassisDims = PxVec3(2.5f, 2.0f, 5.0f);
		m_chassisMOI = PxVec3((m_chassisDims.y*m_chassisDims.y + m_chassisDims.z*m_chassisDims.z)*m_chassisMass / 12.0f,
			                  (m_chassisDims.x*m_chassisDims.x + m_chassisDims.z*m_chassisDims.z)*0.8f*m_chassisMass / 12.0f,
			                  (m_chassisDims.x*m_chassisDims.x + m_chassisDims.y*m_chassisDims.y)*m_chassisMass / 12.0f);
		m_chassisCMOffset = PxVec3(0.0f, -m_chassisDims.y*0.5f + 0.65f, 0.25f);

		//Set up the wheel mass, radius, width, moment of inertia, and number of wheels.
		//Moment of inertia is just the moment of inertia of a cylinder.
		m_wheelMass = 20.0f;
		m_wheelRadius = 0.5f;
		m_wheelWidth = 0.4f;
		m_wheelMOI = 0.5f*m_wheelMass*m_wheelRadius*m_wheelRadius;
		m_nbWheels = 6;
	}

	DrivingStyleFast::~DrivingStyleFast()
	{
		
	}

	