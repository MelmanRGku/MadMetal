#pragma once
#include "ControllableTemplate.h"
#include "WayPointSystem.h"
#include "Objects\Object.h"
#include "Objects\Cars\Car.h"

class Controllable
{
protected:
	
	ControllableTemplate& m_controllableTemplate;

	WayPoint* m_currentWayPoint;
	WayPoint* m_nextWayPoint;
	Car* m_car;
	
public:
	Controllable(ControllableTemplate& controllableTemplate) : m_controllableTemplate(controllableTemplate){};
	~Controllable(){};

	virtual void playFrame(double dt) = 0;
	void setWayPoint(WayPoint * wayPoint, bool finishLine);
	virtual void setCar(Car * toAdd) = 0;
	Car *getCar() { return m_car; }
	ControllableTemplate& getControllableTemplate();
	
};