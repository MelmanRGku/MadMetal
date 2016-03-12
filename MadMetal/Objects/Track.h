#pragma once

#include "TestObject.h"

class WaypointSystem;
class Waypoint;

class Track : public TestObject
{
public:
	Track(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable *rable, TestObject *drivablePart, TestObject *nonDrivablePart);
	~Track();
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	TestObject *getDrivablePart() { return drivablePart; }
	Waypoint * getWaypointAt(int index);
	
	void playTrackMusic();

private: //members
	TestObject *drivablePart,
		*nonDrivablePart;
	std::vector<WaypointSystem*> m_waypointSystems;
	std::vector<Waypoint*> m_waypointList;
	
};
