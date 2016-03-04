#pragma once
#include "Libraries\glm\glm.hpp"
#include "Simulation\PhysicsManager.h"
#include "Objects\Waypoint.h"
#include "Simulation\PhysicsManager.h"
#include "Factory\GameFactory.h"
#include "Objects\TestObject.h"
#include <vector>
#include <iostream>

class WaypointSystem
{
public:
	WaypointSystem(GameFactory& gameFactory, int trackWidth, int trackLength);
	~WaypointSystem();

public: // member functions
	Waypoint * getWaypointAt(int index) { return m_waypoints[index]; }

private: // members
	std::vector<Waypoint *> m_waypoints;
	GameFactory& m_gameFactory;
};