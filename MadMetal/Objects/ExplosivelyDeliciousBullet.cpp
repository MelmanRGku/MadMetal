#include "ExplosivelyDeliciousBullet.h"
#include "Factory\GameFactory.h"

ExplosivelyDeliciousBullet::ExplosivelyDeliciousBullet(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car *owner) : Bullet(id, aable, pable, anable, rable, owner)
	{
		m_damage = 35;
		maxLifeTime = 2;
	}

ExplosivelyDeliciousBullet::~ExplosivelyDeliciousBullet()
{

}

void ExplosivelyDeliciousBullet::update(float dt) {
	Bullet::update(dt);
	if (hasToBeDeleted) {
		spawnExplosion();
	}
}

void ExplosivelyDeliciousBullet::spawnExplosion() {
	PxGeometry **explosionGeom = new PxGeometry*[1];
	explosionGeom[0] = new PxSphereGeometry(60);
	GameFactory::instance()->makeObject(GameFactory::OBJECT_BOMB_EXPLOSION, &m_physicable->getActor().getGlobalPose(), explosionGeom, m_owner);
	delete explosionGeom[0];
	delete[] explosionGeom;

	m_audioable->getAudioHandle().queAudioSource(&m_physicable->getActor(), BoomSound());
}