#pragma once

#include "Libraries\glew\glew.h"
#include "Libraries\glm\vec3.hpp"
#include "TestObject.h"

class Light : public TestObject
{
protected:
	bool constantPulsationEnabled,
		linearPulsationEnabled,
		quadPulsationEnabled,
		cutoffPulsationEnabled;

	float minConstantValue,
		minLinearValue,
		minQuadValue,
		minCutoffValue;

	float maxConstantValue,
		maxLinearValue,
		maxQuadValue,
		maxCutoffValue;

	float constantPulsationTime,
		linearPulsationTime,
		quadPulsationTime,
		cutoffPulsationTime;

	//-1 or 1
	int constantValueDirection,
		linearValueDirection,
		quadValueDirection,
		cutoffValueDirection;

	void processContantPulsation(float dt);
	void processLinearPulsation(float dt);
	void processQuadPulsation(float dt);
	void processCutoffPulsation(float dt);

public:
	Light(long id, Animatable *anable);

	virtual void update(float dt);
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) { return false; }
	glm::mat4x4 getModelMatrix(){ return glm::mat4x4(); }
	void playSound(){}
	
	glm::vec3 colour;
	GLfloat cutoff;

	GLfloat constant;
	GLfloat linear;
	GLfloat quad;
	
	virtual bool getParentHasToBeDeleted();
	void setConstantPulsation(float min, float max, float time);
	void setLinearPulsation(float min, float max, float time);
	void setQuadPulsation(float min, float max, float time);
	void setCutoffPulsation(float min, float max, float time);
	
};