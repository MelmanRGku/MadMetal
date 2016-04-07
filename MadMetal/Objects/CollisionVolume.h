#pragma once
#include "Libraries\glm\glm.hpp"
#include "Simulation\PhysicsManager.h"
#include <vector>
#include <iostream>
#include "Objects\Object3D.h"


class CollisionVolume : public Object3D
{
	int m_respawnIndex;
	std::vector<PxTransform> m_respawnLocations;
	std::vector<CollisionVolume *> m_nextVolumes;
	bool m_isStartCollisionVolume;

public:
	CollisionVolume(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);
	~CollisionVolume();
	PxTransform getRespawnLocation();
	void setRespawnLocations(std::vector<PxVec3> locations);
	void setIsStartCollisionVolume(bool isStartCollisionVolume);
	bool getIsStartCollisionVolume();

	void addNextVolume(CollisionVolume * toAdd);
	bool isPrevVolumeOf(CollisionVolume *toCheck);
	
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
};