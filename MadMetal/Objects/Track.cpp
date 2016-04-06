#include "Track.h"
#include "Waypoint.h"
#include "Game Logic\WayPointSystem.h"
#include "Game Logic\WaypointDefinitions.h"
#include "Objects\CollisionVolume.h"
#include "ObjectLoaders\ObjModelLoader.h"

Track::Track(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Object3D *drivablePart, Object3D *nonDrivablePart, Object3D* trackWalls) : Object3D(id, aable, pable, anable, rable, NULL), drivablePart(drivablePart), nonDrivablePart(nonDrivablePart), trackWalls(trackWalls)
{
	
	ObjModelLoader *loader = new ObjModelLoader();
	NavigationalGrid *model = loader->loadNavGridFromFile("Assets/NavigationalGrid/trackv3ground.obj");

	std::cout << "hello";

	WaypointSystem * navigationalGrid = new WaypointSystem(*model);

	m_waypointSystems.push_back(navigationalGrid);

	delete model;
	delete loader;
//	WaypointSystem * startLocation = new WaypointSystem(
//		getDrivablePart()->getWorldBounds().maximum.x - 180,
//		getDrivablePart()->getWorldBounds().maximum.x - 140,
//		getDrivablePart()->getWorldBounds().minimum.z + 200,
//		getDrivablePart()->getWorldBounds().minimum.z + 360,
//		getDrivablePart()->getWorldBounds().maximum.y,
//		TOP);
//
//	for (int i = 0; i < startLocation->getWaypointMap().size(); i++)
//	{
//		m_waypointList.insert(m_waypointList.end(), startLocation->getWaypointMap().at(i).begin(), startLocation->getWaypointMap().at(i).end());
//}
//
//	m_waypointSystems.push_back(startLocation);
//
//	WaypointSystem * nextLocation1 = new WaypointSystem(
//		getDrivablePart()->getWorldBounds().maximum.x - 280,
//		getDrivablePart()->getWorldBounds().maximum.x - 40,
//		getDrivablePart()->getWorldBounds().minimum.z + 360,
//		getDrivablePart()->getWorldBounds().maximum.z - 520,
//		getDrivablePart()->getWorldBounds().maximum.y,
//		TOP);
//
//	for (int i = 0; i < nextLocation1->getWaypointMap().size(); i++)
//	{
//		m_waypointList.insert(m_waypointList.end(), nextLocation1->getWaypointMap().at(i).begin(), nextLocation1->getWaypointMap().at(i).end());
//	}
//	WaypointSystem* lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
//	stitchWaypointSystems(BOTTOM, TOP, *lastWaypointSystem, *nextLocation1, 0, 5, true);
//
//	m_waypointSystems.push_back(nextLocation1);
//
//	//setInvalid1();
//
//	WaypointSystem * nextLocation2 = new WaypointSystem(
//		getDrivablePart()->getWorldBounds().maximum.x - 180,
//		getDrivablePart()->getWorldBounds().maximum.x - 140,
//		getDrivablePart()->getWorldBounds().maximum.z - 520,
//		getDrivablePart()->getWorldBounds().maximum.z - 60,
//		getDrivablePart()->getWorldBounds().maximum.y,
//		TOP);
//
//	for (int i = 0; i < nextLocation2->getWaypointMap().size(); i++)
//	{
//		m_waypointList.insert(m_waypointList.end(), nextLocation2->getWaypointMap().at(i).begin(), nextLocation2->getWaypointMap().at(i).end());
//	}
//
//	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
//	stitchWaypointSystems(BOTTOM, TOP, *lastWaypointSystem, *nextLocation2, 5, 0, true);
//
//	m_waypointSystems.push_back(nextLocation2);
//
//	WaypointSystem * nextLocation3 = new WaypointSystem(
//		getDrivablePart()->getWorldBounds().minimum.x + 40,
//		getDrivablePart()->getWorldBounds().maximum.x - 200,
//		getDrivablePart()->getWorldBounds().maximum.z - 100,
//		getDrivablePart()->getWorldBounds().maximum.z - 20,
//		getDrivablePart()->getWorldBounds().maximum.y,
//		RIGHT);
//
//	for (int i = 0; i < nextLocation3->getWaypointMap().size(); i++)
//	{
//		m_waypointList.insert(m_waypointList.end(), nextLocation3->getWaypointMap().at(i).begin(), nextLocation3->getWaypointMap().at(i).end());
//	}
//
//	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
//	stitchWaypointSystems(LEFT, RIGHT, *lastWaypointSystem, *nextLocation3, lastWaypointSystem->getWaypointMap().size() - 2, 0, true);
//
//	m_waypointSystems.push_back(nextLocation3);
//
//	//setInvalid2();
//
//	WaypointSystem * nextLocation4 = new WaypointSystem(
//		getDrivablePart()->getWorldBounds().minimum.x + 40,
//		getDrivablePart()->getWorldBounds().minimum.x + 140,
//		getDrivablePart()->getWorldBounds().maximum.z - 500,
//		getDrivablePart()->getWorldBounds().maximum.z - 100,
//		getDrivablePart()->getWorldBounds().maximum.y,
//		BOTTOM);
//
//	for (int i = 0; i < nextLocation4->getWaypointMap().size(); i++)
//	{
//		m_waypointList.insert(m_waypointList.end(), nextLocation4->getWaypointMap().at(i).begin(), nextLocation4->getWaypointMap().at(i).end());
//	}
//
//	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
//	stitchWaypointSystems(TOP, BOTTOM, *lastWaypointSystem, *nextLocation4, 0, 0, true);
//
//	m_waypointSystems.push_back(nextLocation4);
//
//	WaypointSystem * nextLocation5 = new WaypointSystem(
//		getDrivablePart()->getWorldBounds().minimum.x + 80,
//		getDrivablePart()->getWorldBounds().minimum.x + 180,
//		getDrivablePart()->getWorldBounds().maximum.z - 680,
//		getDrivablePart()->getWorldBounds().maximum.z - 500,
//		getDrivablePart()->getWorldBounds().maximum.y,
//		BOTTOM);
//	
//	for (int i = 0; i < nextLocation5->getWaypointMap().size(); i++)
//	{
//		m_waypointList.insert(m_waypointList.end(), nextLocation5->getWaypointMap().at(i).begin(), nextLocation5->getWaypointMap().at(i).end());
//	}
//	
//	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
//	stitchWaypointSystems(TOP, BOTTOM, *lastWaypointSystem, *nextLocation5, 2, 0, true);
//	
//	m_waypointSystems.push_back(nextLocation5);
//
//	WaypointSystem * nextLocation6 = new WaypointSystem(
//		getDrivablePart()->getWorldBounds().minimum.x + 180,
//		getDrivablePart()->getWorldBounds().minimum.x + 240,
//		getDrivablePart()->getWorldBounds().maximum.z - 1120,
//		getDrivablePart()->getWorldBounds().maximum.z - 620,
//		getDrivablePart()->getWorldBounds().maximum.y,
//		BOTTOM);
//
//	for (int i = 0; i < nextLocation6->getWaypointMap().size(); i++)
//	{
//		m_waypointList.insert(m_waypointList.end(), nextLocation6->getWaypointMap().at(i).begin(), nextLocation6->getWaypointMap().at(i).end());
//	}
//
//	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
//	stitchWaypointSystems(RIGHT, LEFT, *lastWaypointSystem, *nextLocation6, 0, nextLocation6->getWaypointMap().size() - 3, true);
//
//	m_waypointSystems.push_back(nextLocation6);
//
//	WaypointSystem * nextLocation7 = new WaypointSystem(
//		getDrivablePart()->getWorldBounds().minimum.x + 60,
//		getDrivablePart()->getWorldBounds().minimum.x + 180,
//		getDrivablePart()->getWorldBounds().maximum.z - 1220,
//		getDrivablePart()->getWorldBounds().maximum.z - 1040,
//		getDrivablePart()->getWorldBounds().maximum.y,
//		BOTTOM);
//
//	for (int i = 0; i < nextLocation7->getWaypointMap().size(); i++)
//	{
//		m_waypointList.insert(m_waypointList.end(), nextLocation7->getWaypointMap().at(i).begin(), nextLocation7->getWaypointMap().at(i).end());
//	}
//
//	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
//	stitchWaypointSystems(LEFT, RIGHT, *lastWaypointSystem, *nextLocation7, 0, nextLocation7->getWaypointMap().size() - 4, true);
//
//	m_waypointSystems.push_back(nextLocation7);
//
//	WaypointSystem * nextLocation8 = new WaypointSystem(
//		getDrivablePart()->getWorldBounds().minimum.x + 20,
//		getDrivablePart()->getWorldBounds().minimum.x + 60,
//		getDrivablePart()->getWorldBounds().minimum.z + 40,
//		getDrivablePart()->getWorldBounds().maximum.z - 1120,
//		getDrivablePart()->getWorldBounds().maximum.y,
//		BOTTOM);
//
//	for (int i = 0; i < nextLocation8->getWaypointMap().size(); i++)
//	{
//		m_waypointList.insert(m_waypointList.end(), nextLocation8->getWaypointMap().at(i).begin(), nextLocation8->getWaypointMap().at(i).end());
//	}
//
//	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
//	stitchWaypointSystems(LEFT, RIGHT, *lastWaypointSystem, *nextLocation8, 0, nextLocation8->getWaypointMap().size() - 5, true);
//
//	m_waypointSystems.push_back(nextLocation8);
//
//	WaypointSystem * nextLocation9 = new WaypointSystem(
//		getDrivablePart()->getWorldBounds().minimum.x + 60,
//		getDrivablePart()->getWorldBounds().minimum.x + 160,
//		getDrivablePart()->getWorldBounds().minimum.z + 20,
//		getDrivablePart()->getWorldBounds().minimum.z + 100,
//		getDrivablePart()->getWorldBounds().maximum.y,
//		LEFT);
//
//	for (int i = 0; i < nextLocation9->getWaypointMap().size(); i++)
//	{
//		m_waypointList.insert(m_waypointList.end(), nextLocation9->getWaypointMap().at(i).begin(), nextLocation9->getWaypointMap().at(i).end());
//	}
//
//	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
//	stitchWaypointSystems(RIGHT, LEFT, *lastWaypointSystem, *nextLocation9, 0, 1, true);
//
//	m_waypointSystems.push_back(nextLocation9);
//
//
//	WaypointSystem * nextLocation10 = new WaypointSystem(
//		getDrivablePart()->getWorldBounds().minimum.x + 160,
//		getDrivablePart()->getWorldBounds().maximum.x - 140,
//		getDrivablePart()->getWorldBounds().minimum.z + 20,
//		getDrivablePart()->getWorldBounds().minimum.z + 60,
//		getDrivablePart()->getWorldBounds().maximum.y,
//		LEFT);
//
//	for (int i = 0; i < nextLocation10->getWaypointMap().size(); i++)
//	{
//		m_waypointList.insert(m_waypointList.end(), nextLocation10->getWaypointMap().at(i).begin(), nextLocation10->getWaypointMap().at(i).end());
//	}
//
//	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
//	stitchWaypointSystems(RIGHT, LEFT, *lastWaypointSystem, *nextLocation10, 0, 0, true);
//
//	m_waypointSystems.push_back(nextLocation10);
//
//	WaypointSystem * nextLocation11 = new WaypointSystem(
//		getDrivablePart()->getWorldBounds().maximum.x - 180,
//		getDrivablePart()->getWorldBounds().maximum.x - 140,
//		getDrivablePart()->getWorldBounds().minimum.z + 60,
//		getDrivablePart()->getWorldBounds().minimum.z + 200,
//		getDrivablePart()->getWorldBounds().maximum.y,
//		TOP);
//
//	for (int i = 0; i < nextLocation11->getWaypointMap().size(); i++)
//	{
//		m_waypointList.insert(m_waypointList.end(), nextLocation11->getWaypointMap().at(i).begin(), nextLocation11->getWaypointMap().at(i).end());
//	}
//
//	lastWaypointSystem = m_waypointSystems.at(m_waypointSystems.size() - 1);
//	stitchWaypointSystems(BOTTOM, TOP, *lastWaypointSystem, *nextLocation11, lastWaypointSystem->getWaypointMap().at(0).size() - 2, 0, true);
//	lastWaypointSystem = m_waypointSystems.at(0);
//	stitchWaypointSystems(TOP, BOTTOM, *lastWaypointSystem, *nextLocation11, 0, 0, false);
//	//stitchWaypointSystems(BOTTOM, TOP, *nextLocation11, *m_waypointSystems.at(0), 0, 0, false);
//
//	m_waypointSystems.push_back(nextLocation11);
//
//	setValidPath();
//
//	PxTransform * pos;
//	PxGeometry **geom1 = new PxGeometry *[1];
//	PxGeometry **geom2 = new PxGeometry *[1];
//	PxGeometry **geom3 = new PxGeometry *[1];
//	geom1[0] = new PxBoxGeometry(PxVec3(80, getDrivablePart()->getWorldBounds().maximum.y, 10));
//	geom2[0] = new PxBoxGeometry(PxVec3(10, getDrivablePart()->getWorldBounds().maximum.y, 100));
//	geom3[0] = new PxBoxGeometry(PxVec3(80, getDrivablePart()->getWorldBounds().maximum.y, 20));
//	
//	/***************
//	3              4
//	2              
//	1              5
//	
//	0           6 
//	
//	             7 
//		           8 
//	      9         
//	*/
//	//clockwise 
//
//
//
//	CollisionVolume::globalID = 0;
//	//0
//	pos = new PxTransform(getWaypointAt(0)->getActor().getGlobalPose().p + PxVec3(10,0,0));
//	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom3, NULL)));
//	delete pos;
//	//1
//	pos = new PxTransform(getWaypointAt(367)->getActor().getGlobalPose().p + PxVec3(-20,0,0));
//	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
//	delete pos;
//	//2
//	pos = new PxTransform(getWaypointAt(550)->getActor().getGlobalPose());
//	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
//	delete pos;
//	//3
//	pos = new PxTransform(getWaypointAt(629)->getActor().getGlobalPose().p, PxQuat(3.14 / 2, PxVec3(0,-1,0)));
//	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom3, NULL)));
//	delete pos;
//	//4
//	pos = new PxTransform(getWaypointAt(813)->getActor().getGlobalPose().p + PxVec3(-20,0,0), PxQuat(3.14, PxVec3(0, -1, 0)));
//	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom2, NULL)));
//	delete pos;
//	//5
//	pos = new PxTransform(getWaypointAt(716)->getActor().getGlobalPose().p, PxQuat( 1.73758, PxVec3(0, 1, 0)));
//	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
//	delete pos;
//	//6
//	pos = new PxTransform(getWaypointAt(896)->getActor().getGlobalPose().p, PxQuat(3.14, PxVec3(0,1,0)));
//	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
//	delete pos;
//	//7
//	pos = new PxTransform(getWaypointAt(953)->getActor().getGlobalPose().p, PxQuat(2.61412, PxVec3(0, -1, 0)));
//	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom2, NULL)));
//	delete pos;
//	//8
//	pos = new PxTransform(getWaypointAt(1003)->getActor().getGlobalPose().p + PxVec3(-10,0,0), PxQuat(3.14, PxVec3(0,1,0)));
//	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
//	delete pos;
//	//9
//	pos = new PxTransform(getWaypointAt(1074)->getActor().getGlobalPose().p, PxQuat(3.14 / 2, PxVec3(0, 1, 0)));
//	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom2, NULL)));
//	delete pos;
//
//	delete geom1[0];
//	delete geom2[0];
//	delete geom3[0];
//	delete[] geom1;
//	delete[] geom2;
//	delete[] geom3;

	PxTransform * pos;
	PxGeometry **geom1 = new PxGeometry *[1];
	geom1[0] = new PxBoxGeometry(10, 10, 10);

	//startLine
	pos = new PxTransform(PxVec3(4, 0 ,-35));
	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));

	//path branch leading into the dessert
	pos = new PxTransform(PxVec3(0, 0 ,225));
	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));

	//top of the jump ramp in the dessert
	pos = new PxTransform(PxVec3(-30, 25, 325));
	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));

	//deathPit 1
	pos = new PxTransform(PxVec3(15, 0,515));
	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));

	//second death pit
	pos = new PxTransform(PxVec3(-25, 0, 860));
	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));

	//start of the canyon
	pos = new PxTransform(PxVec3(0, 0, 1100));
	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));

	//branch path in the canyon
	pos = new PxTransform(PxVec3(-45, 0, 1555));
	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));

	//landing platform in the goo pit
	pos = new PxTransform(PxVec3(-800, -30, 1550));
	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));

	//end of the first train tunnel
	pos = new PxTransform(PxVec3(-856, -30, 751));
	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));

	//maybe the ramp exit of tunnel :p
	pos = new PxTransform(PxVec3(-730, 0, 120));
	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));

	//entrence to the trafic circle
	pos = new PxTransform(PxVec3(-625, 0, -105));
	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));

	//top of the traffic circle
	pos = new PxTransform(PxVec3(-378, 6, 21.5));
	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));

	//bottom of the traffic circle
	pos = new PxTransform(PxVec3(-378, 6, -231.5));
	m_collisionVolumes.push_back(dynamic_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));


}

