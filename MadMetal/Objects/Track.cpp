#include "Track.h"
#include "Waypoint.h"
#include "Game Logic\WayPointSystem.h"
#include "Game Logic\WaypointDefinitions.h"
#include "Objects\CollisionVolume.h"
#include "ObjectLoaders\ObjModelLoader.h"
#include "Game Logic\AIDefinitions.h"

Track::Track(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Object3D *drivablePart, Object3D *nonDrivablePart, Object3D* trackWalls) : Object3D(id, aable, pable, anable, rable, NULL), drivablePart(drivablePart), nonDrivablePart(nonDrivablePart), trackWalls(trackWalls)
{
	setupCollisionVolumes();
}

Track::~Track()
{
	
}

CollisionVolume* Track::getStartLine()
{
	if (m_collisionVolumes.size() > 0)
		return m_collisionVolumes[0];
	else
		return NULL;
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
	
	PxTransform * pos = NULL;
	PxGeometry **geom1 = new PxGeometry *[1];
	CollisionVolume::resetGlobalId();
	int sameIndex = 0;
	std::vector<PxVec3> respawnLocations;

	// 0 start line
	geom1[0] = new PxBoxGeometry(50, 5, 10);
	pos = new PxTransform(PxVec3(0, 6, -40));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsStartCollisionVolume(true);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(0, 0, 1), PxVec3(10, 10,-35), 4, 2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setSectionSpeedDamping(0.9);
	delete pos;
	delete geom1[0];

	//1a
	geom1[0] = new PxBoxGeometry(24, 5, 10);
	pos = new PxTransform(PxVec3(23, 6, 124.7), PxQuat(0, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	delete pos;
	delete geom1[0];

	//1b
	geom1[0] = new PxBoxGeometry(25, 5, 30);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-17, 6, 118));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	respawnLocations.clear();
	delete pos;
	delete geom1[0];


	// 2a
	geom1[0] = new PxBoxGeometry(70, 10, 12);
	pos = new PxTransform(PxVec3(25, 10, 290), PxQuat(0, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(0, 0, 1), pos->p, 2, 2);
	delete pos;
	delete geom1[0];

	// 2b
	geom1[0] = new PxBoxGeometry(17, 10, 5);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-33, 35, 341), PxQuat(0, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setSectionSpeedDamping(0.9);
	respawnLocations.clear();
	delete pos;
	delete geom1[0];

	// 3a
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(10, 10, 436), PxQuat(0.52, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setRespawnLocations(respawnLocations);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(-0.139, 0, .99), PxVec3(18.45, 15, 525), 2, 2);

	delete pos;
	delete geom1[0];

	// 3b
	geom1[0] = new PxBoxGeometry(15, 5, 20);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-35, 31, 495));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setSectionSpeedDamping(0.9);
	respawnLocations.clear();
	delete pos;
	delete geom1[0];

	// 4a
	geom1[0] = new PxBoxGeometry(50, 10, 30);
	pos = new PxTransform(PxVec3(-6.31, 10, 589));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	respawnLocations.clear();
	delete pos;
	delete geom1[0];


	// 4b
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	geom1[0] = new PxBoxGeometry(30, 5, 10);
	pos = new PxTransform(PxVec3(20, 31, 606));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	respawnLocations.clear();
	delete pos;
	delete geom1[0];

	// 5a
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-7, 10, 760));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(0, 0, 1), PxVec3(-26, 15, 843), 3, 2);

	respawnLocations.clear();
	delete pos;
	delete geom1[0];

	// 5b
	geom1[0] = new PxBoxGeometry(25, 10, 20);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(20, 35, 908), PxQuat(0.05, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	respawnLocations.clear();
	delete pos;
	delete geom1[0];

	// 5
	geom1[0] = new PxBoxGeometry(50, 10, 10);
	pos = new PxTransform(PxVec3(2.3, 10, 1230));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setSectionSpeedDamping(0.8);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(0, 0, 1), pos->p, 2, 2);

	respawnLocations.clear();
	delete pos;
	delete geom1[0];

	// 6
	geom1[0] = new PxBoxGeometry(40, 5, 5);
	pos = new PxTransform(PxVec3(-2, 10, 1430), PxQuat(0.0, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(0, 0, 1), pos->p, 2, 2);
	delete pos;
	delete geom1[0];

	// 7
	geom1[0] = new PxBoxGeometry(40, 5, 5);
	pos = new PxTransform(PxVec3(-23, 10, 1505));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	respawnLocations.clear();
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	delete pos;
	delete geom1[0];

	// 8
	geom1[0] = new PxBoxGeometry(25, 5, 50);
	pos = new PxTransform(PxVec3(-57, 10, 1530), PxQuat(1.5, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(-1, 0, 0), pos->p, 2, 2);
	delete pos;
	delete geom1[0];

	// 9
	geom1[0] = new PxBoxGeometry(30, 5, 40);
	pos = new PxTransform(PxVec3(-167, 10, 1539), PxQuat(1.5, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(-1, 0, 0), pos->p, 2, 2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setSectionSpeedDamping(0.8);
	delete pos;
	delete geom1[0];

	/*/ 11a
	geom1[0] = new PxBoxGeometry(20, 5, 15);
	pos = new PxTransform(PxVec3(-289, 10, 1579), PxQuat(1.5, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	
	respawnLocations.clear();
	delete pos;
	delete geom1[0];

	//11b
	geom1[0] = new PxBoxGeometry(20, 5, 15);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-286.8, 10, 1530), PxQuat(1.5, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	

	delete pos;
	delete geom1[0];

	//12a
	geom1[0] = new PxBoxGeometry(20, 5, 25);
	pos = new PxTransform(PxVec3(-341, 10, 1586), PxQuat(1.5, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	
	
	
	delete pos;
	delete geom1[0];

	// 12b
	geom1[0] = new PxBoxGeometry(20, 5, 20);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-338, 10, 1530), PxQuat(1.5, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	
	
	delete pos;
	delete geom1[0];
	*/
	//13a
	geom1[0] = new PxBoxGeometry(25, 5, 30);
	pos = new PxTransform(PxVec3(-368, 10, 1600));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	//m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(-1, 0, 0), PxVec3(-858, -15, 1550), 3, 2);
	
	delete pos;
	delete geom1[0];

	//13b
	geom1[0] = new PxBoxGeometry(25, 5, 30);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-374, 10, 1505));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	//m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(-1, 0, 0), PxVec3(-858, -15, 1550), 3, 2);
	
	delete pos;
	delete geom1[0];
	
	//14a
	geom1[0] = new PxBoxGeometry(5, 10, 20);
	pos = new PxTransform(PxVec3(-553, 13, 1586), PxQuat(1.5, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);

	delete pos;
	delete geom1[0];

	//14b
	geom1[0] = new PxBoxGeometry(5, 10, 20);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-640, 13, 1524), PxQuat(1.5, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);

	delete pos;
	delete geom1[0];


	//Canyon landing pad
	
	//13
	geom1[0] = new PxBoxGeometry(300, 10, 400);
	pos = new PxTransform(PxVec3(-500, -20, 1550), PxQuat(1.5, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(-1, 0, 0), PxVec3(-858, -15, 1550), 3, 2);
	
	delete pos;
	delete geom1[0];

	//14
	geom1[0] = new PxBoxGeometry(40, 10, 30);
	pos = new PxTransform(PxVec3(-966, -20, 1472));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setSectionSpeedDamping(0.8);

	delete pos;
	delete geom1[0];

	// 15
	geom1[0] = new PxBoxGeometry(60, 10, 10);
	pos = new PxTransform(PxVec3(-985, -20, 1147), PxQuat(3.10, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(0, 0, -1), pos->p, 1, 3);
	
	delete pos;
	delete geom1[0];

	// 16
	geom1[0] = new PxBoxGeometry(30, 10, 30);
	pos = new PxTransform(PxVec3(-989, -20, 983), PxQuat(3.10, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	
	

	delete pos;
	delete geom1[0];


	//17
	geom1[0] = new PxBoxGeometry(20, 5, 40);
	pos = new PxTransform(PxVec3(-968, -20, 872));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	respawnLocations.clear();
	

	delete pos;
	delete geom1[0];

	//18
	geom1[0] = new PxBoxGeometry(45, 10, 15);
	pos = new PxTransform(PxVec3(-840, -20, 739), PxQuat(4.0, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(0.793, 0, -.609), pos->p, 2, 2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setSectionSpeedDamping(0.9);
	delete pos;
	delete geom1[0];

	//19
	geom1[0] = new PxBoxGeometry(10, 10, 60);
	pos = new PxTransform(PxVec3(-760, -20, 665));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setSectionSpeedDamping(0.9);
	respawnLocations.clear();
	delete pos;
	delete geom1[0];

	//20
	geom1[0] = new PxBoxGeometry(50, 10, 10);
	pos = new PxTransform(PxVec3(-738, 10, 130), PxQuat(3.17322, PxVec3(0,1,0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(0, 0, -1), pos->p, 2, 2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setSectionSpeedDamping(0.5);
	
	delete pos;
	delete geom1[0];

	// 21
	geom1[0] = new PxBoxGeometry(65, 10, 10);
	pos = new PxTransform(PxVec3(-728, 10, -62));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setSectionSpeedDamping(0.9);
	delete pos;
	delete geom1[0];

	//22
	geom1[0] = new PxBoxGeometry(15, 10, 60);
	pos = new PxTransform(PxVec3(-558, 10, -101), PxQuat(4.7, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(1, 0, 0), pos->p, 2, 2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setSectionSpeedDamping(0.9);
	delete pos;
	delete geom1[0];

	//23a
	geom1[0] = new PxBoxGeometry(70, 5, 10);
	pos = new PxTransform(PxVec3(-495.8, 10, -63.4));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	respawnLocations.clear();
	delete pos;
	delete geom1[0];

	//23b
	geom1[0] = new PxBoxGeometry(70, 5, 10);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-495.6, 10, -133));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	respawnLocations.clear();
	delete pos;
	delete geom1[0];

	// 24a
	geom1[0] = new PxBoxGeometry(10, 5, 70);
	pos = new PxTransform(PxVec3(-442, 10, 14), PxQuat(5.83, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	respawnLocations.clear();
	delete pos;
	delete geom1[0];

	//24b
	geom1[0] = new PxBoxGeometry(10, 5, 70);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-446, 6, -205));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	respawnLocations.clear();
	delete pos;
	delete geom1[0];

	//25a
	geom1[0] = new PxBoxGeometry(20, 5, 70);
	pos = new PxTransform(PxVec3(-321, 6, 12));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	respawnLocations.clear();
	delete pos;
	delete geom1[0];

	//25b
	geom1[0] = new PxBoxGeometry(20, 5, 70);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-319, 10, -213));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	respawnLocations.clear();
	delete pos;
	delete geom1[0];

	/*/26a
	geom1[0] = new PxBoxGeometry(25, 10, 25);
	pos = new PxTransform(PxVec3(-269, 10, -54), PxQuat(2.583, PxVec3(0, 1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setSectionSpeedDamping(0.5);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	respawnLocations.clear();
	delete pos;
	delete geom1[0];

	//26b 
	geom1[0] = new PxBoxGeometry(25, 10, 25);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-269, 10, -155), PxQuat(5.79, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setSectionSpeedDamping(0.5);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	respawnLocations.clear();
	delete pos;
	delete geom1[0];
	*/
	

	//27
	geom1[0] = new PxBoxGeometry(40, 10, 60);
	pos = new PxTransform(PxVec3(-238, 10, -100), PxQuat(4.7, PxVec3(0, -1, 0)));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->generateRespawnLocations(PxVec3(1, 0, 0), pos->p, 2, 2);
	delete pos;
	delete geom1[0];

	//28
	geom1[0] = new PxBoxGeometry(10, 10, 60);
	pos = new PxTransform(PxVec3(-63, 10, -103));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsRespawnLocation(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setSectionSpeedDamping(0.9);
	delete pos;
	delete geom1[0];

	attachNextCollsionVolumes();
	attachReachableCollsionVolumes();

	delete[] geom1;

}

bool Track::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	
	//do nothing
	return false;

}

void Track::playTrackMusic()
{
	m_audioable->getAudioHandle().playMusic(m_sound);
}

void Track::attachNextCollsionVolumes()
{
	for (unsigned int i = 0; i < m_collisionVolumes.size(); i++)
	{
		int indexToAdd = 1;
		CollisionVolume* collisionVolumeToCheck = m_collisionVolumes[(i + indexToAdd) % m_collisionVolumes.size()];
		while (collisionVolumeToCheck->getId() == m_collisionVolumes[i]->getId())
		{
			indexToAdd++;
			collisionVolumeToCheck = m_collisionVolumes[(i + indexToAdd) % m_collisionVolumes.size()];
		}
		CollisionVolume* nextCollisionVolume = collisionVolumeToCheck;
		do
		{
			if (m_collisionVolumes[i]->getIsPartOfMainPath() || m_collisionVolumes[i]->getPathNumber() == nextCollisionVolume->getPathNumber() || nextCollisionVolume->getIsPartOfMainPath())
			{
				m_collisionVolumes[i]->addVolumeToNextCollsionVolumeList(nextCollisionVolume);
			}
			indexToAdd++;
			nextCollisionVolume = m_collisionVolumes[(i + indexToAdd) % m_collisionVolumes.size()];
		} while (collisionVolumeToCheck->getId() == nextCollisionVolume->getId());
		
	}
}

void Track::attachReachableCollsionVolumes()
{
	for (unsigned int i = 0; i < m_collisionVolumes.size(); i++)
	{
		int indexToAdd = 1;
		CollisionVolume* collisionVolumeToCheck = m_collisionVolumes[(i + indexToAdd) % m_collisionVolumes.size()];
		while (collisionVolumeToCheck->getId() == m_collisionVolumes[i]->getId())
		{
			indexToAdd++;
			collisionVolumeToCheck = m_collisionVolumes[(i + indexToAdd) % m_collisionVolumes.size()];
		}
		CollisionVolume* nextCollisionVolume = collisionVolumeToCheck;
		do
		{
			m_collisionVolumes[i]->addVolumeToReachableCollsionVolumeList(nextCollisionVolume);
			indexToAdd++;
			nextCollisionVolume = m_collisionVolumes[(i + indexToAdd) % m_collisionVolumes.size()];
		} while (collisionVolumeToCheck->getId() == nextCollisionVolume->getId());

		// Do a second go around to make sure you account for collisionvolumes on the next next way.

		collisionVolumeToCheck = nextCollisionVolume;
		do
		{
			m_collisionVolumes[i]->addVolumeToReachableCollsionVolumeList(nextCollisionVolume);
			indexToAdd++;
			nextCollisionVolume = m_collisionVolumes[(i + indexToAdd) % m_collisionVolumes.size()];
		} while (collisionVolumeToCheck->getId() == nextCollisionVolume->getId());

	}
}
