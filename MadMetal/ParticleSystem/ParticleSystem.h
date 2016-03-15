#pragma once
#include "ParticleEmitter.h"
#include "ParticleUpdater.h"


class ParticleSystem 
{
private:
	
	
	ParticleEmitter *emitter;
	std::vector<ParticleUpdater *> updaters;
	
	PxVec3 m_position;
	ParticleData * m_particles;
	float m_lifeSpanSeconds;
	float m_currentTimeMillis;
	
	
	//functions
	
public:
	
	
	ParticleSystem(size_t count, PxVec3 position, float lifeSpanSeconds ){
		m_position = position;
		m_lifeSpanSeconds = lifeSpanSeconds;
		m_particles = new ParticleData(count);
		emitter = new ParticleEmitter(1, 0.1);

		PositionGenerator * posGenerator = new PositionGenerator(m_position);
		emitter->setPosGenerator(posGenerator);
		
		TimeGenerator * timeGenerator = new TimeGenerator(1, 1.5);
		emitter->setTimeGenerator(timeGenerator);

		VelocityGenerator * velGenerator = new VelocityGenerator(PxVec3(0,10,0),PxVec3(0,0,0));
		emitter->setVelGenerator(velGenerator);

		
		CirclePositionGenerator * cposGenerator = new CirclePositionGenerator(m_position, PxVec3(0,1,0),5,0.5, false);
		//emitter->setPosGenerator(cposGenerator);

		

		
		/*
		ColorGenerator * colorGenerator = new ColorGenerator();
		colorGenerator->m_minStartColor = glm::vec3(1, .5, 0);
		colorGenerator->m_maxStartColor = glm::vec3(1, 1, 0);
		colorGenerator->m_minEndColor = glm::vec3(0, 0, 0);
		colorGenerator->m_maxEndColor = glm::vec3(0.2, 0.2, 0.2);
		emitter.addGenerator(colorGenerator);

		NormalGenerator * normGenerator = new NormalGenerator();
		normGenerator->m_startNorm = glm::vec3(0, 1, 1);
		emitter.addGenerator(normGenerator);
		*/

		PositionUpdater * posUpdater = new PositionUpdater(PxVec3(0,20,0));
		updaters.push_back(posUpdater);
		
		TimeUpdater* timeUpdater = new TimeUpdater();
		updaters.push_back(timeUpdater);

		

		
	}
	~ParticleSystem(){}

	void setPosition(PxVec3 newPos) { 
		m_position = newPos;
		emitter->getPosGenerator()->updatePosition(m_position);
		
	}

	bool update(float dtMillis)
	{
		//if the particle system is not set to run forever, and its life span has been exceeded return 
		if (m_lifeSpanSeconds > 0 && (m_currentTimeMillis += dtMillis) > m_lifeSpanSeconds)
		{
			std::cout << "System timed out \n";
			for (int i = 0; i < m_particles->m_maxParticleCount; i++)
			{
				m_particles->m_particles[i]->setHasToBeDeleted(true);
			}
			return false;
		}
		
		
		emitter->emit(dtMillis, *m_particles);
		for (auto &updater : updaters)
		{
			updater->update(dtMillis, *m_particles);
		}
	}

};