Track::~Track()
{
	for (std::vector<WaypointSystem*>::iterator it = m_waypointSystems.begin(); it != m_waypointSystems.end(); ++it)
	{
		delete *it;
	}

	for (std::vector<CollisionVolume*>::iterator it = m_collisionVolumes.begin(); it != m_collisionVolumes.end(); ++it)
	{
		//delete *it;
	}
}

bool Track::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	
	//do nothing
	return false;

}

void Track::playTrackMusic()
{
	m_audioable->getAudioHandle().playMusic(m_sound);
}

Waypoint * Track::getWaypointAt(int index)
{
	if (index < m_waypointList.size())
	{
		return m_waypointList[index];
	}
	else
	{
		std::cerr << "ERROR: trying to acquire out of index pointer\n";
		return NULL;
	}
}

void Track::stitchWaypointSystems(Boundry lastWaypointSystemLocation, Boundry newWaypointSystemPosition, WaypointSystem& lastWaypointSystem, WaypointSystem& newWaypointSystem, int lastWaypointSystemIntialPosition, int newWaypointSystemIntialPosition, bool recalculateIds)
{
	bool isStichingRowForLastWaypoint;
	int lastWaypointRowIndex;
	int lastWaypointColumnIndex;

	determineStitchingBoundaries(lastWaypointSystemLocation, lastWaypointSystemIntialPosition, isStichingRowForLastWaypoint, lastWaypointRowIndex, lastWaypointColumnIndex, lastWaypointSystem);

	bool isStichingRowForNewWaypoint;
	int newWaypointRowIndex;
	int newWaypointColumnIndex;

	determineStitchingBoundaries(newWaypointSystemPosition, newWaypointSystemIntialPosition, isStichingRowForNewWaypoint, newWaypointRowIndex, newWaypointColumnIndex, newWaypointSystem);

	if (isStichingRowForLastWaypoint)
	{
		if (isStichingRowForNewWaypoint)
		{
			stitch(lastWaypointSystem, isStichingRowForLastWaypoint, lastWaypointColumnIndex, lastWaypointRowIndex, newWaypointSystem, isStichingRowForNewWaypoint, newWaypointColumnIndex, newWaypointRowIndex);
			recalculateWaypointSystemIds(lastWaypointSystem, newWaypointSystem, recalculateIds);
		}
		else
		{
			std::cerr << "Cannot Stitch row to column\n";
		}
	}
	else
	{
		if (isStichingRowForNewWaypoint)
		{
			std::cerr << "Cannot Stitch column to row\n";
		}
		else
		{
			stitch(lastWaypointSystem, isStichingRowForLastWaypoint, lastWaypointRowIndex, lastWaypointColumnIndex, newWaypointSystem, isStichingRowForNewWaypoint, newWaypointRowIndex, newWaypointColumnIndex);

			recalculateWaypointSystemIds(lastWaypointSystem, newWaypointSystem, recalculateIds);
		}
	}


	//for (int i = 0; i < m_waypointList.size(); i++)
	//{
	//	std::cout << "waypoint: " << m_waypointList[i]->getIndex() << " " << " and is connected to ";
	//	for (int k = 0; k < m_waypointList[i]->getListOfAdjacentWaypoints().size(); k++)
	//	{
	//		std::cout << m_waypointList[i]->getListOfAdjacentWaypoints().at(k)->getIndex() << ", ";
	//	}
	//	std::cout << "\n";
	//}

}

