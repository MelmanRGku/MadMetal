#pragma once
#include "Simulation\PhysicsManager.h"

class DrivingStyle
{
public:
	DrivingStyle() {};
	virtual ~DrivingStyle() {};
	
	virtual void setChassisMass(float mass) = 0;
	virtual float getChassisMass() = 0;
	virtual void setChassisDimensions(PxVec3 dimensions) = 0;
	virtual PxVec3 getChassisDimensions() = 0;
	virtual void setChassisMOI(PxVec3 moi) = 0;
	virtual PxVec3 getChassisMOI() = 0;
	virtual void setChassisCenterOfMassOffsset(PxVec3 mass) = 0;
	virtual PxVec3 getChassisCenterOfMassOffsset() = 0;
	virtual void setWheelMass(float mass) = 0;
	virtual float getWheelMass() = 0;
	virtual void setWheelRadius(float radius) = 0;
	virtual float getWheelRadius() = 0;	
	virtual void setWheelWidth(float width) = 0;
	virtual float getWheelWidth() = 0;	
	virtual void setWheelMOI(float wheelMOI) = 0;
	virtual float getWheelMOI() = 0;	
	virtual void setNbWheels(float numberOfWheels) = 0;
	virtual float getNbWheels() = 0;	

};

