#include "ParticleData.h"
void ParticleData::generate(size_t maxSize)
{
	m_maxParticleCount = maxSize;
	m_countAlive = 0;
	
	m_pos = new PxVec3[maxSize];
	m_vel = new PxVec3[maxSize];
	m_acc = new PxVec3[maxSize];
	m_alive = new bool[maxSize];
	m_time = new float[maxSize];
	m_particles = new Particle*[maxSize];

	PxGeometry*geom[1];
	for (size_t i = 0; i < maxSize; i++)
	{
		
		geom[0] = new PxBoxGeometry(.25, 1, .25);
		m_particles[i] = static_cast<Particle*>(GameFactory::instance()->makeObject(GameFactory::OBJECT_PARTICLE, &PxTransform(PxVec3(0, 0, 0)), geom, NULL));
		m_alive[i] = false;
		
	}
	
	delete geom[0];

	/*m_pos.reset(new glm::vec4[maxSize]);
	m_col.reset(new glm::vec3[maxSize]);
	m_startCol.reset(new glm::vec3[maxSize]);
	m_endCol.reset(new glm::vec3[maxSize]);
	m_vel.reset(new glm::vec4[maxSize]);
	m_acc.reset(new glm::vec4[maxSize]);
	m_time.reset(new float[maxSize]);
	m_alive.reset(new bool[maxSize]);
	m_norm.reset(new glm::vec3[maxSize]);*/
}

void ParticleData::kill(size_t id)
{
	/*if (m_countAlive > 0)
	{
		m_alive[id] = false;
		m_particles[id]->setAlive(false);
		swapData(id, m_countAlive - 1);
		m_countAlive--;
	}*/
}

void ParticleData::wake(size_t id)
{
	/*if (m_countAlive < m_maxParticleCount)
	{
		m_alive[id] = true;
		m_particles[id]->setAlive(true);
		swapData(id, m_countAlive);
		
		m_countAlive++;
	}*/

}

void ParticleData::swapData(size_t a, size_t b)
{
	
	//std::swap(m_norm[a], m_norm[b]);
	//std::swap(m_col[a], m_col[b]);
	//std::swap(m_startCol[a], m_startCol[b]);
	//std::swap(m_endCol[a], m_endCol[b]);
	std::swap(m_pos[a], m_pos[b]);
	std::swap(m_vel[a], m_vel[b]);
	std::swap(m_acc[a], m_acc[b]);
	std::swap(m_time[a], m_time[b]);
	std::swap(m_alive[a], m_alive[b]);
	std::swap(m_particles[a], m_particles[b]);
}

