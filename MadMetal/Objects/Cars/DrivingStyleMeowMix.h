#pragma once
#include "DrivingStyle.h"

class DrivingStyleMeowMix : public DrivingStyle
{
private:
	
public:
	DrivingStyleMeowMix(PxMaterial *chassisMaterial, PxMaterial *wheelMaterial);
	virtual ~DrivingStyleMeowMix();
};

