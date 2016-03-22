#pragma once

#include "Object3D.h"

#define LOADING_BAR_BORDER_SIZE  0.1f

class LoadingBar : public Object3D
{
private:
	float percentageDone;
	TestObject *completeBar;
public:
	LoadingBar(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);
	~LoadingBar();
	void setPercentage(float percentage);
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void setProgress(float percentage);
};

