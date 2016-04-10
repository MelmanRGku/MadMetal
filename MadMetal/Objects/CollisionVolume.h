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

	CollisionVolume * getNextCollisionVolume();
	void setNextCollisionVolume(CollisionVolume* toSet);
	void setSectionSpeedDamping(float damping);
	void setSectionSteeringDamping(float damping);

	Waypoint* getCurrentWaypointIndex();
	Waypoint* getLastWaypointIndex();
	Waypoint* getGoalWaypointIndex();
	float getSpeedDamping();
	float getSteeringDamping();
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	static void resetGlobalId();

private: //members

	float m_speedDamping;
	float m_steeringDamping;
	int m_respawnIndex;
	CollisionVolume * m_next;
	std::vector<PxTransform> m_respawnLocations;
	bool m_isStartCollisionVolume;
	int m_volumeIndex;
	static int globalID;
};