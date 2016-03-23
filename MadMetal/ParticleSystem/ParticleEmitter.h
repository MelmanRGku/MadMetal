#pragma once
#include "ParticleGenerator.h"

#include <vector>

class ParticleEmitter
{
private:
	std::vector<ParticleGenerator *> m_generators;
	PositionGenerator* m_posGenerator;
	VelocityGenerator* m_velGenerator;
	TimeGenerator * m_timeGenerator;
	
	float m_emmitIntervalSeconds;
	float m_timer;
	int m_emmitAmount;

public:
	
	ParticleEmitter(int emmitAmount, float emmitIntervalSeconds) : m_emmitAmount(emmitAmount), m_emmitIntervalSeconds(emmitIntervalSeconds){ m_timer = 0; }
	~ParticleEmitter(){}
	
	void setPosGenerator(PositionGenerator * generator);
	PositionGenerator* getPosGenerator();
	void setVelGenerator(VelocityGenerator * generator);
	void setTimeGenerator(TimeGenerator * generator);
	void emit(double dt, ParticleData& p);

};