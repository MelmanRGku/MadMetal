#pragma once
#include "ControllableTemplate.h"
#include "WaypointSystem.h"
#include "Simulation\Waypoint.h"

class Controllable
{
protected:
	
	ControllableTemplate& m_controllableTemplate;

	Waypoint* m_currentWaypoint;
	Waypoint* m_nextWaypoint;

	
public:
	Controllable(ControllableTemplate& controllableTemplate) : m_controllableTemplate(controllableTemplate){};
	~Controllable(){};

	virtual void playFrame(double dt) = 0;
	void setWaypoint(Waypoint * waypoint, bool finishLine);
	
	ControllableTemplate& getControllableTemplate();
	
};