#include "Track.h"
#include "Waypoint.h"
#include "Game Logic\WayPointSystem.h"

Track::Track(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable *rable, TestObject *drivablePart, TestObject *nonDrivablePart) : TestObject(id, aable, pable, anable, rable), drivablePart(drivablePart), nonDrivablePart(nonDrivablePart)
{
	WaypointSystem * startLocation = new WaypointSystem(
		getDrivablePart()->getWorldBounds().minimum.x,
		getDrivablePart()->getWorldBounds().maximum.x,
		getDrivablePart()->getWorldBounds().minimum.z,
		getDrivablePart()->getWorldBounds().maximum.z,
		getDrivablePart()->getWorldBounds().maximum.y);

	//m_waypointList.resize(m_waypointList.size() + (startLocation->getWaypointMap().at(0).size() * startLocation->getWaypointMap().size()));
	for (int i = 0; i < startLocation->getWaypointMap().size(); i++)
	{
		m_waypointList.insert(m_waypointList.end(), startLocation->getWaypointMap().at(i).begin(), startLocation->getWaypointMap().at(i).end());
	}

	m_waypointSystems.push_back(startLocation);
}

Track::~Track()
{
	for (std::vector<Waypoint*>::iterator it = m_waypointList.begin(); it != m_waypointList.end(); ++it)
	{
		delete *it;
	}
}

bool Track::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	
	//do nothing
	return false;

}

void Track::playTrackMusic()
{
	m_audioable->getAudioHandle().playMusic(m_sound);
}

Waypoint * Track::getWaypointAt(int index)
{
	if (index < m_waypointList.size())
	{
		return m_waypointList[index];
	}
	else
	{
		std::cerr << "ERROR: trying to acquire out of index pointer\n";
		return NULL;
	}
}