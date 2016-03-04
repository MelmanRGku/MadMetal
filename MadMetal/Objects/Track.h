#pragma once
#include "Object.h"
#include "Game Logic\WayPointSystem.h"
#include "Game Logic\PowerUp.h"
#include "Audio\Sound.h"

class Track
{
public:
	Track(){}
	~Track()
	{
		m_trackMusic = NULL;
		
		m_powerUps.clear();
		for (int i = 0; i < m_collisionsVolumes.size(); i++)
		{
			delete m_collisionsVolumes[i];
		}
		m_collisionsVolumes.clear();

		
		for (int i = 0; i < m_powerUps.size(); i++)
		{
			delete m_powerUps[i];
		}
		delete m_wayPointSystem;
		m_track = NULL;

	}

private: //members
	//peices of the physics track and the renderable surface
	Object * m_track;
	//load from file
	WaypointSystem * m_wayPointSystem;
	std::vector<Object *> m_powerUps;
	std::vector<Object *> m_collisionsVolumes;
	Sound * m_trackMusic;
	
};