void Track::determineStitchingBoundaries(Boundry locationOfStiching, int initialPosition,  bool& isStichingRow, int& RowIndex, int& ColumnIndex, WaypointSystem& system)
{
	switch (locationOfStiching)
	{
	case TOP:
		isStichingRow = true;
		RowIndex = 0;
		ColumnIndex = initialPosition;
		break;
	case BOTTOM:
		isStichingRow = true;
		RowIndex = system.getWaypointMap().size() - 1;
		ColumnIndex = initialPosition;
		break;
	case LEFT:
		isStichingRow = false;
		RowIndex = initialPosition;
		ColumnIndex = 0;
		break;
	case RIGHT:
		isStichingRow = false;
		RowIndex = initialPosition;
		ColumnIndex = system.getWaypointMap().at(0).size() - 1;
		break;
	}
}

void Track::stitch(WaypointSystem& waypointSystem1, bool isRowStiching1, int limitOfStichingIteration1, int indexOfEdge1, WaypointSystem& waypointSystem2, bool isRowStiching2, int limitOfStichingIteration2, int indexOfEdge2)
{
	int waypointSystem1EdgeLimit;
	int waypointSystem2EdgeLimit;

	isRowStiching1 ? waypointSystem1EdgeLimit = waypointSystem1.getWaypointMap().at(0).size() : waypointSystem1EdgeLimit = waypointSystem1.getWaypointMap().size();
	isRowStiching2 ? waypointSystem2EdgeLimit = waypointSystem2.getWaypointMap().at(0).size() : waypointSystem2EdgeLimit = waypointSystem2.getWaypointMap().size();

	for (int i = limitOfStichingIteration1, j = limitOfStichingIteration2;
		i < waypointSystem1EdgeLimit &&
		j < waypointSystem2EdgeLimit;
	i++, j++)
	{
		if ((j - 1) >= 0)
		{
			determinePlaceInAdjecencyListAndPush(waypointSystem1, isRowStiching1, indexOfEdge1, i, waypointSystem2, isRowStiching2, indexOfEdge2, j - 1);
		}

		determinePlaceInAdjecencyListAndPush(waypointSystem1, isRowStiching1, indexOfEdge1, i, waypointSystem2, isRowStiching2, indexOfEdge2, j);

		if ((j + 1) < waypointSystem2EdgeLimit)
		{
			determinePlaceInAdjecencyListAndPush(waypointSystem1, isRowStiching1, indexOfEdge1, i, waypointSystem2, isRowStiching2, indexOfEdge2, j + 1);
		}

		if ((i - 1) >= 0)
		{
			determinePlaceInAdjecencyListAndPush(waypointSystem2, isRowStiching2, indexOfEdge2, j, waypointSystem1, isRowStiching1, indexOfEdge1, i - 1);
		}

		determinePlaceInAdjecencyListAndPush(waypointSystem2, isRowStiching2, indexOfEdge2, j, waypointSystem1, isRowStiching1, indexOfEdge1, i);

		if ((i + 1) < waypointSystem1EdgeLimit)
		{
			determinePlaceInAdjecencyListAndPush(waypointSystem2, isRowStiching2, indexOfEdge2, j, waypointSystem1, isRowStiching1, indexOfEdge1, i + 1);
		}
	}
}

