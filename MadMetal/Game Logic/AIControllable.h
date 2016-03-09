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
	void processFire(std::vector<Controllable *> *players);
private: //helper functions
	void accelerate(float amount);
	void recalculatePath();
	void checkCollisionVolumes();
	void setHighCostWaypointsToHigh();
	void setHighCostWaypointsToLow();
	void backUp(float amount);
	void processInputAcceleration(float amount);
	void accelerateToNextWaypoint();
	void reverseToPreviousWaypoint();
	void changeTurning(float turningDirectionValue, float turningAmountValue);

private: //members
	//Car* m_car;
	PathFinding* m_pathFinder;
	Waypoint* m_goalWaypoint;
	WaypointSystem* m_waypointSystem;
	Waypoint* m_nextWaypoint;
	Waypoint* m_potentialWaypoint;
	Waypoint* m_currentKnownWaypoint;
	std::vector<Waypoint*> m_currentPath;
	std::vector<int> m_listOfWaypointsHighCost;
	bool m_needsToBackup;
	int m_counter;
};