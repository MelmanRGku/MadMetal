#pragma once

#include "Object3D.h"

class GooMonster : public Object3D
{
public :
	GooMonster(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);
	~GooMonster();
	virtual void update(float dt);
	void setSpawnVelocity(PxVec3 velocity);
private:
	bool m_needsRespawn;
	float m_respawnCounter;
	PxVec3 m_spawnLocation;
	PxVec3 m_spawnVelocity;
};