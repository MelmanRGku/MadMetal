#pragma once

#include "Object3D.h"
#include "Game Logic\WaypointDefinitions.h"

class WaypointSystem;
class Waypoint;


class Track : public Object3D
{
public:
	Track(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Object3D *drivablePart, Object3D *nonDrivablePart);
	~Track();
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	Waypoint * getWaypointAt(int index);
	Object3D *getDrivablePart() { return drivablePart; }
	
	void playTrackMusic();

private: //members
	Object3D *drivablePart,
		*nonDrivablePart;
	std::vector<WaypointSystem*> m_waypointSystems;
	std::vector<Waypoint*> m_waypointList;
private: //helper functions 
	void stitchWaypointSystems(Boundry lastWaypointSystemLocation, Boundry newWaypointSystemPosition, WaypointSystem& lastWaypointSystem, WaypointSystem& newWaypointSystem, int lastWaypointSystemIntialPosition, int newWaypointSystemIntialPosition, bool recalculateIds);
	void determineStitchingBoundaries(Boundry locationOfStiching, int initialPosition, bool& isStichingRow, int& RowIndex, int& ColumnIndex, WaypointSystem& system);
	void stitch(WaypointSystem& waypointSystem1, bool isRowStiching1, int limitOfStichingIteration1, int indexOfEdge1, WaypointSystem& waypointSystem2, bool isRowStiching2, int limitOfStichingIteration2, int indexOfEdge2);
	void determinePlaceInAdjecencyListAndPush(WaypointSystem& waypointSystem1, bool isRowStiching1, int indexOfEdge1, int indexOfIncrement1, WaypointSystem& waypointSystem2, bool isRowStiching2, int indexOfEdge2, int indexOfIncrement2);
};
