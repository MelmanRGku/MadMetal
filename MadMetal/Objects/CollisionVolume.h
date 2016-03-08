#pragma once
#include "Libraries\glm\glm.hpp"
#include "Simulation\PhysicsManager.h"
#include <vector>
#include <iostream>
#include <Objects\TestObject.h>


class CollisionVolume : public TestObject
{
	static int globalID;
	int m_id;

public:
	CollisionVolume(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable);
	~CollisionVolume();
	const int& getId();
};