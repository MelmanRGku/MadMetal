#pragma once

#include "TexturedObject2D.h"

class HealthBar2D : public TexturedObject2D
{
private:
	float healthPercentage;
	Model2D *currentHealthModel,
		*lostHealthModel;
public:
	HealthBar2D(long id, Audioable *aable, Animatable *anable, Renderable2D *rable, Model2D *currentHealthModel, Model2D *lostHealthModel);
	~HealthBar2D();
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void setHealthPercentage(float percentage) { healthPercentage = percentage; if (healthPercentage < 0) healthPercentage = 0; }
};

