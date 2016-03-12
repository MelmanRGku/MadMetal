#pragma once
#include "ControllableTemplate.h"
#include "WaypointSystem.h"
#include "Objects\Waypoint.h"

class Car;

class Controllable
{
protected:
	
	ControllableTemplate& m_controllableTemplate;
	bool m_controlsPaused;
	bool m_finishedRace;

public:
	Controllable(ControllableTemplate& controllableTemplate) : m_controllableTemplate(controllableTemplate){};
	virtual ~Controllable()
	{
	};

	virtual void playFrame(double dt) = 0;
	void setWaypoint(Waypoint * waypoint, bool finishLine);
	
	ControllableTemplate& getControllableTemplate();
	virtual void setCar(Car * toAdd) = 0;
	
	Car *getCar() { return m_car; }

	void pauseControls(bool pause);
	
protected:
	Car* m_car;
};