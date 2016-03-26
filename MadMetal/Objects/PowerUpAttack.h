#pragma once
#include "PowerUpVolume.h"
#include "ParticleSystem\ParticleEmitter.h"


class PowerUpAttack : public PowerUpVolume
{
public:

	PowerUpAttack(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Car * owner) : PowerUpVolume(id, aable, pable, anable, rable, owner)
	{
		m_emitter = new ParticleEmitter(.5, PxVec3(0, 5, 0), 1, "healthCross", static_cast<Object3D *>(owner));
	}
	virtual ~PowerUpAttack()
	{
		delete m_emitter;
	}

	virtual void update(float dtMillis)
	{
		m_emitter->update(dtMillis);
		PowerUpVolume::update(dtMillis);
	}
private://members
	ParticleEmitter * m_emitter;
private:

};