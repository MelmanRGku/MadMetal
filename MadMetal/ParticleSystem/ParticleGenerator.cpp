#include "ParticleGenerator.h"
#include <iostream>

void PositionGenerator::generate(double dt, ParticleData *p, size_t startId, size_t endId)
{

	glm::vec4 posMin{ m_pos.x - m_maxStartPosOffset.x,
		m_pos.y - m_maxStartPosOffset.y,
		m_pos.z - m_maxStartPosOffset.z,
		1.0 };
	glm::vec4 posMax{ m_pos.x + m_maxStartPosOffset.x,
		m_pos.y + m_maxStartPosOffset.y,
		m_pos.z + m_maxStartPosOffset.z,
		1.0 };

	for (size_t i = startId; i < endId; i++)
	{
		p->m_pos[i] = glm::linearRand(posMin, posMax);
	}

	for (size_t i = startId; i < endId; i++)
	{
		p->m_vel[i] = glm::vec4(0);
	}

	for (size_t i = startId; i < endId; i++)
	{
		p->m_acc[i] = glm::vec4(0);
	}


}

void CirclePositionGenerator::generate(double dt, ParticleData *p, size_t startId, size_t endId)
{

	
	if (m_randomStart){
		for (size_t i = startId; i < endId; i++)
		{
			glm::vec2 position = glm::circularRand(m_radius);
			p->m_pos[i] = m_pos + glm::vec4(position.x, position.y, 0, 0);
		}
	}
	else {
		m_circProg = fmod((m_circProg + dt * 5) ,360);
		glm::vec3 position = glm::rotateZ(glm::vec3(1, 0,0) * m_radius, m_circProg);
		for (size_t i = startId; i < endId; i++)
		{
			
			p->m_pos[i] = m_pos + glm::vec4(position.x, position.y, position.z, 0);
		}
	}
	

	for (size_t i = startId; i < endId; i++)
	{
		p->m_vel[i] = glm::vec4(0);
	}

	for (size_t i = startId; i < endId; i++)
	{
		p->m_acc[i] = glm::vec4(0);
	}


}

void ColorGenerator::generate(double dt, ParticleData *p, size_t startId, size_t endId)
{

	for (size_t i = startId; i < endId; i++)
	{
		p->m_startCol[i] = p->m_col[i] = glm::linearRand(m_minStartColor, m_maxStartColor);
		p->m_endCol[i] = glm::linearRand(m_minEndColor, m_maxEndColor);
		std::cout << p->m_col[i].y << "\n";
	}

}

void TimeGenerator::generate(double dt, ParticleData * p, size_t startId, size_t endId)
{

	for (size_t i = startId; i < endId; i++)
	{
		p->m_time[i] = glm::linearRand(m_minStartTime, m_maxStartTime);
	}
}

void VelocityGenerator::generate(double dt, ParticleData * p, size_t startId, size_t endId)
{
	for (size_t i = startId; i < endId; i++)
	{
		p->m_vel[i] = glm::linearRand(m_minStartVel, m_maxStartVel);
	}
}

void NormalGenerator::generate(double dt, ParticleData * p, size_t startId, size_t endId)
{
	for (size_t i = startId; i < endId; i++)
	{
		p->m_norm[i] = m_startNorm;
	}
}