void Track::determinePlaceInAdjecencyListAndPush(WaypointSystem& waypointSystem1, bool isRowStiching1, int indexOfEdge1, int indexOfIncrement1, WaypointSystem& waypointSystem2, bool isRowStiching2, int indexOfEdge2, int indexOfIncrement2)
{
	if (isRowStiching1 && isRowStiching2)
	{
		waypointSystem1.getWaypointMap().at(indexOfEdge1).at(indexOfIncrement1)->getListOfAdjacentWaypoints().push_back(
			waypointSystem2.getWaypointMap().at(indexOfEdge2).at(indexOfIncrement2));
	}
	else if (isRowStiching1 && !isRowStiching2)
	{
		waypointSystem1.getWaypointMap().at(indexOfEdge1).at(indexOfIncrement1)->getListOfAdjacentWaypoints().push_back(
			waypointSystem2.getWaypointMap().at(indexOfIncrement2).at(indexOfEdge2)); 
	}
	else if (isRowStiching2 && !isRowStiching1)
	{
		waypointSystem1.getWaypointMap().at(indexOfIncrement1).at(indexOfEdge1)->getListOfAdjacentWaypoints().push_back(
			waypointSystem2.getWaypointMap().at(indexOfEdge2).at(indexOfIncrement2));
	}
	else
	{
		waypointSystem1.getWaypointMap().at(indexOfIncrement1).at(indexOfEdge1)->getListOfAdjacentWaypoints().push_back(
			waypointSystem2.getWaypointMap().at(indexOfIncrement2).at(indexOfEdge2));
	}
}

