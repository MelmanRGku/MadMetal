#include "CollisionVolume.h"
#include "Settings.h"



CollisionVolume::CollisionVolume(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable, NULL)
{
	
}


CollisionVolume::~CollisionVolume()
{
}

void CollisionVolume::addAdjacentVolume(CollisionVolume * toAdd)
{
	m_adjacentVolumes.push_back(toAdd);
}

bool CollisionVolume::isAdjacent(CollisionVolume * toCheck)
{
	for (int i = 0; i < m_adjacentVolumes.size(); i++)
	{
		if (m_adjacentVolumes[i] == toCheck)
		{
			return true;
		}
	}
	return false;
	
}

bool CollisionVolume::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
#ifdef _RENDER_COLLISION_VOLUME
	return Object3D::draw(renderer, type, passNumber);
#else
	return false;
#endif
}
