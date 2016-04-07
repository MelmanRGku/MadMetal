#pragma once
#include "Libraries\glm\glm.hpp"
#include "Simulation\PhysicsManager.h"
#include <vector>
#include <iostream>
#include "Objects\Object3D.h"

class Waypoint;

class CollisionVolume : public Object3D
{
public:
	CollisionVolume(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);
	~CollisionVolume();
	void addAdjacentVolume(CollisionVolume * toAdd);
	bool isAdjacent(CollisionVolume *toCheck);

	void setCurrentWaypointIndex(Waypoint* waypoint);
	void setGoalWaypointIndex(Waypoint* waypoint);

	Waypoint* getCurrentWaypointIndex();
	Waypoint* getGoalWaypointIndex();
	
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);

private: //members
	std::vector<CollisionVolume *> m_adjacentVolumes;
	Waypoint* m_indexOfCurrentWaypoint;
	Waypoint* m_indexOfGoalWaypoint;
};