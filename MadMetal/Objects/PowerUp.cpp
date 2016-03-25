#include "PowerUp.h"
#include "ParticleSystem\ParticleEmitter.h"


PowerUp::PowerUp(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable, NULL)
{
	m_emitter = new ParticleEmitter(0.1, PxVec3(0, 10, 0), 1, "powerup_particle_attack", static_cast<Object3D * > (this));
	activate();

	m_floatingYUpperLimit = m_floatingYLowerLimit = getAnimatablePos().y;
	m_floatingYLowerLimit -= 1;
	m_floatingYUpperLimit += 1;
	m_floatingUp = true;
	
	
}

PowerUp::~PowerUp()
{
	delete m_emitter;
}

bool PowerUp::isActive()
{
	return m_respawnDelay <= 0;
}


float PowerUp::getLifeStealPercentage()
{
	return LIFESTEAL_PERCENTAGE;
}

float PowerUp::getSpeedImpactDamage()
{
	return SPEED_IMPACT_DAMAGE;
}

float PowerUp::getSpeedImpulse()
{
	return SPEED_IMPULSE_AMOUNT;
}

void PowerUp::update(float dtMillis)
{
	if (m_respawnDelay > 0)
	{
		if ((m_respawnDelay -= dtMillis) <= 0)
		{
			activate();
		}
	} else 
	 {
		if (m_floatingUp)
		{
			
			if (getAnimatablePos().y > m_floatingYUpperLimit)
			{
				m_floatingUp = false;
			}
		}
		else {
			if (getAnimatablePos().y < m_floatingYLowerLimit)
			{
				m_floatingUp = true;
			}
		}
		//std::cout << getPosition().y << ", " << m_floatLowerLimit.y << "," << m_floatUpperLimit.y << std::endl;
		updatePosition(glm::vec3(0, m_floatingUp ? dtMillis * 2 : -dtMillis * 2, 0));
		
		 m_emitter->update(dtMillis);
	 }
}
void PowerUp::setActiveType(int type)
{
	
	switch (type)
	{
	case(1) :
		m_type = PowerUpType::ATTACK;
		m_renderable->setModel(Assets::getModel("attackPowerUp_pickup"));
		m_emitter->setParticleModel("powerup_particle_attack");
		break;
	case(2) :
		m_type = PowerUpType::DEFENSE;
		m_renderable->setModel(Assets::getModel("sheildPowerUp_pickup"));
		m_emitter->setParticleModel("powerup_particle_defense");
		break;
	case(3) :
		m_type = PowerUpType::SPEED;
		m_renderable->setModel(Assets::getModel("speedPowerUp_pickup"));
		m_emitter->setParticleModel("powerup_particle_speed");
		break;
	default:
		m_type = PowerUpType::NONE;
		break;
	}
	static_cast<Renderable3D *>(m_renderable)->adjustModel(true, true);
}

void PowerUp::activate()
{
	int choice = 1 + rand() % 3;
	
	switch (choice)
	{
	case(1) :
		m_type = PowerUpType::ATTACK;
		m_renderable->setModel(Assets::getModel("attackPowerUp_pickup"));
		m_emitter->setParticleModel("powerup_particle_attack");
		break;
	case(2) :
		m_type = PowerUpType::DEFENSE;
		m_renderable->setModel(Assets::getModel("sheildPowerUp_pickup"));
		m_emitter->setParticleModel("powerup_particle_defense");
		break;
	case(3) :
		m_type = PowerUpType::SPEED;
		m_renderable->setModel(Assets::getModel("speedPowerUp_pickup"));
		m_emitter->setParticleModel("powerup_particle_speed");
		break;
	default:
		m_type = PowerUpType::NONE;
		break;
	}
	static_cast<Renderable3D *>(m_renderable)->adjustModel(true, true);
}

float PowerUp::getPowerUpDuration(PowerUpType toGet)
{
	switch (toGet)
	{
	case(ATTACK) :
		return ATTACK_DURATION_SECONDS;
	case(DEFENSE) :
		return DEFENSE_DURATION_SECONDS;
	case(SPEED) :
		return SPEED_DURATION_SECONDS;
	default:
		return 0;
	}
}
PowerUpType PowerUp::pickup()
{
	
	m_respawnDelay = RESPAWN_DELAY_SECONDS;
	m_renderable->setModel(NULL);
	return m_type;
	
}

