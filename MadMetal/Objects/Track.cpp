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
	geom1[0] = new PxBoxGeometry(50, 10, 50);





	std::vector<PxVec3> collisionVolumePositions;
	collisionVolumePositions.push_back(PxVec3(4, 10, -40));
	collisionVolumePositions.push_back(PxVec3(14, 10, 215));
	collisionVolumePositions.push_back(PxVec3(15, 10, 436));
	collisionVolumePositions.push_back(PxVec3(-9, 10, 606));
	collisionVolumePositions.push_back(PxVec3(-25, 10, 760));
	collisionVolumePositions.push_back(PxVec3(-9, 10, 1050));
	collisionVolumePositions.push_back(PxVec3(-2, 10, 1430));
	
	
	for (int i = 0; i < collisionVolumePositions.size(); i++)
	{
		pos = new PxTransform(collisionVolumePositions[i]);
		m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	}

	for (int i = 0; i < m_collisionVolumes.size(); i++)
	{
		if (i == m_collisionVolumes.size() - 1)
		{
			m_collisionVolumes[i]->setNextCollisionVolume(m_collisionVolumes[0]);
		}
		else {
			m_collisionVolumes[i]->setNextCollisionVolume(m_collisionVolumes[i + 1]);
		}
	}




	//std::vector<PxVec3> respawnLocations;
	////startLine
	//pos = new PxTransform(PxVec3(4, 15, -35));
	//startLine = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	//m_collisionVolumes.push_back(startLine);
	//respawnLocations.push_back(PxVec3(25, 20, -35));
	//respawnLocations.push_back(PxVec3(5, 20, -35));
	//respawnLocations.push_back(PxVec3(-15, 20, -35));
	//respawnLocations.push_back(PxVec3(25, 20, -60));
	//respawnLocations.push_back(PxVec3(5, 20, -60));
	//respawnLocations.push_back(PxVec3(-15, 20, -60));
	//startLine->setRespawnLocations(respawnLocations);
	//startLine->setIsStartCollisionVolume(true);
	//respawnLocations.clear();

	////path branch leading into the dessert
	//pos = new PxTransform(PxVec3(15, 15, 225));
	//geom1[0] = new PxBoxGeometry(25, 10, 10);
	//respawnLocations.push_back(PxVec3(25, 20, 225));
	//respawnLocations.push_back(PxVec3(5, 20, 225));
	//respawnLocations.push_back(PxVec3(25, 20, 200));
	//respawnLocations.push_back(PxVec3(5, 20, 200));
	//pathBranchLeadingIntoTheDessert = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	//startLine->setNextCollisionVolume(pathBranchLeadingIntoTheDessert);
	//pathBranchLeadingIntoTheDessert->setSectionSpeedDamping(1.0);
	//pathBranchLeadingIntoTheDessert->setSectionSteeringDamping(0.6);

	//m_collisionVolumes.push_back(pathBranchLeadingIntoTheDessert);
	//pathBranchLeadingIntoTheDessert->setRespawnLocations(respawnLocations);
	//respawnLocations.clear();

	////top of the jump ramp in the dessert
	//pos = new PxTransform(PxVec3(-30, 37, 325));
	//topOfTheJumpRampInTheDesert = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	////m_collisionVolumes.push_back(topOfTheJumpRampInTheDesert);

	////deathPit 1
	//geom1[0] = new PxBoxGeometry(40, 15, 45);
	//respawnLocations.push_back(PxVec3(25, 20, 525));
	//respawnLocations.push_back(PxVec3(5, 20, 525));
	//respawnLocations.push_back(PxVec3(25, 20, 500));
	//respawnLocations.push_back(PxVec3(5, 20, 500));
	//pos = new PxTransform(PxVec3(15, 0, 450));
	//deathPit1 = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	//pathBranchLeadingIntoTheDessert->setNextCollisionVolume(deathPit1);
	//deathPit1->setSectionSpeedDamping(1.0);
	//deathPit1->setSectionSteeringDamping(0.4);
	//m_collisionVolumes.push_back(deathPit1);
	//deathPit1->setRespawnLocations(respawnLocations);
	//respawnLocations.clear();

	////second death pit
	//geom1[0] = new PxBoxGeometry(40, 15, 38);
	//respawnLocations.push_back(PxVec3(-35, 20, 865));
	//respawnLocations.push_back(PxVec3(-15, 20, 865));
	//respawnLocations.push_back(PxVec3(-35, 20, 840));
	//respawnLocations.push_back(PxVec3(-15, 20, 840));
	//pos = new PxTransform(PxVec3(-25, 0, 760));
	//deathPit2 = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	//deathPit1->setNextCollisionVolume(deathPit2)
	//m_collisionVolumes.push_back(deathPit2);
	//deathPit2->setRespawnLocations(respawnLocations);
	//deathPit2->setSectionSpeedDamping(1.0);
	//deathPit2->setSectionSteeringDamping(0.8);
	//respawnLocations.clear();
	//
	////start of the canyon
	//geom1[0] = new PxBoxGeometry(40, 10, 55);
	//respawnLocations.push_back(PxVec3(-15, 20, 1100));
	//respawnLocations.push_back(PxVec3(15, 20, 1100));
	//respawnLocations.push_back(PxVec3(-15, 20, 1075));
	//respawnLocations.push_back(PxVec3(15, 20, 1075));
	//pos = new PxTransform(PxVec3(0, 15, 1100));
	//startOfTheCanyon = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	//m_collisionVolumes.push_back(startOfTheCanyon);
	//startOfTheCanyon->setSectionSpeedDamping(1.0);
	//startOfTheCanyon->setSectionSteeringDamping(0.35);
	//startOfTheCanyon->setRespawnLocations(respawnLocations);
	//respawnLocations.clear();

	////branch path in the canyon
	//respawnLocations.push_back(PxVec3(-45, 20, 1560));
	//respawnLocations.push_back(PxVec3(-20, 20, 1560));
	//respawnLocations.push_back(PxVec3(-45, 20, 1540));
	//respawnLocations.push_back(PxVec3(-25, 20, 1540));
	//pos = new PxTransform(PxVec3(-45, 15, 1555), PxQuat(1.6203, PxVec3(0, -1, 0)));
	//branchPathInTheCanyon = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	//branchPathInTheCanyon->setSectionSpeedDamping(1.0);
	//branchPathInTheCanyon->setSectionSteeringDamping(0.7);
	//m_collisionVolumes.push_back(branchPathInTheCanyon);
	//branchPathInTheCanyon->setRespawnLocations(respawnLocations);
	//respawnLocations.clear();

	////landing platform in the goo pit
	//geom1[0] = new PxBoxGeometry(300, 10, 300);
	//respawnLocations.push_back(PxVec3(-870, 20, 1575));
	//respawnLocations.push_back(PxVec3(-870, 20, 1550));
	//respawnLocations.push_back(PxVec3(-870, 20, 1525));
	//
	//respawnLocations.push_back(PxVec3(-840, 20, 1575));
	//respawnLocations.push_back(PxVec3(-840, 20, 1550));
	//respawnLocations.push_back(PxVec3(-840, 20, 1525));
	//pos = new PxTransform(PxVec3(-640, -18, 1550), PxQuat(1.6203, PxVec3(0, -1, 0)));
	//landingPlatformInTheGooPit = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	//landingPlatformInTheGooPit->setSectionSpeedDamping(1.0);
	//landingPlatformInTheGooPit->setSectionSteeringDamping(0.8);
	//m_collisionVolumes.push_back(landingPlatformInTheGooPit);
	//landingPlatformInTheGooPit->setRespawnLocations(respawnLocations);
	//respawnLocations.clear();

	////end of the first train tunnel
	//geom1[0] = new PxBoxGeometry(50, 10, 50);
	//respawnLocations.push_back(PxVec3(-900, -15, 771));
	//respawnLocations.push_back(PxVec3(-875, -15, 755));
	//respawnLocations.push_back(PxVec3(-900, -15, 740));
	//respawnLocations.push_back(PxVec3(-875, -15, 725));
	//pos = new PxTransform(PxVec3(-856, -18, 751), PxQuat(2.04, PxVec3(0, 1, 0)));
	//endOfTheFirstTrainTunnel = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	//endOfTheFirstTrainTunnel->setSectionSpeedDamping(1.0);
	//endOfTheFirstTrainTunnel->setSectionSteeringDamping(0.7);
	//m_collisionVolumes.push_back(endOfTheFirstTrainTunnel);
	//endOfTheFirstTrainTunnel->setRespawnLocations(respawnLocations);
	//respawnLocations.clear();

	////maybe the ramp exit of tunnel :p
	//respawnLocations.push_back(PxVec3(-710, 20, 120));
	//respawnLocations.push_back(PxVec3(-710, 20, 95));
	//respawnLocations.push_back(PxVec3(-760, 20, 120));
	//respawnLocations.push_back(PxVec3(-760, 20, 95));
	//pos = new PxTransform(PxVec3(-730, 10, 120), PxQuat(3.14, PxVec3(0, 1, 0)));
	//maybeTheRampExitInTheTunnel = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));

	//maybeTheRampExitInTheTunnel->setSectionSpeedDamping(1.0);
	//maybeTheRampExitInTheTunnel->setSectionSteeringDamping(1.0);
	//m_collisionVolumes.push_back(maybeTheRampExitInTheTunnel);
	//maybeTheRampExitInTheTunnel->setRespawnLocations(respawnLocations);
	//respawnLocations.clear();

	////entrence to the trafic circle
	//respawnLocations.push_back(PxVec3(-625, 20, -95));
	//respawnLocations.push_back(PxVec3(-625, 20, -120));
	//respawnLocations.push_back(PxVec3(-600, 20, -95));
	//respawnLocations.push_back(PxVec3(-600, 20, -120));
	//pos = new PxTransform(PxVec3(-625, 15, -105), PxQuat(1.53, PxVec3(0, 1, 0)));
	//entranceToTheTrafficCircle = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));

	//entranceToTheTrafficCircle->setSectionSpeedDamping(1.0);
	//entranceToTheTrafficCircle->setSectionSteeringDamping(1.0);
	//m_collisionVolumes.push_back(entranceToTheTrafficCircle);
	//entranceToTheTrafficCircle->setRespawnLocations(respawnLocations);
	//respawnLocations.clear();

	////top of the traffic circle
	//geom1[0] = new PxBoxGeometry(25, 15, 25);
	//respawnLocations.push_back(PxVec3(-348, 20, 0));
	//respawnLocations.push_back(PxVec3(-348, 20, 21.5));
	//respawnLocations.push_back(PxVec3(-348, 20, 41.5));
	//pos = new PxTransform(PxVec3(-378, 17, 21.5), PxQuat(2.22962, PxVec3(0, 1, 0)));
	//topOfTheTrafficCircle = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	//m_collisionVolumes.push_back(topOfTheTrafficCircle);
	//topOfTheTrafficCircle->setRespawnLocations(respawnLocations);
	//respawnLocations.clear();

	////bottom of the traffic circle
	//respawnLocations.push_back(PxVec3(-348, 20, -211.5));
	//respawnLocations.push_back(PxVec3(-348, 20, -231.5));
	//respawnLocations.push_back(PxVec3(-348, 20, -251.5));
	//pos = new PxTransform(PxVec3(-378, 17, -231.5), PxQuat(0.685, PxVec3(0, 1, 0)));
	//bottomOfTheTrafficCircle = static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL));
	//m_collisionVolumes.push_back(bottomOfTheTrafficCircle);
	//bottomOfTheTrafficCircle->setRespawnLocations(respawnLocations);
	//respawnLocations.clear();

	delete pos;
	delete geom1[0];
	delete[] geom1;

	//startLine->addNextVolume(pathBranchLeadingIntoTheDessert);
	//startLine->addNextVolume(topOfTheJumpRampInTheDesert);

	//pathBranchLeadingIntoTheDessert->addNextVolume(deathPit1);
	//pathBranchLeadingIntoTheDessert->addNextVolume(topOfTheJumpRampInTheDesert);

	//topOfTheJumpRampInTheDesert->addNextVolume(deathPit1);
	//topOfTheJumpRampInTheDesert->addNextVolume(deathPit2);
	//topOfTheJumpRampInTheDesert->addNextVolume(startOfTheCanyon);

	//deathPit1->addNextVolume(deathPit2);

	//deathPit2->addNextVolume(startOfTheCanyon);

	//startOfTheCanyon->addNextVolume(branchPathInTheCanyon);

	//branchPathInTheCanyon->addNextVolume(landingPlatformInTheGooPit);

	//landingPlatformInTheGooPit->addNextVolume(endOfTheFirstTrainTunnel);

	//endOfTheFirstTrainTunnel->addNextVolume(maybeTheRampExitInTheTunnel);

	//maybeTheRampExitInTheTunnel->addNextVolume(entranceToTheTrafficCircle);

	//entranceToTheTrafficCircle->addNextVolume(topOfTheTrafficCircle);
	//entranceToTheTrafficCircle->addNextVolume(bottomOfTheTrafficCircle);

	//topOfTheTrafficCircle->addNextVolume(startLine);

	//bottomOfTheTrafficCircle->addNextVolume(startLine);
}

bool Track::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	
	//do nothing
	return false;

}

void Track::playTrackMusic()
{
	m_audioable->getAudioHandle().playMusic(m_sound);
}
