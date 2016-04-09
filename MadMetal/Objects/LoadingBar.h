#pragma once

#include "Object3D.h"

class LoadingBar : public Object3D
{
private:
	float percentageDone;
	float completedScaleX = 25.3f;
	float completedPosX = 0;
public:
	LoadingBar(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);
	~LoadingBar();
	void setPercentage(float percentage);
	void setProgress(float percentage);
};

