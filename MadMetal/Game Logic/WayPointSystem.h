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
	std::vector<std::vector<Waypoint*>>& getWaypointMap() { return m_waypointMap; }

private: // members
	std::vector<std::vector<Waypoint*>> m_waypointMap;
	std::vector<Waypoint *> m_waypoints;
	GameFactory& m_gameFactory;


	void test();
};