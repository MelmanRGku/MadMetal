#pragma once
#include "Libraries\glm\glm.hpp"
#include "Simulation\PhysicsManager.h"
#include <vector>
#include <iostream>


#define WAYPOINT_DIMENSION_X 4

class Waypoint
{
	int m_id;
	glm::vec3 m_position;
	std::vector<Waypoint*> m_adjecentWaypoints;

public:
	Waypoint(glm::vec3 position, int id)
	{
		m_position = position;
		m_id = id;
	}
	~Waypoint()
	{
	}
	// void setNextWaypoint(Waypoint * next){ m_next = next; }
	// void setPreviousWaypoint(Waypoint * previous) { m_previous = previous; }
	std::vector<Waypoint*>& getListOfAdjacentWaypoints(){ return m_adjecentWaypoints; }
	glm::vec3& getWaypointPosition() { return m_position; }
	int& getId()
	{
		return m_id;
	}

	void addAdjecentWaypoint(Waypoint* waypoint)
	{
		m_adjecentWaypoints.push_back(waypoint);
	}
};