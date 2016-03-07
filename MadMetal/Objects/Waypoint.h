#pragma once
#include "Libraries\glm\glm.hpp"
#include "Simulation\PhysicsManager.h"
#include <vector>
#include <iostream>
#include <Objects\TestObject.h>

#define WAYPOINT_DIMENSION_X 4

class Waypoint : public TestObject
{
	static int globalID;
	int m_id;
	bool m_isValid;
	std::vector<Waypoint*> m_adjecentWaypoints;

public:
	Waypoint(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable);
	~Waypoint();
	std::vector<Waypoint*>& getListOfAdjacentWaypoints(){ return m_adjecentWaypoints; }
	const int& getId();
	bool isValid();
	void setValid(bool isValid);

	void addAdjecentWaypoint(Waypoint* waypoint);
};