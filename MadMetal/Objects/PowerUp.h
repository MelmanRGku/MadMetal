#pragma once
#include "Object3D.h"
#include "Global\Assets.h"




#define ATTACK_DURATION_SECONDS 5
#define DEFENSE_DURATION_SECONDS 5
#define SPEED_DURATION_SECONDS 5
#define RESPAWN_DELAY_SECONDS 5

#define LIFESTEAL_PERCENTAGE 0.5
#define SPEED_IMPACT_DAMAGE 50

enum PowerUpType {
	NONE,
	ATTACK,
	DEFENSE,
	SPEED
};

class PowerUp : public Object3D
{
private:
	PowerUpType m_type;
	float m_respawnDelay;
	const float m_attackDuration = ATTACK_DURATION_SECONDS;
	const float m_defenseDuration = DEFENSE_DURATION_SECONDS;
	const float m_speedDuration = SPEED_DURATION_SECONDS;
	const float m_attackLifeSteal = LIFESTEAL_PERCENTAGE;
	const float m_speedImpactDamage = SPEED_IMPACT_DAMAGE;

public:
	

	PowerUp(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable);
	virtual ~PowerUp();
	
	virtual void update(float dtMillis);
	bool isActive();
	PowerUpType pickup();
	void activate();
	static float getPowerUpDuration(PowerUpType toGet);
	static float getLifeStealPercentage();
	static float getSpeedImpactDamage();

	

	

};