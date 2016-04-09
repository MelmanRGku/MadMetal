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
	PxTransform getRespawnLocation();
	void setRespawnLocations(std::vector<PxVec3> locations);
	void setIsStartCollisionVolume(bool isStartCollisionVolume);
	bool getIsStartCollisionVolume();

	CollisionVolume * getNextCollisionVolume();
	void setNextCollisionVolume(CollisionVolume* toSet);
	void setCurrentWaypointIndex(Waypoint* waypoint);
	void setGoalWaypointIndex(Waypoint* waypoint);

	Waypoint* getCurrentWaypointIndex();
	Waypoint* getGoalWaypointIndex();
	
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);

private: //members
	int m_respawnIndex;
	CollisionVolume * m_next;
	std::vector<PxTransform> m_respawnLocations;
	bool m_isStartCollisionVolume;

};