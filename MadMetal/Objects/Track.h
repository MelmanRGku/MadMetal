#pragma once

#include "Object3D.h"
#include "Game Logic\WaypointDefinitions.h"

class WaypointSystem;
class Waypoint;
class CollisionVolume;


class Track : public Object3D
{
public:
	Track(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Object3D *drivablePart, Object3D *nonDrivablePart, Object3D* trackWalls);
	~Track();
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);

	Object3D *getDrivablePart() { return drivablePart; }
	
	void playTrackMusic();
	CollisionVolume * getStartLine();
private: //members
	Object3D *drivablePart,
		*nonDrivablePart,
		*trackWalls;
	std::vector<CollisionVolume*> m_collisionVolumes;
private: //helper functions 

	void setupCollisionVolumes();
	
	void attachNextCollsionVolumes();
	void attachReachableCollsionVolumes();
};
