#include "Waypoint.h"

int Waypoint::globalID = 0;

Waypoint::Waypoint(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable) : TestObject(id, aable, pable, anable, rable)
{
	m_id = Waypoint::globalID;
	Waypoint::globalID++;
	m_isValid = true;
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

//bool Waypoint::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
//	if (Renderer::ShaderType::SHADER_TYPE_CELL != type || passNumber > 1)
//		return false;
//
//	return false;
//}