void Track::recalculateWaypointSystemIds(WaypointSystem& waypointSystem1, WaypointSystem& waypointSystem2, bool& recalculateIds)
{
	if (recalculateIds)
	{
		int difference1 = abs(waypointSystem1.getWaypointMap().at(waypointSystem1.getWaypointMap().size() - 1).at(waypointSystem1.getWaypointMap().at(0).size() - 1)->getId() -
			waypointSystem2.getWaypointMap().at(0).at(waypointSystem2.getWaypointMap().at(0).size() - 1)->getId());
		int secondValue = waypointSystem1.getWaypointMap().at(waypointSystem1.getWaypointMap().size() - 1).at(waypointSystem1.getWaypointMap().at(0).size() - 1)->getId() == waypointSystem1.getWaypointMap().at(0).at(waypointSystem1.getWaypointMap().at(0).size() - 1)->getId() ?
			waypointSystem1.getWaypointMap().at(0).at(0)->getId() :
			waypointSystem1.getWaypointMap().at(0).at(waypointSystem1.getWaypointMap().at(0).size() - 1)->getId();
		int difference2 = abs(secondValue -
			waypointSystem2.getWaypointMap().at(0).at(waypointSystem2.getWaypointMap().at(0).size() - 1)->getId());

		if (difference1 > difference2)
		{
			waypointSystem2.addIdToAllWaypointsInTheSystem(waypointSystem1.getWaypointMap().at(waypointSystem1.getWaypointMap().size() - 1).at(waypointSystem1.getWaypointMap().at(0).size() - 1)->getId());
		}
		else
		{
			waypointSystem2.addIdToAllWaypointsInTheSystem(secondValue);
		}
	}
}

