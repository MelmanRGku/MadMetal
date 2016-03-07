#pragma once

#include "TestObject.h"

#define LOADING_BAR_BORDER_SIZE  0.2f

class LoadingBar : public TestObject
{
private:
	float percentageDone;
	TestObject *completeBar;
public:
	LoadingBar(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable);
	~LoadingBar();
	void setPercentage(float percentage);
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void setProgress(float percentage);
};

