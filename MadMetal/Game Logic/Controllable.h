#pragma once
#include "ControllableTemplate.h"
#include "WaypointSystem.h"
#include "Objects\Waypoint.h"

class Car;

class Controllable
{
protected:
	
	ControllableTemplate& m_controllableTemplate;

public:
	Controllable(ControllableTemplate& controllableTemplate) : m_controllableTemplate(controllableTemplate){};
	~Controllable()
	{
		delete m_car;
	};

	virtual void playFrame(double dt) = 0;
	void setWaypoint(Waypoint * waypoint, bool finishLine);
	
	ControllableTemplate& getControllableTemplate();
	virtual void setCar(Car * toAdd) = 0;
	Car *getCar() { return m_car; }
protected:
	Car* m_car;
};