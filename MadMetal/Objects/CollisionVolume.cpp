#include "CollisionVolume.h"
#include "Settings.h"

int CollisionVolume::globalID = 0;

CollisionVolume::CollisionVolume(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable)
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

bool CollisionVolume::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
#ifdef _RENDER_COLLISION_VOLUME
	return TestObject::draw(renderer, type, passNumber);
#else
	return false;
#endif
}
