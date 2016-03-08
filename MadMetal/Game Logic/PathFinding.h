#pragma once
#include <vector>
#include "Libraries\glm\glm.hpp"

class Waypoint;
class SearchWaypoint;

class PathFinding
{
public: //Constructors
	PathFinding();
	~PathFinding();

public: // functions
	std::vector<Waypoint*> findPath(Waypoint * currentPosition, Waypoint * targetPosition);
	void setWaypointCostOf(std::vector<int> listOfHighWaypoints);
	//glm::vec3 NextPathPosition();
	//void clearOpenList();
	//void clearVisitedList();
	//void clearPathToGoal();
	//bool isStartGoalInitialized();
	//bool isGoalFound();

private: 
	bool m_initializedStartGOal;
	bool m_foundGoal;
	void setStartAndGoal(Waypoint& currentPosition, Waypoint& targetPosition);
	void pathOpened(Waypoint& waypoint, float newCost, SearchWaypoint *parent);
	SearchWaypoint* getNextCell();
	void continuePath();
private: //memebers 
	SearchWaypoint* m_startWaypoint;
	SearchWaypoint* m_goalWaypoint;
	std::vector<SearchWaypoint*> m_openList;
	std::vector<SearchWaypoint*> m_visitedList;
	std::vector<Waypoint*> m_pathToGoal;
	std::vector<int> m_indexWithHighCost;
};