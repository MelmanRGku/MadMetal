#pragma once

#include "TexturedObject2D.h"

class GaugeBar : public TexturedObject2D
{
private:
	float gaugePercentage;
	float timeBetweenFullGaugeBarFramesSeconds;
	float currentFrameTimeSeconds = 0;
	float superTotalDuration;
	bool superInUse = false;
	float superDurationRemaining;
	Model2D *currentGaugeModel;
	Model2D *currentCompleteGaugeModel;
	int currentCompleteGaugeModelIndex = 0;
	std::vector<Model2D *> completeGaugeModels;
public:
	GaugeBar(long id, Audioable *aable, Animatable *anable, Renderable2D *rable, Model2D *currentGaugeModel, std::vector<Model2D *> completeGaugeModels);
	~GaugeBar();

	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	bool drawWhenNotInUse(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	bool drawWhenInUse(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void setGaugePercentage(float percentage);
	virtual void update(float dt);
	void superUsed(float totalDuration);
	void setSuperDurationRemaining(float duration);
};

