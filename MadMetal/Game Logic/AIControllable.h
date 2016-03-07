#pragma once
#include "Controllable.h"
#include "ControllableTemplate.h"
#include "Objects\Cars\Car.h"

class PathFinding;
class m_waypointSystem;

class AIControllable : public Controllable
{
public:
	AIControllable(ControllableTemplate& aiTemplate, WaypointSystem* waypointSystem = NULL);
	~AIControllable();

	void playFrame(double dt);//todo: fearless leader <
	void setCar(Car * toAdd);
	//Car *getCar() { return m_car; }
	Waypoint* getGoalWaypoint(Waypoint* waypoint);
	void setGoalWaypoint();
	void updateNextWaypoint();
	void setWaypointSystem(WaypointSystem* waypointSystem);
private: //helper functions
	void accelerate(float amount);

private: //members
	//Car* m_car;
	PathFinding* m_pathFinder;
	Waypoint* m_goalWaypoint;
	WaypointSystem* m_waypointSystem;
	Waypoint* m_nextWaypoint;
	std::vector<Waypoint*> m_currentPath;
};