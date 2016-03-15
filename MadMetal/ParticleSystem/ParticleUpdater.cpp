#include "ParticleUpdater.h"
#include <iostream>

void PositionUpdater::update(float dt, ParticleData& particles)
{
	//PxVec3 accel(dt * m_globalAcc.x, dt * m_globalAcc.y, dt * m_globalAcc.z);
	

	const unsigned int endId = particles.m_countAlive;

	for (size_t i = 0; i < particles.m_countAlive; i++)
	{
		
		//particles.m_vel[i] += accel;
		PxVec3 deltaV = PxVec3(particles.m_vel[i].x * dt, particles.m_vel[i].y * dt, particles.m_vel[i].z * dt);
		particles.m_pos[i] += deltaV;
		particles.m_particles[i]->getRigidActor()->setGlobalPose(PxTransform(particles.m_pos[i]));
	}

	
	
	
	
	


}

void TimeUpdater::update(float dt, ParticleData& particles)
{
	
	for (size_t i = 0; i < particles.m_countAlive; i++)
	{
		if ((particles.m_time[i] -= dt) <= 0)
		{
			particles.kill(i);
		}
	}
}

