#pragma once

#include "TestObject.h"

class HealthBar2D : public TestObject
{
private:
	float healthPercentage;
public:
	HealthBar2D(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable *rable);
	~HealthBar2D();
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void setHealthPercentage(float percentage) { healthPercentage = percentage; }
};

