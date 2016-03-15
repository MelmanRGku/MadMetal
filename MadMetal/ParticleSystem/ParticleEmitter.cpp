#include "ParticleEmitter.h"
#include <iostream>

void ParticleEmitter::emit(double dt, ParticleData& particles)
{
	m_timer += dt;
	if (m_timer < m_emmitIntervalSeconds)
		return;
	m_timer = 0;

	
	size_t startId = particles.m_countAlive;
	
	const size_t endId = std::min(startId + m_emmitAmount, particles.m_maxParticleCount - 1);

	
	m_posGenerator->generate(particles, startId, endId);
	m_velGenerator->generate(particles, startId, endId);
	m_timeGenerator->generate(particles, startId, endId);

	for (size_t i = startId; i < endId; i++)
	{
		particles.wake(i);
		
	}
}

void ParticleEmitter::setPosGenerator(PositionGenerator * generator)
{
	m_posGenerator = generator;
}

void ParticleEmitter::setVelGenerator(VelocityGenerator * generator)
{
	m_velGenerator = generator;
}

void ParticleEmitter::setTimeGenerator(TimeGenerator * generator)
{
	m_timeGenerator = generator;
}

PositionGenerator* ParticleEmitter::getPosGenerator()
{
	return m_posGenerator;
}

