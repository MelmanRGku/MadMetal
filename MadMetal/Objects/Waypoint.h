#pragma once
#include "Libraries\glm\glm.hpp"
#include "Simulation\PhysicsManager.h"
#include <vector>
#include <iostream>
#include "Objects\Object3D.h"

#define WAYPOINT_DIMENSION_X 4

class Waypoint : public Object3D
{
	static int globalID;
	int m_index;
	int m_id;
	bool m_isValid;
	bool m_isFinish;
	float m_highCost;
	std::vector<Waypoint*> m_adjecentWaypoints;

public:
	Waypoint(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);
	~Waypoint();
	std::vector<Waypoint*>& getListOfAdjacentWaypoints(){ return m_adjecentWaypoints; }
	const int& getIndex();
	bool isValid();
	void setValid(bool isValid);
	bool isFinish();
	void setFinish(bool finish);
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void addAdjecentWaypoint(Waypoint* waypoint);
	int getId();
	void setId(int id);
	PxVec3 m_position;

	void setHighCost(float highCost);
	float getHighCost();

	static void resetGlobalId();
};