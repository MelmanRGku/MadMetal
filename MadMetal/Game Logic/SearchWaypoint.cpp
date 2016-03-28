#include "Game Logic\SearchWaypoint.h"
#include "Objects\Waypoint.h"
#include <math.h>

SearchWaypoint::SearchWaypoint(Waypoint& waypoint, SearchWaypoint* parent, float G, float H)
: m_waypoint(waypoint)
{
	m_parent = parent;
	m_G = G;
	m_H = H;
}

SearchWaypoint::~SearchWaypoint()
{
	
}

float SearchWaypoint::GetF()
{
	return m_G + m_H + m_waypoint.getHighCost();
}

Waypoint& SearchWaypoint::getWaypoint()
{
	return m_waypoint;
}

float SearchWaypoint::ManHattanDistance(SearchWaypoint * endNode)
{
	float  x = static_cast<float>(fabs(static_cast<float>(m_waypoint.getGlobalPose().x - endNode->getWaypoint().getGlobalPose().x)));
	float  z = static_cast<float>(fabs(static_cast<float>(m_waypoint.getGlobalPose().z - endNode->getWaypoint().getGlobalPose().z)));

	return x + z;
}

void SearchWaypoint::setParent(SearchWaypoint* parent)
{
	m_parent = parent;
}
void SearchWaypoint::setH(float H)
{
	m_H = H;
}
void SearchWaypoint::setG(float G)
{
	m_G = G;
}
float SearchWaypoint::getG()
{
	return m_G;
}
float SearchWaypoint::getH()
{
	return m_H;
}
SearchWaypoint* SearchWaypoint::getParent()
{
	return m_parent;
}
