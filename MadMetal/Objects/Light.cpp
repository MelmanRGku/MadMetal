#include "Light.h"
#include "Object3D.h"

Light::Light(long id, Animatable *anable) : TestObject(id, NULL, anable, NULL)
{ 
	constantValueDirection = 1;
	linearValueDirection = 1;
	quadValueDirection = 1;
	cutoffValueDirection = 1;
}

bool Light::getParentHasToBeDeleted() {
	return false;
}

void Light::setConstantPulsation(float min, float max, float time) {
	constantPulsationEnabled = true;
	minConstantValue = min;
	maxConstantValue = max;
	constantPulsationTime = time;
}

void Light::setLinearPulsation(float min, float max, float time){
	linearPulsationEnabled = true;
	minLinearValue = min;
	maxLinearValue = max;
	linearPulsationTime = time;
}

void Light::setQuadPulsation(float min, float max, float time){
	quadPulsationEnabled = true;
	minQuadValue = min;
	maxQuadValue = max;
	quadPulsationTime = time;
}

void Light::setCutoffPulsation(float min, float max, float time){
	cutoffPulsationEnabled = true;
	minCutoffValue = min;
	maxCutoffValue = max;
	cutoffPulsationTime = time;
}


void Light::processContantPulsation(float dt) {
	float delta = (maxConstantValue - minConstantValue) * dt / constantPulsationTime;
	constant = constant + delta * constantValueDirection;

	if (constant > maxConstantValue) {
		constantValueDirection = -1;
	}
	else if (constant < minConstantValue) {
		constantValueDirection = 1;
	}
}

void Light::processLinearPulsation(float dt) {
	float delta = (maxLinearValue - minLinearValue) * dt / linearPulsationTime;
	linear = linear + delta * linearValueDirection;

	if (linear > maxLinearValue) {
		linearValueDirection = -1;
	}
	else if (linear < minLinearValue) {
		linearValueDirection = 1;
	}
}

void Light::processQuadPulsation(float dt) {
	float delta = (maxQuadValue - minQuadValue) * dt / quadPulsationTime;
	quad = quad + delta * quadValueDirection;

	if (quad > maxQuadValue) {
		quadValueDirection = -1;
	}
	else if (quad < minQuadValue) {
		quadValueDirection = 1;
	}
}

void Light::processCutoffPulsation(float dt) {
	float delta = (maxCutoffValue - minCutoffValue) * dt / cutoffPulsationTime;
	cutoff = cutoff + delta * cutoffValueDirection;

	if (cutoff > maxCutoffValue) {
		cutoffValueDirection = -1;
	}
	else if (cutoff < minCutoffValue) {
		cutoffValueDirection = 1;
	}
}

void Light::update(float dt) { 
	TestObject::update(dt); 
	if (constantPulsationEnabled)
		processContantPulsation(dt);
	if (linearPulsationEnabled)
		processLinearPulsation(dt);
	if (quadPulsationEnabled)
		processQuadPulsation(dt);
	if (cutoffPulsationEnabled)
		processCutoffPulsation(dt);
}