#pragma once

#include "GooMonster.h"

GooMonster::GooMonster(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable, NULL)
{
	std::cout << "Spawned goo monster\n";
	m_respawnCounter = 0;
	
	m_spawnLocation = m_physicable->getActor().getGlobalPose().p;
	m_needsRespawn = false;
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
			m_respawnCounter = 1 + (float) (rand() % 2) / 2;
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
		if (actor == NULL)
		{
			//std::cout << "actor is null \n";
		}
		else
		{


			actor->setLinearVelocity(m_spawnVelocity);
			actor->setGlobalPose(PxTransform(m_spawnLocation));
			//std::cout << "Respawning\n";
		}
	} else {
		m_respawnCounter -= dt;
	}

}

