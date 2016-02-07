#include "ParticleUpdater.h"
#include <iostream>

void PositionUpdater::update(double dt, ParticleData * p)
{
	const glm::vec4 accel{ dt * m_globalAcc.x,
		dt * m_globalAcc.y,
		dt * m_globalAcc.z,
		0.0 };
	const float localDT = (float)dt;

	const unsigned int endId = p->m_countAlive;

	for (size_t i = 0; i < p->m_countAlive; i++)
	{
		p->m_acc[i] += accel;
	}

	for (size_t i = 0; i < p->m_countAlive; i++)
	{
		p->m_vel[i] += localDT * p->m_acc[i];
	}

	for (size_t i = 0; i < p->m_countAlive; i++)
	{
		p->m_pos[i] += localDT * p->m_vel[i];
	}
}

void TimeUpdater::update(double dt, ParticleData * p)
{
	const float localDT = (float)dt;
	for (size_t i = 0; i < p->m_countAlive; i++)
	{
		if ((p->m_time[i] -= localDT) <= 0)
		{
			p->kill(i);
		}
	}
}

void AttractorUpdater::update(double dt, ParticleData *p)
{
	const float localDT = (float)dt;
	
	for (size_t i = 0; i < p->m_countAlive; i++)
	{
		
		float distance = (m_pos.y - p->m_pos[i].y) ;
		if (abs(distance) < m_radius && abs(distance) >= 0.01 )
		{
			float scalar = localDT * 1 / distance;
			glm::vec4 dVec = glm::vec4(scalar / 100, 0, 0, 0);

			//float distance = sqrt(dVec.x * dVec.x + dVec.y * dVec.y + dVec.z * dVec.z);
			p->m_pos[i] += dVec;
		}
		

	}
}

void ColorUpdater::update(double dt, ParticleData *p)
{
	double scalar = dt / 4;
	for (size_t i = 0; i < p->m_countAlive; i++)
	{
		p->m_col[i] -= glm::vec3(scalar, scalar, scalar);
	}
}