#include "Track.h"
#include "Waypoint.h"
#include "Game Logic\WayPointSystem.h"
#include "Game Logic\WaypointDefinitions.h"
#include "Objects\CollisionVolume.h"
#include "ObjectLoaders\ObjModelLoader.h"

Track::Track(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Object3D *drivablePart, Object3D *nonDrivablePart, Object3D* trackWalls) : Object3D(id, aable, pable, anable, rable, NULL), drivablePart(drivablePart), nonDrivablePart(nonDrivablePart), trackWalls(trackWalls)
{
	
	ObjModelLoader *loader = new ObjModelLoader();
	NavigationalGrid *model = loader->loadNavGridFromFile("Assets/NavigationalGrid/trackv3ground4.obj");

	std::cout << "hello";

	WaypointSystem * navigationalGrid = new WaypointSystem(*model);

	m_waypointList = navigationalGrid->getWaypointList();

	m_waypointSystems.push_back(navigationalGrid);

	delete model;
	delete loader;
	
	setupCollisionVolumes();
}

Track::~Track()
{
	for (std::vector<WaypointSystem*>::iterator it = m_waypointSystems.begin(); it != m_waypointSystems.end(); ++it)
	{
		delete *it;
	}
}

void Track::setupCollisionVolumes() {
	CollisionVolume *startLine = NULL,
		*pathBranchLeadingIntoTheDessert = NULL,
		*topOfTheJumpRampInTheDesert = NULL,
		*deathPit1 = NULL,
		*deathPit2 = NULL,
		*startOfTheCanyon = NULL,
		*branchPathInTheCanyon = NULL,
		*landingPlatformInTheGooPit = NULL,
		*endOfTheFirstTrainTunnel = NULL,
		*maybeTheRampExitInTheTunnel = NULL,
		*entranceToTheTrafficCircle = NULL,
		*topOfTheTrafficCircle = NULL,
		*bottomOfTheTrafficCircle = NULL;
	
	PxTransform * pos;
	PxGeometry **geom1 = new PxGeometry *[1];
	geom1[0] = new PxBoxGeometry(50, 10, 10);
	std::vector<PxVec3> respawnLocations;
	//startLine
	pos = new PxTransform(PxVec3(4, 0, -35));
	startLine = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	startLine->setGoalWaypointIndex(getWaypointAt(7));
	startLine->setCurrentWaypointIndex(getWaypointAt(48));
	m_collisionVolumes.push_back(startLine);
	respawnLocations.push_back(PxVec3(25, 20, -35));
	respawnLocations.push_back(PxVec3(5, 20, -35));
	respawnLocations.push_back(PxVec3(-15, 20, -35));
	respawnLocations.push_back(PxVec3(25, 20, -60));
	respawnLocations.push_back(PxVec3(5, 20, -60));
	respawnLocations.push_back(PxVec3(-15, 20, -60));
	startLine->setRespawnLocations(respawnLocations);
	startLine->setIsStartCollisionVolume(true);
	respawnLocations.clear();

	//path branch leading into the dessert
	pos = new PxTransform(PxVec3(15, 0, 225));
	geom1[0] = new PxBoxGeometry(25, 10, 10);
	respawnLocations.push_back(PxVec3(25, 20, 225));
	respawnLocations.push_back(PxVec3(5, 20, 225));
	respawnLocations.push_back(PxVec3(25, 20, 200));
	respawnLocations.push_back(PxVec3(5, 20, 200));
	pathBranchLeadingIntoTheDessert = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	pathBranchLeadingIntoTheDessert->setGoalWaypointIndex(getWaypointAt(7));
	pathBranchLeadingIntoTheDessert->setCurrentWaypointIndex(getWaypointAt(84));
	m_collisionVolumes.push_back(pathBranchLeadingIntoTheDessert);
	pathBranchLeadingIntoTheDessert->setRespawnLocations(respawnLocations);
	respawnLocations.clear();

	//top of the jump ramp in the dessert
	pos = new PxTransform(PxVec3(-30, 25, 325));
	topOfTheJumpRampInTheDesert = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	m_collisionVolumes.push_back(topOfTheJumpRampInTheDesert);

	//deathPit 1
	geom1[0] = new PxBoxGeometry(40, 15, 48);
	respawnLocations.push_back(PxVec3(25, 20, 525));
	respawnLocations.push_back(PxVec3(5, 20, 525));
	respawnLocations.push_back(PxVec3(25, 20, 500));
	respawnLocations.push_back(PxVec3(5, 20, 500));
	pos = new PxTransform(PxVec3(15, 0, 450));
	deathPit1 = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	deathPit1->setGoalWaypointIndex(getWaypointAt(216));
	deathPit1->setCurrentWaypointIndex(getWaypointAt(1014));
	m_collisionVolumes.push_back(deathPit1);
	deathPit1->setRespawnLocations(respawnLocations);
	respawnLocations.clear();

	//second death pit
	geom1[0] = new PxBoxGeometry(40, 15, 55);
	respawnLocations.push_back(PxVec3(-35, 20, 865));
	respawnLocations.push_back(PxVec3(-15, 20, 865));
	respawnLocations.push_back(PxVec3(-35, 20, 840));
	respawnLocations.push_back(PxVec3(-15, 20, 840));
	pos = new PxTransform(PxVec3(-25, 0, 760));
	deathPit2 = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	m_collisionVolumes.push_back(deathPit2);
	deathPit2->setRespawnLocations(respawnLocations);
	deathPit2->setGoalWaypointIndex(getWaypointAt(260));
	deathPit2->setCurrentWaypointIndex(getWaypointAt(16));
	respawnLocations.clear();
	
	//start of the canyon
	geom1[0] = new PxBoxGeometry(40, 15, 55);
	respawnLocations.push_back(PxVec3(-15, 20, 1100));
	respawnLocations.push_back(PxVec3(15, 20, 1100));
	respawnLocations.push_back(PxVec3(-15, 20, 1075));
	respawnLocations.push_back(PxVec3(15, 20, 1075));
	pos = new PxTransform(PxVec3(0, -5, 1100));
	startOfTheCanyon = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	m_collisionVolumes.push_back(startOfTheCanyon);
	startOfTheCanyon->setGoalWaypointIndex(getWaypointAt(229));
	startOfTheCanyon->setCurrentWaypointIndex(getWaypointAt(260));
	startOfTheCanyon->setRespawnLocations(respawnLocations);
	respawnLocations.clear();

	//branch path in the canyon
	respawnLocations.push_back(PxVec3(-45, 20, 1560));
	respawnLocations.push_back(PxVec3(-20, 20, 1560));
	respawnLocations.push_back(PxVec3(-45, 20, 1540));
	respawnLocations.push_back(PxVec3(-25, 20, 1540));
	pos = new PxTransform(PxVec3(-45, 0, 1555), PxQuat(1.6203, PxVec3(0, -1, 0)));
	branchPathInTheCanyon = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	branchPathInTheCanyon->setGoalWaypointIndex(getWaypointAt(229));
	branchPathInTheCanyon->setCurrentWaypointIndex(getWaypointAt(260));
	m_collisionVolumes.push_back(branchPathInTheCanyon);
	branchPathInTheCanyon->setRespawnLocations(respawnLocations);
	respawnLocations.clear();

	//landing platform in the goo pit
	geom1[0] = new PxBoxGeometry(300, 15, 300);
	respawnLocations.push_back(PxVec3(-870, 20, 1575));
	respawnLocations.push_back(PxVec3(-870, 20, 1550));
	respawnLocations.push_back(PxVec3(-870, 20, 1525));
	
	respawnLocations.push_back(PxVec3(-840, 20, 1575));
	respawnLocations.push_back(PxVec3(-840, 20, 1550));
	respawnLocations.push_back(PxVec3(-840, 20, 1525));
	pos = new PxTransform(PxVec3(-640, -30, 1550), PxQuat(1.6203, PxVec3(0, -1, 0)));
	landingPlatformInTheGooPit = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	landingPlatformInTheGooPit->setGoalWaypointIndex(getWaypointAt(564));
	landingPlatformInTheGooPit->setCurrentWaypointIndex(getWaypointAt(559));
	m_collisionVolumes.push_back(landingPlatformInTheGooPit);
	landingPlatformInTheGooPit->setRespawnLocations(respawnLocations);
	respawnLocations.clear();

	//end of the first train tunnel
	geom1[0] = new PxBoxGeometry(50, 15, 50);
	respawnLocations.push_back(PxVec3(-900, -15, 771));
	respawnLocations.push_back(PxVec3(-875, -15, 755));
	respawnLocations.push_back(PxVec3(-900, -15, 740));
	respawnLocations.push_back(PxVec3(-875, -15, 725));
	pos = new PxTransform(PxVec3(-856, -30, 751), PxQuat(2.04, PxVec3(0, 1, 0)));
	endOfTheFirstTrainTunnel = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	endOfTheFirstTrainTunnel->setGoalWaypointIndex(getWaypointAt(339));
	endOfTheFirstTrainTunnel->setCurrentWaypointIndex(getWaypointAt(332));
	m_collisionVolumes.push_back(endOfTheFirstTrainTunnel);
	endOfTheFirstTrainTunnel->setRespawnLocations(respawnLocations);
	respawnLocations.clear();

	//maybe the ramp exit of tunnel :p
	respawnLocations.push_back(PxVec3(-710, 20, 120));
	respawnLocations.push_back(PxVec3(-710, 20, 95));
	respawnLocations.push_back(PxVec3(-760, 20, 120));
	respawnLocations.push_back(PxVec3(-760, 20, 95));
	pos = new PxTransform(PxVec3(-730, 0, 120), PxQuat(3.14, PxVec3(0, 1, 0)));
	maybeTheRampExitInTheTunnel = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	maybeTheRampExitInTheTunnel->setGoalWaypointIndex(getWaypointAt(826));
	maybeTheRampExitInTheTunnel->setCurrentWaypointIndex(getWaypointAt(850));
	m_collisionVolumes.push_back(maybeTheRampExitInTheTunnel);
	maybeTheRampExitInTheTunnel->setRespawnLocations(respawnLocations);
	respawnLocations.clear();

	//entrence to the trafic circle
	respawnLocations.push_back(PxVec3(-625, 20, -95));
	respawnLocations.push_back(PxVec3(-625, 20, -120));
	respawnLocations.push_back(PxVec3(-600, 20, -95));
	respawnLocations.push_back(PxVec3(-600, 20, -120));
	pos = new PxTransform(PxVec3(-625, 0, -105), PxQuat(1.53, PxVec3(0, 1, 0)));
	entranceToTheTrafficCircle = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	entranceToTheTrafficCircle->setGoalWaypointIndex(getWaypointAt(768));
	entranceToTheTrafficCircle->setCurrentWaypointIndex(getWaypointAt(813));
	m_collisionVolumes.push_back(entranceToTheTrafficCircle);
	entranceToTheTrafficCircle->setRespawnLocations(respawnLocations);
	respawnLocations.clear();

	//top of the traffic circle
	geom1[0] = new PxBoxGeometry(25, 15, 25);
	respawnLocations.push_back(PxVec3(-348, 20, 0));
	respawnLocations.push_back(PxVec3(-348, 20, 21.5));
	respawnLocations.push_back(PxVec3(-348, 20, 41.5));
	pos = new PxTransform(PxVec3(-378, 6, 21.5), PxQuat(2.22962, PxVec3(0, 1, 0)));
	topOfTheTrafficCircle = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	m_collisionVolumes.push_back(topOfTheTrafficCircle);
	topOfTheTrafficCircle->setRespawnLocations(respawnLocations);
	respawnLocations.clear();

	//bottom of the traffic circle
	respawnLocations.push_back(PxVec3(-348, 20, -211.5));
	respawnLocations.push_back(PxVec3(-348, 20, -231.5));
	respawnLocations.push_back(PxVec3(-348, 20, -251.5));
	pos = new PxTransform(PxVec3(-378, 6, -231.5), PxQuat(0.685, PxVec3(0, 1, 0)));
	bottomOfTheTrafficCircle = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	bottomOfTheTrafficCircle->setGoalWaypointIndex(getWaypointAt(48));
	bottomOfTheTrafficCircle->setCurrentWaypointIndex(getWaypointAt(768));
	m_collisionVolumes.push_back(bottomOfTheTrafficCircle);
	bottomOfTheTrafficCircle->setRespawnLocations(respawnLocations);
	respawnLocations.clear();

	delete pos;
	delete geom1[0];
	delete[] geom1;

	startLine->addNextVolume(pathBranchLeadingIntoTheDessert);
	startLine->addNextVolume(topOfTheJumpRampInTheDesert);

	pathBranchLeadingIntoTheDessert->addNextVolume(deathPit1);
	pathBranchLeadingIntoTheDessert->addNextVolume(topOfTheJumpRampInTheDesert);

	topOfTheJumpRampInTheDesert->addNextVolume(deathPit1);
	topOfTheJumpRampInTheDesert->addNextVolume(deathPit2);
	topOfTheJumpRampInTheDesert->addNextVolume(startOfTheCanyon);

	deathPit1->addNextVolume(deathPit2);

	deathPit2->addNextVolume(startOfTheCanyon);

	startOfTheCanyon->addNextVolume(branchPathInTheCanyon);

	branchPathInTheCanyon->addNextVolume(landingPlatformInTheGooPit);

	landingPlatformInTheGooPit->addNextVolume(endOfTheFirstTrainTunnel);

	endOfTheFirstTrainTunnel->addNextVolume(maybeTheRampExitInTheTunnel);

	maybeTheRampExitInTheTunnel->addNextVolume(entranceToTheTrafficCircle);

	entranceToTheTrafficCircle->addNextVolume(topOfTheTrafficCircle);
	entranceToTheTrafficCircle->addNextVolume(bottomOfTheTrafficCircle);

	topOfTheTrafficCircle->addNextVolume(startLine);

	bottomOfTheTrafficCircle->addNextVolume(startLine);
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
