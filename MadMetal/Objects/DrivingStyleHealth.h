#pragma once
#include "DrivingStyle.h"

class DrivingStyleHealth : public DrivingStyle
{
private:

public:
	DrivingStyleHealth(PxMaterial *chassisMaterial, PxMaterial *wheelMaterial);
	virtual ~DrivingStyleHealth();
};

