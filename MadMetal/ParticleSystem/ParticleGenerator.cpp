#include "ParticleGenerator.h"
#include <iostream>

void PositionGenerator::generate( ParticleData &particles, size_t startId, size_t endId)
{

	for (size_t i = startId; i < endId; i++)
	{
		
		particles.m_pos[i] = m_pos;
		
		particles.m_particles[i]->getRigidActor()->setGlobalPose(PxTransform(particles.m_pos[i]));
		
		
		//std::cout << "particle generated at " << actor->getGlobalPose().p.x << "," << actor->getGlobalPose().p.y << "," << actor->getGlobalPose().p.z << std::endl;
		
	}

}

void PositionGenerator::updatePosition(PxVec3 pos)
{
	m_pos = pos;
}

void CirclePositionGenerator::generate(ParticleData &particles, size_t startId, size_t endId)
{

	
	if (m_randomStart){
		for (size_t i = startId; i < endId; i++)
		{
			glm::vec2 position;// = glm::circularRand(m_radius);

			particles.m_pos[i] = PxVec3(m_pos.x + position.x, m_pos.y, m_pos.z + position.y);
			
			
		}
	}
	else {
		m_circProg = (float)fmod((m_circProg + m_rotateSpeed) ,360);
		glm::vec3 position;// = glm::rotateY(glm::vec3(1, 0, 0) * m_radius, m_circProg);
		for (size_t i = startId; i < endId; i++)
		{
			particles.m_pos[i] = PxVec3(m_pos.x + position.x, m_pos.y + position.y, m_pos.z + position.z);
			particles.m_particles[i]->getRigidActor()->setGlobalPose(PxTransform(particles.m_pos[i]));
		}
	}

}
/*
void ColorGenerator::generate(double dt, ParticleData *p, size_t startId, size_t endId)
{

	for (size_t i = startId; i < endId; i++)
	{
		p->m_startCol[i] = p->m_col[i] = glm::linearRand(m_minStartColor, m_maxStartColor);
		p->m_endCol[i] = glm::linearRand(m_minEndColor, m_maxEndColor);
		std::cout << p->m_col[i].y << "\n";
	}

}*/


void TimeGenerator::generate( ParticleData& particles, size_t startId, size_t endId)
{

	for (size_t i = startId; i < endId; i++)
	{
		particles.m_time[i];// = glm::linearRand(m_minStartTime, m_maxStartTime);
	}
}

void VelocityGenerator::generate(ParticleData& particles, size_t startId, size_t endId)
{
	for (size_t i = startId; i < endId; i++)
	{
		glm::vec3 startVelocity;// = glm::linearRand(glm::vec3(m_minStartVel.x, m_minStartVel.y, m_minStartVel.z), glm::vec3(m_maxStartVel.x, m_maxStartVel.y, m_maxStartVel.z));
		particles.m_vel[i] = PxVec3(startVelocity.x, startVelocity.y, startVelocity.z);
	}
}
/*
void NormalGenerator::generate(double dt, ParticleData * p, size_t startId, size_t endId)
{
	for (size_t i = startId; i < endId; i++)
	{
		p->m_norm[i] = m_startNorm;
	}
}
*/
