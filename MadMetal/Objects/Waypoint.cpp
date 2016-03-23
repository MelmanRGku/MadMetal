#include "Settings.h"
#include "Waypoint.h"

int Waypoint::globalID = 0;

Waypoint::Waypoint(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable, NULL)
{
	m_index = Waypoint::globalID;
	m_id = m_index;
	Waypoint::globalID++;
	m_isValid = true;
}


Waypoint::~Waypoint()
{
}

const int& Waypoint::getIndex()
{
	return Waypoint::m_index;
}

void Waypoint::addAdjecentWaypoint(Waypoint* waypoint)
{
	m_adjecentWaypoints.push_back(waypoint);
}

bool Waypoint::isValid()
{
	return m_isValid;
}

bool Waypoint::isFinish() {
	return m_isFinish;
}

void Waypoint::setValid(bool isValid)
{
	m_isValid = isValid;
}


void Waypoint::setFinish(bool finish) {
	m_isFinish = finish;
}

int Waypoint::getId()
{
	return m_id;
}

void Waypoint::setId(int id)
{
	m_id = id;
}

bool Waypoint::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
#ifdef _RENDER_WAYPOINT
	return Object3D::draw(renderer, type, passNumber);
#else
	return false;
#endif
}