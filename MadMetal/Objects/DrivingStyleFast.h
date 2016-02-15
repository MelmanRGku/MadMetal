#pragma once
#include "DrivingStyle.h"

class DrivingStyleFast : public DrivingStyle
{
private:
	
public:
	DrivingStyleFast();
	virtual ~DrivingStyleFast();

	void setChassisMass(float mass);
	float getChassisMass();
	void setChassisDimensions(PxVec3 dimensions);
	PxVec3 getChassisDimensions();
	void setChassisMOI(PxVec3 moi);
	PxVec3 getChassisMOI();
	void setChassisCenterOfMassOffsset(PxVec3 mass);
	PxVec3 getChassisCenterOfMassOffsset();
	void setWheelMass(float mass);
	float getWheelMass();
	void setWheelRadius(float radius);
	float getWheelRadius();	
	void setWheelWidth(float width);
	float getWheelWidth();	
	void setWheelMOI(float wheelMOI);
	float getWheelMOI();	
	void setNbWheels(float numberOfWheels);
	float getNbWheels();	

private: //members
	float m_chassisMass;
	PxVec3 m_chassisDims;
	PxVec3 m_chassisMOI;
	PxVec3 m_chassisCMOffset;
	float m_wheelMass;
	float m_wheelRadius;
	float m_wheelWidth;
	float m_wheelMOI;
	float m_nbWheels;
};

