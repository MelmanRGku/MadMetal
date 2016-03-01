#pragma once
#include "ControllableTemplate.h"
#include "WayPointSystem.h"

class Controllable
{
protected:
	
	ControllableTemplate& m_controllableTemplate;
	
	WayPoint* m_currentWayPoint;
	WayPoint* m_nextWayPoint;


public:
	Controllable(ControllableTemplate& controllableTemplate) : m_controllableTemplate(controllableTemplate){};
	~Controllable(){};

	virtual void playFrame(double dt) = 0;
	void setWayPoint(WayPoint * wayPoint, bool finishLine);

	ControllableTemplate& getControllableTemplate();
	
};