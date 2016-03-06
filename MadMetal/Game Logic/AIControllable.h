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
		m_car = NULL;
	};

	void playFrame(double dt);
	void setCar(Car * toAdd);
	
private: //members
	Car* m_car;

};