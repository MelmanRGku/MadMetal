#include "ParticleData.h"
#include "..\Libraries\glm\gtc\random.hpp"
#include "..\Libraries\glm/gtx/rotate_vector.hpp"
#include <math.h>

class ParticleGenerator
{
public:

	virtual void generate(double dt, ParticleData * p, size_t startId, size_t endId) = 0;

};


class PositionGenerator : public ParticleGenerator
{
public:
	PositionGenerator(){}
	glm::vec4 m_pos{ 0.0 };
	glm::vec4 m_maxStartPosOffset{ 0.0 };



	void generate(double dt, ParticleData *p, size_t startId, size_t endId);
};

class CirclePositionGenerator : public ParticleGenerator
{
public:
	CirclePositionGenerator(){}
	glm::vec4 m_upVec{ 0.0 };
	glm::vec4 m_pos{ 0.0 };
	float m_radius;
	float m_circProg;
	bool m_randomStart;



	void generate(double dt, ParticleData *p, size_t startId, size_t endId);
};


class TimeGenerator : public ParticleGenerator
{
public:
	float m_minStartTime;
	float m_maxStartTime;

	void generate(double dt, ParticleData *p, size_t startId, size_t endId);

};

class ColorGenerator : public ParticleGenerator
{
public:
	
	glm::vec3 m_minStartColor{ 0.0 };
	glm::vec3 m_maxStartColor{ 0.0 };
	glm::vec3 m_minEndColor{ 0.0 };
	glm::vec3 m_maxEndColor{ 0.0 };


void generate(double dt, ParticleData *p, size_t startId, size_t endId);
};



class VelocityGenerator : public ParticleGenerator
{
public:
glm::vec4 m_minStartVel{ 0.0 };
glm::vec4 m_maxStartVel{ 0.0 };


void generate(double dt, ParticleData *p, size_t startId, size_t endId);
};

class NormalGenerator : public ParticleGenerator
{
public:
	glm::vec3 m_startNorm{ 1.0 };
	void generate(double dt, ParticleData *p, size_t startId, size_t endId);
};
