#pragma once

#include "Object2D.h"

class GaugeBar : public Object2D
{
private:
	float gaugePercentage;
public:
	GaugeBar(long id, Audioable *aable, Animatable *anable, Renderable2D *rable);
	~GaugeBar();

	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void setGaugePercentage(float percentage) { gaugePercentage = percentage; }
};

