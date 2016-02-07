#include "ParticleEmitter.h"
#include <iostream>

void ParticleEmitter::emit(double dt, ParticleData *p)
{
	const size_t maxNewParticles = static_cast<size_t> (dt*m_emitRate);
	const size_t startId = p->m_countAlive;
	
	const size_t endId = std::min(startId + maxNewParticles, p->m_count - 1);

	for (auto &gen : generators)
	{
		gen->generate(dt, p, startId, endId);
	}

	for (size_t i = startId; i < endId; i++)
	{
		p->wake(i);
		//std::cout << p->m_col[i].x << "," << p->m_col[i].y << "," << p->m_col[i].z << "\n";
	}
}

void ParticleEmitter::addGenerator(ParticleGenerator * generator)
{
	generators.push_back(generator);
}

