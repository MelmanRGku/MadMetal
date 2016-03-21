#include "PowerUp.h"
#include "ParticleSystem\ParticleSystem.h"

PowerUp::PowerUp(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable)
{
	activate();
	PxVec3 dimensions = pable->getActor().getWorldBounds().getDimensions(); 
	PxVec3 position = pable->getActor().getGlobalPose().p;
	
}

PowerUp::~PowerUp()
{

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
	}
}

void PowerUp::activate()
{
	int choice = 1 + rand() % 3;
	switch (choice)
	{
	case(1) :
		m_type = PowerUpType::ATTACK;
		break;
	case(2) :
		m_type = PowerUpType::DEFENSE;
		break;
	case(3) :
		m_type = PowerUpType::SPEED;
		break;
	default:
		m_type = PowerUpType::NONE;
		break;
	}
	m_renderable->setModel(Assets::getModel("sword"));
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
	case(3) :
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

