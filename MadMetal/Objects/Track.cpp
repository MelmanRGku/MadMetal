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
	CollisionVolume::resetGlobalId();
	int sameIndex = 0;

	// 0
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(0, 10, -40));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsStartCollisionVolume(true);
	delete pos;
	delete geom1[0];

	// 1a
	geom1[0] = new PxBoxGeometry(17, 10, 20);
	pos = new PxTransform(PxVec3(10, 10, 181.75));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	delete pos;
	delete geom1[0];

	// 1b
	geom1[0] = new PxBoxGeometry(15, 10, 20);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-31.5, 35, 360));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	delete pos;
	delete geom1[0];

	// 2a
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(10, 10, 436));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	delete pos;
	delete geom1[0];

	// 2b
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-31.5, 35, 534));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	delete pos;
	delete geom1[0];

	// 3a
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-15, 10, 606));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	delete pos;
	delete geom1[0];


	// 3b
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(32, 35, 659));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	delete pos;
	delete geom1[0];

	// 4a
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-30, 10, 760));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	delete pos;
	delete geom1[0];

	// 4b
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(32, 35, 908));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	delete pos;
	delete geom1[0];

	// 5
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-4, 10, 1050));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	delete pos;
	delete geom1[0];

	// 6
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-2, 10, 1430));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	delete pos;
	delete geom1[0];

	// 7
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-10, 10, 1505));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	delete pos;
	delete geom1[0];

	// 8
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-57, 10, 1555));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	delete pos;
	delete geom1[0];

	// 9
	geom1[0] = new PxBoxGeometry(50, 10, 40);
	pos = new PxTransform(PxVec3(-245, 10, 1555));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	delete pos;
	delete geom1[0];

	// 10a
	geom1[0] = new PxBoxGeometry(50, 10, 25);
	pos = new PxTransform(PxVec3(-341, 10, 1584));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	delete pos;
	delete geom1[0];

	//10b
	geom1[0] = new PxBoxGeometry(25, 10, 25);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-338, 10, 1515));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	delete pos;
	delete geom1[0];

	//11a
	geom1[0] = new PxBoxGeometry(25, 10, 25);
	pos = new PxTransform(PxVec3(-400, 10, 1599));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	delete pos;
	delete geom1[0];

	// 11b
	geom1[0] = new PxBoxGeometry(25, 10, 25);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-396, 10, 1500));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	delete pos;
	delete geom1[0];

	//12a
	geom1[0] = new PxBoxGeometry(25, 10, 25);
	pos = new PxTransform(PxVec3(-594, 15, 1603));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	delete pos;
	delete geom1[0];

	//12b
	geom1[0] = new PxBoxGeometry(25, 10, 25);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-591, 15, 1500));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	delete pos;
	delete geom1[0];

	//13a
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-830, -20, 1603));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	delete pos;
	delete geom1[0];

	//13b
	geom1[0] = new PxBoxGeometry(25, 10, 25);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-830, -20, 1500));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	delete pos;
	delete geom1[0];

	//14a
	geom1[0] = new PxBoxGeometry(25, 10, 25);
	pos = new PxTransform(PxVec3(-934, -20, 1559));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	delete pos;
	delete geom1[0];

	//14b
	geom1[0] = new PxBoxGeometry(25, 10, 25);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-923, -20, 1490));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	delete pos;
	delete geom1[0];

	// 15
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-987, -20, 1436));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	delete pos;
	delete geom1[0];

	// 16
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-989, -20, 844));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	delete pos;
	delete geom1[0];

	//17
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-842, -20, 750));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	delete pos;
	delete geom1[0];

	//18
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-740, -20, 659));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	delete pos;
	delete geom1[0];

	//19
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-736, 10, -59));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	delete pos;
	delete geom1[0];

	// 20
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-713, 10, -91));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	delete pos;
	delete geom1[0];

	//21
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-557, 10, -104));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	delete pos;
	delete geom1[0];

	//22a
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-478, 10, -35));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	delete pos;
	delete geom1[0];

	//22b
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-473, 10, -183));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	delete pos;
	delete geom1[0];

	// 23a
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-383, 10, 4));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	delete pos;
	delete geom1[0];

	//23b
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-380, 10, -219));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	delete pos;
	delete geom1[0];

	//24a
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-343, 10, -5));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(1);
	delete pos;
	delete geom1[0];

	//24b
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	sameIndex = m_collisionVolumes[m_collisionVolumes.size() - 1]->getId();
	pos = new PxTransform(PxVec3(-333, 10, -207));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setIsParthOfMainPath(false);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setPathNumber(2);
	m_collisionVolumes[m_collisionVolumes.size() - 1]->setId(sameIndex);
	delete pos;
	delete geom1[0];

	//25
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-184.2, 10, -100));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
	delete pos;
	delete geom1[0];

	//26
	geom1[0] = new PxBoxGeometry(50, 10, 50);
	pos = new PxTransform(PxVec3(-23, 10, -100));
	m_collisionVolumes.push_back(static_cast<CollisionVolume*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_COLLISION_VOLUME, pos, geom1, NULL)));
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

	}
}
