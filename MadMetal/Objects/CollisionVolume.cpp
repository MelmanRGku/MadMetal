#include "CollisionVolume.h"
#include "Settings.h"

int CollisionVolume::globalID = 0;

void CollisionVolume::resetGlobalId() {
	CollisionVolume::globalID = 0;
}

CollisionVolume::CollisionVolume(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable, NULL)
{
	m_respawnIndex = 0;
	m_isStartCollisionVolume = false;
	m_speedDamping = 1.0;
	m_steeringDamping = 1.0;
	m_volumeId = CollisionVolume::globalID;
	CollisionVolume::globalID++;
	m_isPartOfMainPath = true;
	m_pathNumber = 1;
	static_cast<Model3D *>(m_renderable->getModel())->setAlpha(0.3);
}


CollisionVolume::~CollisionVolume()
{
}

CollisionVolume * CollisionVolume::getNextCollisionVolume()
{
	srand(time(NULL));
	if (m_possibleNextCollisionVolumes.empty())
	{
		return NULL;
	}
	else
	{
		return m_possibleNextCollisionVolumes[rand() % m_possibleNextCollisionVolumes.size()];
	}
}

void CollisionVolume::setNextCollisionVolume(CollisionVolume * toSet)
{
	m_next = toSet;

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

/*void CollisionVolume::addNextVolume(CollisionVolume * toAdd)
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
	
}*/

void CollisionVolume::setIsStartCollisionVolume(bool isStartCollisionVolume) {
	m_isStartCollisionVolume = isStartCollisionVolume;
}

/*void CollisionVolume::setCurrentWaypointIndex(Waypoint* waypoint)
{
	m_currentWaypoint = waypoint;
}

void CollisionVolume::setGoalWaypointIndex(Waypoint* waypoint)
{
	m_goalWaypoint = waypoint;
}*/


/*Waypoint* CollisionVolume::getCurrentWaypointIndex()
{
	return m_currentWaypoint;
}
Waypoint* CollisionVolume::getGoalWaypointIndex()
{
	return m_goalWaypoint;
}*/

float CollisionVolume::getSpeedDamping()
{
	return m_speedDamping;
}
float CollisionVolume::getSteeringDamping()
{
	return m_steeringDamping;
}

void CollisionVolume::setSectionSpeedDamping(float damping)
{
	m_speedDamping = damping;
}

void CollisionVolume::setSectionSteeringDamping(float damping)
{
	m_steeringDamping = damping;
}

void CollisionVolume::addVolumeToNextCollsionVolumeList(CollisionVolume* toAdd)
{
	m_possibleNextCollisionVolumes.push_back(toAdd);
}

int CollisionVolume::getId()
{
	return m_volumeId;
}

void CollisionVolume::setPathNumber(int pathNumber)
{
	m_pathNumber = pathNumber;
}
void CollisionVolume::setIsParthOfMainPath(bool part)
{
	m_isPartOfMainPath = part;
}
void CollisionVolume::setId(int id)
{
	m_volumeId = id;
}

int CollisionVolume::getPathNumber()
{
	return m_pathNumber;
}
bool CollisionVolume::getIsPartOfMainPath()
{
	return m_isPartOfMainPath;
}

bool CollisionVolume::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
#ifdef _RENDER_COLLISION_VOLUME
	return Object3D::draw(renderer, type, passNumber);
#else
	return false;
#endif
}
