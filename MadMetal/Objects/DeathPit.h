#pragma once

#include "Object3D.h"

class DeathPit : public Object3D
{
public:
	DeathPit(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);
	~DeathPit();
	void setRespawnLocation(PxVec3 respawnLoc);
private:
	PxVec3 m_respawnLocation;
};