#pragma once
#include "ParticleGenerator.h"
#include <algorithm>
#include <vector>

class ParticleEmitter
{
private:
	std::vector<ParticleGenerator *> generators;
	

public:
	
	ParticleEmitter(){}
	~ParticleEmitter(){}
	size_t m_emitRate;
	void addGenerator(ParticleGenerator * generator);
	void emit(double dt, ParticleData * p);

};