#pragma once
#include "Libraries\glm\glm.hpp"
#include "Simulation\PhysicsManager.h"
#include "Simulation\Waypoint.h"
#include <vector>
#include <iostream>
#include "Simulation\Waypoint.h"


// #define WAYpOINT_DIMENSION_X 4

// class Waypoint
// {
// 	glm::vec3 &m_position;
// 	std::vector<&Waypoint> m_adjecentWaypoints;

// public:
// 	Waypoint(glm::vec3 position) : m_position(position){}
// 	~Waypoint()
// 	{
// 	}
// 	// void setNextWaypoint(Waypoint * next){ m_next = next; }
// 	// void setPreviousWaypoint(Waypoint * previous) { m_previous = previous; }
// 	std::vector<&Waypoint>& getListOfAdjacentWaypoints(){ return m_adjecentWaypoints; }
// 	glm::vec3 & getWaypointPosition() { return m_position; }
// };

class WaypointSystem
{
	std::vector<Waypoint *> m_waypoints;

public:
	
	Waypoint * getWaypointAt(int index) { return m_waypoints[index]; }

	/*
		Current System is always a circular track with first position supplied assumed to be the finish line
	*/
	WaypointSystem(PxScene * physicsScene, std::vector<glm::vec3> positions)
	{
		// PxRigidActor * tempActor;
		// PxShape * tempShape;
		// PxMaterial * dummyMaterial = physicsScene->getPhysics().createMaterial(0, 0, 0);

		// //initialize waypoints
		// for (unsigned int i = 0; i < positions.size(); i++)
		// {
		// 	//add waypoint to the list
		// 	m_waypoints.push_back(new Waypoint(positions[i]));
		// 	//create a mirror trigger volume in scene
		// 	tempActor = physicsScene->getPhysics().createRigidStatic(PxTransform(positions[i].x, positions[i].y, positions[i].z));
		// 	tempShape = tempActor->createShape(PxBoxGeometry(WAYpOINT_DIMENSION_X, WAYpOINT_DIMENSION_X, 1), *dummyMaterial);
		// 	tempShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		// 	tempShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

		// 	//set word2 to index of way point in system
			
		// 	PhysicsManager::setupFiltering(
		// 		tempActor, 
		// 		PhysicsManager::WAYpOINT, 
		// 		PhysicsManager::PLAYER, 
		// 		i,				 //index of waypoint in list
		// 		i == 0 ? 1 : 0); //if first waypoint, set info to finishline

		// 	physicsScene->addActor(*tempActor);
		// }

		// if (m_waypoints.size() > 1)
		// {
		// 	//connect way points
		// 	for (unsigned int i = 0; i < m_waypoints.size(); i++)
		// 	{
		// 		if (i == 0)
		// 		{
		// 			std::cout << "waypoint: " << i << " previous set to " << m_waypoints.size() - 1 << " next set to: " << i + 1 << std::endl;
		// 			m_waypoints[i]->setPreviousWaypoint(m_waypoints[m_waypoints.size() - 1]);
		// 			m_waypoints[i]->setNextWaypoint(m_waypoints[i + 1]);
					
		// 		}
		// 		else if (i == m_waypoints.size() - 1)
		// 		{
		// 			std::cout << "waypoint: " << i << " previous set to " << i - 1 << " next set to: " << 0 << std::endl;
		// 			m_waypoints[i]->setPreviousWaypoint(m_waypoints[i - 1]);
		// 			m_waypoints[i]->setNextWaypoint(m_waypoints[0]);
		// 		}
		// 		else {
		// 			std::cout << "waypoint: " << i << " previous set to " << i - 1 << " next set to: " << i + 1 << std::endl;
		// 			m_waypoints[i]->setPreviousWaypoint(m_waypoints[i - 1]);
		// 			m_waypoints[i]->setNextWaypoint(m_waypoints[i + 1]);
		// 		}
		// 	}
		// }
	}
	~WaypointSystem()
	{
		for (unsigned int i = 0; i < m_waypoints.size(); i++)
		{
			delete m_waypoints[i];
		}
		m_waypoints.clear();
		
	}

	

};