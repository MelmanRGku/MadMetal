#pragma once
#include "Libraries\glm\glm.hpp"
#include "Simulation\PhysicsManager.h"
#include "Objects\Waypoint.h"
#include "Simulation\PhysicsManager.h"
#include "Factory\GameFactory.h"
#include "Objects\TestObject.h"
#include <vector>
#include <iostream>

// class Waypoint
// {
// 	glm::vec3 &m_position;
// 	std::vector<&Waypoint> m_adjecentWaypoints;

// public:
// 	Waypoint(glm::vec3 position) : m_position(position){}
// 	~Waypoint()
// 	{
// 	}
// 	// void setNextWaypoint(Waypoint * next){ m_next = next; }
// 	// void setPreviousWaypoint(Waypoint * previous) { m_previous = previous; }
// 	std::vector<&Waypoint>& getListOfAdjacentWaypoints(){ return m_adjecentWaypoints; }
// 	glm::vec3 & getWaypointPosition() { return m_position; }
// };

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