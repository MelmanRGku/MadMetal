#define ATTACK_DURATION 5;
#define DEFENSE_DURATION 5;
#define SPEED_DURATION 5;

enum PowerUpType {
	NONE,
	ATTACK,
	DEFENSE,
	SPEED
};

class PowerUp
{
private:

	const float m_attackDuration = ATTACK_DURATION;
	const float m_defenseDuration = DEFENSE_DURATION;
	const float m_speedDuration = SPEED_DURATION;
	PowerUpType m_type;
public:
	
	PowerUp(){ m_type = NONE; }

	void setPowerUp(PowerUpType type)
	{
		if (m_type != NONE)
			return;
		m_type = type;
	}


	PowerUpType getType()
	{
		return m_type;
	}

	float getPowerUpDuration()
	{
		if (m_type == ATTACK)
			return m_attackDuration;
		if (m_type == DEFENSE)
			return m_defenseDuration;
		if (m_type == SPEED)
			return m_speedDuration;

		return 0;
	}

	

};