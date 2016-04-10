#pragma once

#include "Object3D.h"

class GooMonster : public Object3D
{
public :
	GooMonster(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);
	~GooMonster();

	enum GooMonsterType {
		GOO_MONSTER_TYPE_KILLER,
		GOO_MONSTER_TYPE_PUSHER,
		TOTAL_NUMBER_OF_MONSTER_TYPES
	};

	virtual void update(float dt);
	void setSpawnVelocity(PxVec3 velocity);
	GooMonsterType getMonsterType();
	void setMonsterType(GooMonsterType type);

private:
	void processRoll();

	bool m_needsRespawn;
	float m_respawnCounter;
	PxVec3 m_spawnLocation;
	PxVec3 m_spawnVelocity;
	GooMonsterType type;
	bool rollStarted;
};