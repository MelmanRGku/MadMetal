#pragma once
#include "Libraries\glm\glm.hpp"
#include "Simulation\PhysicsManager.h"
#include <vector>
#include <iostream>
#include "Objects\Object3D.h"


class CollisionVolume : public Object3D
{
	
	int m_id;

public:
	CollisionVolume(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);
	~CollisionVolume();
	static int globalID;
	const int& getIndex();
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
};