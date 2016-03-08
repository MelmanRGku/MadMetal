#pragma once

#include "TestObject.h"
#include "HealthBar2D.h"
#include "GaugeBar.h"
#include "Text2D.h"

class UI : public TestObject
{
public:
	UI(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable);
	~UI();

	HealthBar2D *healthBar;
	GaugeBar *gaugeBar;
	Text2D *score,
		*lap;
		
};

