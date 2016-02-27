#pragma once
#include "DrivingStyle.h"

class DrivingStyleFast : public DrivingStyle
{
private:
	
public:
	DrivingStyleFast(PxMaterial *chassisMaterial, PxMaterial *wheelMaterial);
	virtual ~DrivingStyleFast();
};

