#pragma once
#include "Libraries\glm\glm.hpp"
#include "Simulation\PhysicsManager.h"
#include <vector>
#include <iostream>
#include "Objects\Object3D.h"
#include "Game Logic\AIDefinitions.h"

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

	void addNextVolume(CollisionVolume * toAdd);
	bool isPrevVolumeOf(CollisionVolume *toCheck);
	
	void setCurrentWaypointIndex(Waypoint* waypoint);
	void setLastWaypointIndex(Waypoint* waypoint);
	void setGoalWaypointIndex(Waypoint* waypoint);
	void setAiPlaceInTrack(AiPlaceInTrack movement);

	Waypoint* getCurrentWaypointIndex();
	Waypoint* getLastWaypointIndex();
	Waypoint* getGoalWaypointIndex();

	AiPlaceInTrack getAiPlaceInTrack();
	
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);

private: //members
	Waypoint* m_lastWaypoint;
	Waypoint* m_currentWaypoint;
	Waypoint* m_goalWaypoint;
	AiPlaceInTrack m_aiPlaceInTrack;
	int m_respawnIndex;
	std::vector<CollisionVolume *> m_nextVolumes;
	std::vector<PxTransform> m_respawnLocations;
	bool m_isStartCollisionVolume;

};