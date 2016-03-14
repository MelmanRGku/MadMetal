#include "ParticleUpdater.h"
#include <iostream>

void PositionUpdater::update(float dt, ParticleData * p)
{
	PxVec3 accel(dt * m_globalAcc.x, dt * m_globalAcc.y, dt * m_globalAcc.z);


	const unsigned int endId = p->m_countAlive;

	for (size_t i = 0; i < p->m_countAlive; i++)
	{
		Particle * particle = p->m_particles[i];
		PxVec3 speed = particle->getRigidActor()->getLinearVelocity();
		speed += accel;
		particle->getRigidActor()->setLinearVelocity(speed);
		
		PxVec3 position = particle->getRigidActor()->getGlobalPose().p * dt;
		particle->getRigidActor()->setGlobalPose(PxTransform(position));
	}


}

void TimeUpdater::update(float dt, ParticleData * p)
{
	
	for (size_t i = 0; i < p->m_countAlive; i++)
	{
		if ((p->m_time[i] -= dt) <= 0)
		{
			p->kill(i);
		}
	}
}

