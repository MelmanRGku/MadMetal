#pragma once

#include "GooMonster.h"
#include "Global\Assets.h"
#include "Factory\GameFactory.h"

GooMonster::GooMonster(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable, NULL)
{
	//std::cout << "Spawned goo monster\n";
	m_respawnCounter = 0;
	
	m_spawnLocation = m_physicable->getActor().getGlobalPose().p;
	m_needsRespawn = false;
	type = GOO_MONSTER_TYPE_KILLER;
}

GooMonster::~GooMonster()
{

}

void GooMonster::setSpawnVelocity(PxVec3 vel)
{
	m_spawnVelocity = vel;
}

void GooMonster::update(float dt)
{
	PxVec3 position = m_physicable->getActor().getGlobalPose().p;
	if (!m_needsRespawn)
	{
		if (position.y < m_spawnLocation.y)
		{
			
			m_needsRespawn = true;
			m_respawnCounter = (float) (rand() % 5) / 2;
			//std::cout << "Respawning in " << m_respawnCounter << " seconds \n";
		}
	}
	else if (m_respawnCounter <= 0)
	{
		m_needsRespawn = false;
		Physicable *p = m_physicable;
		PxActor &px = p->getActor();
		PxActor *px2 = &px;
		PxRigidDynamic * actor = static_cast<PxRigidDynamic *>(px2);

		actor->setLinearVelocity(m_spawnVelocity);
		actor->setGlobalPose(PxTransform(m_spawnLocation));

		//change the monster type
		GooMonsterType newType = (GooMonsterType)(rand() % TOTAL_NUMBER_OF_MONSTER_TYPES);

		if (newType == GOO_MONSTER_TYPE_KILLER && type != GOO_MONSTER_TYPE_KILLER) {
			m_renderable->setModel(Assets::getModel("headcrabclassic"));
			static_cast<Renderable3D *>(m_renderable)->adjustModel(true, true);
		}
		else if (newType == GOO_MONSTER_TYPE_PUSHER && type != GOO_MONSTER_TYPE_PUSHER) {
			m_renderable->setModel(Assets::getModel("Slime"));
			static_cast<Renderable3D *>(m_renderable)->adjustModel(true, true);
		}

		setMonsterType(newType);
		rollStarted = false;
		m_animatable->setRotation(glm::vec3(0, 0, 0));

	} else {
		m_respawnCounter -= dt;
	}

	if (type == GooMonsterType::GOO_MONSTER_TYPE_PUSHER)
		processRoll();
}

void GooMonster::processRoll() {
	if (std::abs(static_cast<PxRigidDynamic*>(&m_physicable->getActor())->getLinearVelocity().y) < 22.5f && !rollStarted) {
		m_audioable->getAudioHandle().queAudioSource(&m_physicable->getActor(), WeeeeeSound(), 3.f);
		rollStarted = true;
		ObjectRotationUpdater *upd = new ObjectRotationUpdater(this, glm::vec3(360, 0, 0), 1.5f, ObjectRotationUpdater::ANGLE_TYPE_DEGREES);
		GameFactory::instance()->getWorld().addObjectUpdater(upd);
	}
}

GooMonster::GooMonsterType GooMonster::getMonsterType() {
	return type;
}

void GooMonster::setMonsterType(GooMonsterType type) {
	this->type = type;
}

