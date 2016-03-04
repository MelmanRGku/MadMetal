#include "Waypoint.h"

int Waypoint::globalID = 0;

Waypoint::Waypoint(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio) : TestObject(id, aable, pable, anable, rable, audio)
{
	m_id = Waypoint::globalID;
	Waypoint::globalID++;
}


Waypoint::~Waypoint()
{
}

const int& Waypoint::getId()
{
	return Waypoint::m_id;
}

void Waypoint::addAdjecentWaypoint(Waypoint* waypoint)
{
	m_adjecentWaypoints.push_back(waypoint);
}