#include "CollisionVolume.h"

int CollisionVolume::globalID = 0;

CollisionVolume::CollisionVolume(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable) : TestObject(id, aable, pable, anable, rable)
{
	m_id = CollisionVolume::globalID;
	CollisionVolume::globalID++;
}


CollisionVolume::~CollisionVolume()
{
}

const int& CollisionVolume::getId()
{
	return CollisionVolume::m_id;
}
