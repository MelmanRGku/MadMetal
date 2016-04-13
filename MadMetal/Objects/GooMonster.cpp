#pragma once

#include "GooMonster.h"
#include "Global\Assets.h"
#include "Factory\GameFactory.h"
#include "Game Logic\Controllable.h"
#include "Libraries\glm\gtx\vector_angle.hpp"

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
			m_respawnCounter = (float) 3 + (rand() % 5);
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
			m_renderable->setModel(Assets::getModel("Creature"));
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
	else
		processLookAt();
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


void GooMonster::setPlayers(std::vector<Controllable *> players) {
	this->players = players;
}

void GooMonster::processLookAt() {

	//get the player to look at
	float minDistance = 90000000;
	float minDistancePlayer = -1;
	for (int i = 0; i < players.size(); i++) {
		float dist = glm::distance2(getGlobalPose(), players.at(i)->getCar()->getGlobalPose());
		if (dist < minDistance) {
			minDistance = dist;
			minDistancePlayer = i;
		}
	}

	//get the angle of rotation and the vector to rotate around
	if (minDistancePlayer == -1)
		return;
	glm::vec3 viewDirectionOfTheMonster = glm::vec3(1, 0, 0);
	glm::vec3 requiredViewDirection = glm::normalize(players.at(minDistancePlayer)->getCar()->getGlobalPose() - getGlobalPose());
	float angle = std::acos(glm::dot(viewDirectionOfTheMonster, requiredViewDirection));
	glm::vec3 rotationAxis = glm::normalize(glm::cross(viewDirectionOfTheMonster, requiredViewDirection));

	getActor().setGlobalPose(PxTransform(PxVec3(getActor().getGlobalPose().p), PxQuat(angle, PxVec3(rotationAxis.x, rotationAxis.y, rotationAxis.z))));
}