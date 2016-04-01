#pragma once
#include "Controllable.h"
#include "ControllableTemplate.h"
#include "Objects\Cars\Car.h"
#include "Objects\CollisionVolume.h"
#include "Game Logic\AIDefinitions.h"

class PathFinding;
class Track;

class AIControllable : public Controllable
{
public:
	AIControllable(ControllableTemplate& aiTemplate, Track& track);
	~AIControllable();

	void playFrame(double dt);//todo: fearless leader <
	void setCar(Car * toAdd);
	//Car *getCar() { return m_car; }
	Waypoint* getGoalWaypoint(Waypoint* waypoint);
	void setGoalWaypoint();
	void updateNextWaypoint();
	void processFire(std::vector<Controllable *> *players);
private: //helper functions
	void accelerate(float amount);
	void recalculatePath();
	void checkCollisionVolumes();
	void setHighCostWaypointsToHigh();
	void setHighCostWaypointsToLow();
	void backUp(float amount);
	void processInputAcceleration(float amount);
	void accelerateToNextWaypoint(float speedDamping);
	void reverseToPreviousWaypoint();
	void changeTurning(float turningDirectionValue, float turningAmountValue);
	void checkStuckInWall();
	void updateMovementState(float speedDamping);

private: //members
	//Car* m_car;
	PathFinding* m_pathFinder;
	Waypoint* m_goalWaypoint;
	Track& m_track;
	Waypoint* m_nextWaypoint;
	Waypoint* m_potentialWaypoint;
	Waypoint* m_currentKnownWaypoint;
	AiStateMovement m_movementState;
	AiPlaceInTrack m_AiTrackAreaPosition;
	CollisionVolume* m_lastKnowCollisionVolue;
	std::vector<Waypoint*> m_currentPath;
	std::vector<int> m_listOfWaypointsHighCost;
	bool m_needsToBackup;
	int m_counter;
};