//void Track::setInvalid2()
//{
//	for (int i = 578; i < 592; i += 2)
//	{
//		m_waypointList[i]->setValid(false);
//	}
//
//	for (int i = 602; i < 714; i++)
//	{
//		if ((i > 605 && i < 623) ||
//			(i > 637 && i < 647) ||
//			(i > 649 && i < 664) ||
//			//(i > 668 && i < 673) ||
//			(i > 676 && i < 685) ||
//			(i > 689 && i < 714))
//		{
//			m_waypointList[i]->setValid(false);
//
//			//std::cout << "making invalid: " << m_waypointList[i]->getIndex() << "\n";
//		}
//	}
//}
//
//
//void Track::setInvalid1()
//{
//	m_waypointList[0]->setValid(false);
//	m_waypointList[1]->setValid(false);
//
//	m_waypointList[2]->setValid(false);
//	m_waypointList[4]->setValid(false);
//	m_waypointList[6]->setValid(false);
//	m_waypointList[8]->setValid(false);
//	m_waypointList[10]->setValid(false);
//	m_waypointList[12]->setValid(false);
//	m_waypointList[14]->setValid(false);
//
//	for (int i = 16; i < 555; i++)
//	{
//		if ((i > 16 && i < 21) ||
//			(i > 22 && i < 33) ||
//			(i > 34 && i < 45) ||
//			(i > 46 && i < 58) ||
//			(i > 59 && i < 70) ||
//			(i > 71 && i < 82) ||
//			(i > 83 && i < 94) ||
//			(i > 95 && i < 105) ||
//			(i > 107 && i < 118) ||
//			(i > 120 && i < 131) ||
//			(i > 132 && i < 143) ||
//			(i > 144 && i < 155) ||
//			(i > 157 && i < 168) ||
//			(i > 170 && i < 180) ||
//			(i > 182 && i < 193) ||
//			(i > 195 && i < 205) ||
//			(i > 207 && i < 217) ||
//			(i > 219 && i < 229) ||
//			(i > 231 && i < 241) ||
//			(i > 243 && i < 252) ||
//			(i > 255 && i < 264) ||
//			(i > 266 && i < 276) ||
//			(i > 277 && i < 287) ||
//
//
//			(i > 289 && i < 298) ||
//			(i > 300 && i < 310) ||
//			(i > 311 && i < 321) ||
//			(i > 322 && i < 333) ||
//			(i > 334 && i < 344) ||
//			(i > 345 && i < 355) ||
//			(i > 356 && i < 366) ||
//			(i > 367 && i < 378) ||
//			(i > 379 && i < 390) ||
//			(i > 391 && i < 402) ||
//			(i > 402 && i < 414) ||
//			(i > 414 && i < 426) ||
//			(i > 426 && i < 438) ||
//			(i > 438 && i < 451) ||
//			(i > 451 && i < 463) ||
//			(i > 463 && i < 475) ||
//			(i > 476 && i < 487) ||
//			(i > 488 && i < 500) ||
//			(i > 502 && i < 513) ||
//			(i > 513 && i < 524) ||
//			(i > 524 && i < 537) ||
//			(i > 537 && i < 550) ||
//			(i > 550 && i < 555))
//		{
//			m_waypointList[i]->setValid(false);
//
//			//std::cout << "making invalid: " << m_waypointList[i]->getIndex() << "\n";
//		}
//	}
//}
//
//void Track::setInvalid3()
//{
//	for (int i = 780; i < 802; i++)
//	{
//		if ((i > 779 && i < 783) ||
//			(i > 784 && i < 788) ||
//			(i > 789 && i < 793) ||
//			(i > 799 && i < 803))
//		{
//			m_waypointList[i]->setValid(false);
//		}
//	}
//
//	for (int i = 725; i < 773; i++)
//	{
//		if ((i > 726 && i < 729) ||
//			(i > 760 && i < 764) ||
//			(i > 786 && i < 769) ||
//			(i > 772 && i < 774))
//		{
//			m_waypointList[i]->setValid(false);
//		}
//	}
//
//	for (int i = 739; i < 750; i++)
//	{
//		if ((i > 738 && i < 741) ||
//			(i > 743 && i < 746) ||
//			(i > 748 && i < 751))
//		{
//			m_waypointList[i]->setValid(false);
//		}
//	}
//
//	for (int i = 714; i < 733; i++)
//	{
//		if ( i != 716 ||
//			 i != 721 || 
//			 i != 726 || 
//			 i != 711 )
//		{
//			m_waypointList[i]->setValid(false);
//		}
//	}
//
//}

