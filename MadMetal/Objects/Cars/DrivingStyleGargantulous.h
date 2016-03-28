#pragma once
#include "DrivingStyle.h"

class DrivingStyleGargantulous : public DrivingStyle
{
private:

public:
	DrivingStyleGargantulous(PxMaterial *chassisMaterial, PxMaterial *wheelMaterial);
	virtual ~DrivingStyleGargantulous();
};

