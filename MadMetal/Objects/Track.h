#pragma once

#include "TestObject.h"

class WaypointSystem;
class Waypoint;

enum Boundry
{
	TOP = 1,
	BOTTOM = 2,
	LEFT = 3,
	RIGHT = 4,
};

class Track : public TestObject
{
public:
	Track(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable *rable, TestObject *drivablePart, TestObject *nonDrivablePart);
	~Track();
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	TestObject *getDrivablePart() { return drivablePart; }
	Waypoint * getWaypointAt(int index);

	void playTrackMusic();

private: //members
	TestObject *drivablePart,
		*nonDrivablePart;
	std::vector<WaypointSystem*> m_waypointSystems;
	std::vector<Waypoint*> m_waypointList;
private: //helper functions 
	void stitchWaypointSystems(Boundry lastWaypointSystemLocation, Boundry newWaypointSystemPosition, WaypointSystem& lastWaypointSystem, WaypointSystem& newWaypointSystem, int lastWaypointSystemIntialPosition, int newWaypointSystemIntialPosition);
	void determineStitchingBoundaries(Boundry locationOfStiching, int initialPosition, bool& isStichingRow, int& RowIndex, int& ColumnIndex, WaypointSystem& system);
	void stitch(WaypointSystem& waypointSystem1, bool isRowStiching1, int limitOfStichingIteration1, int indexOfEdge1, WaypointSystem& waypointSystem2, bool isRowStiching2, int limitOfStichingIteration2, int indexOfEdge2);
	void determinePlaceInAdjecencyListAndPush(WaypointSystem& waypointSystem1, bool isRowStiching1, int indexOfEdge1, int indexOfIncrement1, WaypointSystem& waypointSystem2, bool isRowStiching2, int indexOfEdge2, int indexOfIncrement2);

};