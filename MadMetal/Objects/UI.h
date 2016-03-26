#pragma once

#include "Object2D.h"
#include "HealthBar2D.h"
#include "GaugeBar.h"
#include "Text2D.h"
#include "MapUI.h"

class UI : public Object2D
{
public:
	UI(long id, Audioable *aable, Animatable *anable, Renderable2D *rable);
	~UI();
	virtual bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void adjustStringsForViewport(int thisViewportNumber, int totalNumberOfViewports);
	HealthBar2D *healthBar;
	GaugeBar *gaugeBar;
	Text2D *score,
		*lap;
	MapUI *map;
		
};

