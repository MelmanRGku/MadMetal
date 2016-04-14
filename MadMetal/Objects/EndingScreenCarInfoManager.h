#pragma once

#include "Object3D.h"

class FTPolygonFont;

class EndingScreenCarInfoManager : public Object3D
{
private:
	Object3D *car;
	FTPolygonFont *font;
	float fontSize;
	std::string name, pos, score;
public:
	EndingScreenCarInfoManager(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Animation *aniable, Object3D *car, int playerNumber);
	~EndingScreenCarInfoManager();
	virtual bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
};

