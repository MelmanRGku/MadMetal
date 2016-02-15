#pragma once
#include "Libraries\glm\glm.hpp"
#include "Simulation\PhysicsManager.h"
#include <vector>
#include <iostream>


#define WAYPOINT_DIMENSION_X 4

class WayPoint
{

	WayPoint * m_next;
	WayPoint * m_previous;
	glm::vec3 &m_position;
public:
	WayPoint(glm::vec3 position) : m_position(position){}
	~WayPoint()
	{
		delete m_next;
		delete m_previous;
	}
	void setNextWayPoint(WayPoint * next){ m_next = next; }
	void setPreviousWayPoint(WayPoint * previous) { m_previous = previous; }
	WayPoint * getNextWayPoint(){ return m_next; }
	WayPoint * getPreviousWayPoint() { return m_previous; }


};

class WayPointSystem
{
	std::vector<WayPoint *> m_wayPoints;

public:
	
	WayPoint * getWayPointAt(int index) { return m_wayPoints[index]; }

	/*
		Current System is always a circular track with first position supplied assumed to be the finish line
	*/
	WayPointSystem(PxScene * physicsScene, std::vector<glm::vec3> positions)
	{
		PxRigidActor * tempActor;
		PxShape * tempShape;
		PxMaterial * dummyMaterial = physicsScene->getPhysics().createMaterial(0, 0, 0);

		//initialize waypoints
		for (unsigned int i = 0; i < positions.size(); i++)
		{
			//add waypoint to the list
			m_wayPoints.push_back(new WayPoint(positions[i]));
			//create a mirror trigger volume in scene
			tempActor = physicsScene->getPhysics().createRigidStatic(PxTransform(positions[i].x, positions[i].y, positions[i].z));
			tempShape = tempActor->createShape(PxBoxGeometry(WAYPOINT_DIMENSION_X, WAYPOINT_DIMENSION_X, 1), *dummyMaterial);
			tempShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
			tempShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

			//set word2 to index of way point in system
			
			PhysicsManager::setupFiltering(
				tempActor, 
				PhysicsManager::WAYPOINT, 
				PhysicsManager::PLAYER, 
				i,				 //index of waypoint in list
				i == 0 ? 1 : 0); //if first waypoint, set info to finishline

			physicsScene->addActor(*tempActor);
		}

		if (m_wayPoints.size() > 1)
		{
			//connect way points
			for (unsigned int i = 0; i < m_wayPoints.size(); i++)
			{
				if (i == 0)
				{
					std::cout << "waypoint: " << i << " previous set to " << m_wayPoints.size() - 1 << " next set to: " << i + 1 << std::endl;
					m_wayPoints[i]->setPreviousWayPoint(m_wayPoints[m_wayPoints.size() - 1]);
					m_wayPoints[i]->setNextWayPoint(m_wayPoints[i + 1]);
					
				}
				else if (i == m_wayPoints.size() - 1)
				{
					std::cout << "waypoint: " << i << " previous set to " << i - 1 << " next set to: " << 0 << std::endl;
					m_wayPoints[i]->setPreviousWayPoint(m_wayPoints[i - 1]);
					m_wayPoints[i]->setNextWayPoint(m_wayPoints[0]);
				}
				else {
					std::cout << "waypoint: " << i << " previous set to " << i - 1 << " next set to: " << i + 1 << std::endl;
					m_wayPoints[i]->setPreviousWayPoint(m_wayPoints[i - 1]);
					m_wayPoints[i]->setNextWayPoint(m_wayPoints[i + 1]);
				}
			}
		}
	}
	~WayPointSystem()
	{
		for (unsigned int i = 0; i < m_wayPoints.size(); i++)
		{
			delete m_wayPoints[i];
		}
		m_wayPoints.clear();
		
	}

	

};