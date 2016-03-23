#pragma once
#include "Objects\Particle.h"
#include "Factory\GameFactory.h"

#ifndef _PARTICLEDATA_H
#define _PARTICLEDATA_H
class ParticleData
{
public:
	/*
	std::unique_ptr<glm::vec4[]> m_pos;
	std::unique_ptr<glm::vec3[]> m_norm;
	std::unique_ptr<glm::vec3[]> m_col;
	std::unique_ptr<glm::vec3[]> m_startCol;
	std::unique_ptr<glm::vec3[]> m_endCol;
	std::unique_ptr<glm::vec4[]> m_vel;
	std::unique_ptr<glm::vec4[]> m_acc;
	*/
	float* m_time;
	bool* m_alive;
	
	PxVec3* m_pos;
	PxVec3* m_vel;
	PxVec3* m_acc;
	Particle** m_particles;
	size_t m_maxParticleCount{ 0 };
	size_t m_countAlive{ 0 };
	

public:
	ParticleData(size_t maxCount) { generate(maxCount); }
	~ParticleData() {}

	

	void generate(size_t maxSize);
	void kill(size_t id);
	void wake(size_t id);
	void swapData(size_t a, size_t b);
};

#endif /*_PARTICLEDATA_H*/