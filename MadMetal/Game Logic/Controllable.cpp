#include "Controllable.h"
#include <iostream>

void Controllable::setWayPoint(WayPoint * wayPoint, bool finishLine)
{
	//when players first spawn they will have no wayPoint so the first waypoint 
	//they encounter will just set them up
	if (m_currentWayPoint == NULL)
	{
		std::cout << "First way point set! \n";
		m_currentWayPoint = wayPoint;
		m_nextWayPoint = wayPoint->getNextWayPoint();
	}
	//check if the new way points previous waypoint is the players current waypoint
	//if not the player is driving backwards or is skipping through the map some how. 
	else {
		if (m_currentWayPoint == wayPoint->getPreviousWayPoint())
		{
			
			m_currentWayPoint = wayPoint;
			m_nextWayPoint = wayPoint->getNextWayPoint();
		}
		else {
			//std::cout << "Player missed a waypoint. Way point not updated \n";
		}
	}
}


ControllableTemplate& Controllable::getControllableTemplate()
{
	return m_controllableTemplate;
}

