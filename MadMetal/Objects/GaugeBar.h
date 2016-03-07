#pragma once

#include "TestObject.h"

class GaugeBar : public TestObject
{
private:
	float gaugePercentage;
public:
	GaugeBar(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable);
	~GaugeBar();

	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void setGaugePercentage(float percentage) { gaugePercentage = percentage; }
};

