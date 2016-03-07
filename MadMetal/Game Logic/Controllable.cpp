#include "Controllable.h"
#include <iostream>

void Controllable::setWaypoint(Waypoint * waypoint, bool finishLine)
{
	// //when players first spawn they will have no waypoint so the first waypoint 
	// //they encounter will just set them up
	// if (m_currentWaypoint == NULL)
	// {
	// 	std::cout << "First way point set! \n";
	// 	m_currentWaypoint = waypoint;
	// 	m_nextWaypoint = waypoint->getNextWaypoint();
	// }
	// //check if the new way points previous waypoint is the players current waypoint
	// //if not the player is driving backwards or is skipping through the map some how. 
	// else {
	// 	if (m_currentWaypoint == waypoint->getPreviousWaypoint())
	// 	{
			
	// 		m_currentWaypoint = waypoint;
	// 		m_nextWaypoint = waypoint->getNextWaypoint();
	// 	}
	// 	else {
	// 		//std::cout << "Player missed a waypoint. Way point not updated \n";
	// 	}
	// }
}



ControllableTemplate& Controllable::getControllableTemplate()
{
	return m_controllableTemplate;
}

void Controllable::pauseControls(bool pause) {
	m_controlsPaused = pause;
}