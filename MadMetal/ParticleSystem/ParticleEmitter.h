#pragma once
#include "Objects\Particle.h"
#include "Factory\GameFactory.h"
#include "glm\gtx\rotate_vector.hpp"
#include <vector>

class ParticleEmitter
{
private:
	bool m_circle_generation;
	float m_emmitIntervalSeconds;
	float m_emmitTimer;

	float m_maxLifeTime;
	float m_lifeTimer;

	float m_particleLifeTime;

	PxVec3 m_position;
	PxVec3 m_emmitVelocity;
	Object3D * m_parent;
	std::string m_model;



public:
	
	ParticleEmitter(float emmitIntervalSeconds, PxVec3 emmitVelocity, float particleLifeTimeSeconds, std::string model, Object3D * parent, bool circle_generation = true, float lifeTime = -1)
	{
		m_maxLifeTime = lifeTime;
		m_emmitIntervalSeconds = emmitIntervalSeconds;
		m_particleLifeTime = particleLifeTimeSeconds;
		m_emmitVelocity = emmitVelocity;
		m_model = model;
		m_parent = parent;
		m_position = m_parent->getActor().getGlobalPose().p;
		m_circle_generation = circle_generation;
	}

	~ParticleEmitter()
	{
		
	}
	
	void setParticleModel(std::string model)
	{
		m_model = model;
	}

	void update(double dtMillis)
	{
		
		m_lifeTimer -= dtMillis;
		
		if (m_parent != NULL)
		{
			m_position = m_parent->getActor().getGlobalPose().p;
		}
			
		m_emmitTimer += dtMillis;
		if (m_emmitTimer > m_emmitIntervalSeconds)
		{
			m_emmitTimer = 0;
			emit();
		}

		
	}

	float getTimeRemaining()
	{
		return m_lifeTimer;
	}

#define HEALTH_SCALE .25, .5, .25
#define POWER_UP_SCALE .5, 1, .5
	void emit()
	{
		glm::vec3 rotate;
		if (m_circle_generation)
		{
			rotate = glm::rotateY(glm::vec3(3, 0, 0), (float)(rand() % 360));

		} 
			PxGeometry * geom[1];
			geom[0] = new PxBoxGeometry(.5, 1,.5);
			Particle * particle = static_cast<Particle*> (GameFactory::instance()->makeObject(GameFactory::OBJECT_PARTICLE, &PxTransform(PxVec3(m_position.x + rotate.x, 0, m_position.z + rotate.z)), geom, NULL));
			delete geom[0];
			particle->setMaxLifeTime(m_particleLifeTime);
			particle->getRenderable()->setModel(Assets::getModel(m_model));
			if (m_model == "powerup_particle_attack" || m_model == "powerup_particle_defense" || m_model == "powerup_particle_speed")
			{
				particle->setScale(glm::vec3(POWER_UP_SCALE));
			}
			else {
				particle->setScale(glm::vec3(HEALTH_SCALE));
			}
			
			PxRigidDynamic * actor = static_cast<PxRigidDynamic* >(&particle->getActor());
			PxRigidDynamic * parent;
			if ((parent = static_cast<PxRigidDynamic*>(&m_parent->getActor())->isRigidDynamic()))
			{
				actor->setLinearVelocity(m_emmitVelocity + parent->getLinearVelocity());
			}
			else {
				actor->setLinearVelocity(m_emmitVelocity);
			}
			
			
		
	}

};