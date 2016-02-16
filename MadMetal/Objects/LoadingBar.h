#pragma once

#include "RenderableObject.h"

class LoadingBar : public RenderableObject
{
private:
	float percentageDone;
	glm::vec3 size, position;
public:
	LoadingBar(glm::vec3 size, glm::vec3 position);
	~LoadingBar();
	void setPercentage(float percentage);
};