void Track::setValidPath()
{
	std::vector<int> validWaypoints{ 0, 1054, 1059, 1070, 1095, 1132, 1133, 673, 1131, 1, 3, 5, 7, 9, 11, 13, 15, 22, 34, 46, 58, 70, 82, 83, 95, 107, 119, 120, 132, 144, 156, 157, 169, 181, 182, 194, 206, 218, 230, 242, 254, 266, 265, 277, 276, 288, 300, 299, 311, 310, 322, 321, 333, 345, 344, 356, 355, 367, 366, 378, 390, 389, 401, 413, 425, 437, 449, 450, 462, 474, 475, 487, 488, 500, 501, 513, 525, 526, 538, 550, 557, 559, 561, 563, 565, 567, 569, 571, 573, 575, 577, 579, 581, 583, 585, 587, 589, 591, 593, 598, 605, 594, 596, 629, 628, 627, 626, 625, 652, 651, 650, 649, 648, 675, 674, 673, 672, 700, 699, 698, 670, 669, 668, 667, 666, 665, 664, 663, 662, 661, 633, 660, 812, 807, 802, 798, 797, 792, 787, 782, 781, 776, 771, 766, 761, 756, 751, 746, 741, 736, 731, 726, 721, 716, 855, 856, 717, 850, 845, 846, 841, 836, 837, 832, 833, 828, 931, 928, 925, 922, 672, 919, 917, 914, 911, 908, 905, 902, 899, 896, 893, 890, 887, 884, 881, 878, 875, 874, 871, 868, 987, 981, 980, 974, 973, 967, 966, 960, 959, 953, 952, 946, 940, 1043, 1041, 1039, 1037, 1036, 1034, 1032, 1030, 1028, 1026, 1024, 1022, 1020, 1018, 1016, 1014, 1012, 1010, 1008, 1006, 1004, 1005, 1002, 1003, 1001, 1065, 995, 997, 1000, 999, 1066, 1061, 1057, 1058, 1054, 1070, 1071, 1072, 1100, 1101, 1102, 1103, 1104, 1105, 1106, 1107, 1108, 1109, 1110, 1111,  1086, 1087, 1088, 1089, 1090, 1091, 1092, 1117, 1118, 1120, 1122, 1123, 1093, 1116, 1115, 1114, 1080, 1112, 1113, 1119, 1121, 1125, 1127, 1129};

	for (int i = 0; i < validWaypoints.size(); i++)
	{
		m_waypointList[validWaypoints.at(i)]->setValid(true);
	}
}
