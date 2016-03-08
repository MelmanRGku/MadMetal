#pragma once

#define WORLD_SIZE 64

class Waypoint;

class SearchWaypoint
{
public: //Constuctors
	SearchWaypoint(Waypoint& waypoint, SearchWaypoint* parent = 0, float G = 0, float H = 0);
	virtual ~SearchWaypoint();
	float GetF();
	float ManHattanDistance(SearchWaypoint * endNode);
	Waypoint& getWaypoint();

	void setParent(SearchWaypoint* parent);
	void setH(float H);
	void setG(float G);
	float getG();
	float getH();

	void setHighCost(float highCost);
	float getHighCost();
	SearchWaypoint* getParent();

private: //members
	Waypoint& m_waypoint;
	SearchWaypoint * m_parent;
	
	float m_G;
	float m_H;
	float m_highCost;
};