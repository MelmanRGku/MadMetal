#pragma once
#include "Libraries\glm\glm.hpp"
#include "Simulation\PhysicsManager.h"
#include <vector>
#include <iostream>
#include "Objects\Object3D.h"


class CollisionVolume : public Object3D
{
	
	
	std::vector<CollisionVolume *> m_adjacentVolumes;
public:
	CollisionVolume(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);
	~CollisionVolume();
	void addAdjacentVolume(CollisionVolume * toAdd);
	bool isAdjacent(CollisionVolume *toCheck);
	
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
};