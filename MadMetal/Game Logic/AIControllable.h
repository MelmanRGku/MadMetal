#pragma once
#include "Controllable.h"
#include "ControllableTemplate.h"
#include "Objects\Cars\Car.h"

class AIControllable : public Controllable
{
public:
	AIControllable(ControllableTemplate& aiTemplate) : Controllable(aiTemplate)
	{

	};
	~AIControllable()
	{

	};

	void playFrame(double dt){};//todo: fearless leader <3

private: //members
	Car* m_car;

};