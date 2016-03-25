#pragma once
#include "Libraries\glm\glm.hpp"
#include "Simulation\PhysicsManager.h"
#include "Objects\Waypoint.h"
#include "Simulation\PhysicsManager.h"
#include "Factory\GameFactory.h"
#include "Game Logic\WaypointDefinitions.h"
#include "Objects\TestObject.h"
#include <vector>
#include <iostream>

class WaypointSystem
{
public:
	WaypointSystem(int trackWidthMin, int trackWidthMax, int trackLengthMin, int trackLengthMax, int yposition, Boundry startingPosition);
	~WaypointSystem();
	void addIdToAllWaypointsInTheSystem(int id);

public: // member functions
	Waypoint * getWaypointAt(int index) { return m_waypoints[index]; }
	std::vector<std::vector<Waypoint*>>& getWaypointMap() { return m_waypointMap; }
	void createWaypointConnections();

private: // members
	std::vector<std::vector<Waypoint*>> m_waypointMap;
	std::vector<Waypoint *> m_waypoints;

	void test();
};