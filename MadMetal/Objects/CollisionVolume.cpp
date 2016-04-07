#include "CollisionVolume.h"
#include "Settings.h"



CollisionVolume::CollisionVolume(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable, NULL)
{
	m_respawnIndex = 0;
	m_isStartCollisionVolume = false;
}


CollisionVolume::~CollisionVolume()
{
}

void CollisionVolume::setRespawnLocations(std::vector<PxVec3> locations)
{
	m_respawnLocations.clear();
	PxQuat quat = m_physicable->getActor().getGlobalPose().q;
	for (int i = 0; i < locations.size(); i++)
	{
		m_respawnLocations.push_back(PxTransform(locations[i], quat));
	}
}

PxTransform CollisionVolume::getRespawnLocation()
{
	if (m_respawnLocations.size() == 0)
	{
		return m_physicable->getActor().getGlobalPose();
	}
	PxTransform  transform = m_respawnLocations[m_respawnIndex++];
	if (m_respawnIndex == m_respawnLocations.size())
	{
		m_respawnIndex = 0;
	}
	return transform;
}

void CollisionVolume::addNextVolume(CollisionVolume * toAdd)
{
	m_nextVolumes.push_back(toAdd);
}

bool CollisionVolume::isPrevVolumeOf(CollisionVolume * toCheck)
{
	for (int i = 0; i < m_nextVolumes.size(); i++)
	{
		if (m_nextVolumes[i] == toCheck)
		{
			return true;
		}
	}
	return false;
	
}

void CollisionVolume::setIsStartCollisionVolume(bool isStartCollisionVolume) {
	m_isStartCollisionVolume = isStartCollisionVolume;
}

bool CollisionVolume::getIsStartCollisionVolume() {
	return m_isStartCollisionVolume;
}


bool CollisionVolume::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
#ifdef _RENDER_COLLISION_VOLUME
	return Object3D::draw(renderer, type, passNumber);
#else
	return false;
#endif
}
