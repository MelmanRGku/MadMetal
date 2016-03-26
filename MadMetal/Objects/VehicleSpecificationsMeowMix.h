#pragma once
#include "VehicleSpecifications.h"

class VehicleSpecificationsMeowMix : public VehicleSpecifications
{
private:
	
public:
	VehicleSpecificationsMeowMix(PxMaterial *chassisMaterial, PxMaterial *wheelMaterial);
	virtual ~VehicleSpecificationsMeowMix();
};

