#pragma once

#include "Object2D.h"

class HealthBar2D : public Object2D
{
private:
	float healthPercentage;
public:
	HealthBar2D(long id, Audioable *aable, Animatable *anable, Renderable2D *rable);
	~HealthBar2D();
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void setHealthPercentage(float percentage) { healthPercentage = percentage; if (healthPercentage < 0) healthPercentage = 0; }
};

