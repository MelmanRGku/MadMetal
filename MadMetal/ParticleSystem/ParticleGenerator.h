#include "ParticleData.h"
#include "..\Libraries\glm\gtc\random.hpp"
#include "..\Libraries\glm/gtx/rotate_vector.hpp"
#include <math.h>

class ParticleGenerator
{
public:
	ParticleGenerator(){}
	virtual ~ParticleGenerator(){}
	virtual void generate(ParticleData & particles, size_t startId, size_t endId) = 0;

};


class PositionGenerator : public ParticleGenerator
{
public:
	PositionGenerator(PxVec3 pos) : m_pos(pos){}
	PxVec3 m_pos;
	
	void generate(ParticleData &particles, size_t startId, size_t endId);
	void updatePosition(PxVec3 pos);
};

class CirclePositionGenerator : public PositionGenerator
{
public:
	CirclePositionGenerator(PxVec3 pos, PxVec3 up, float radius, float rotateSpeed = 0.1, bool randomStart = true) 
		: PositionGenerator(pos) ,m_upVec(up), m_radius(radius), m_rotateSpeed(rotateSpeed), m_randomStart(randomStart){}
	
	PxVec3 m_upVec;
	float m_radius;
	float m_circProg;
	float m_rotateSpeed;
	bool m_randomStart;



	void generate(ParticleData &particles, size_t startId, size_t endId);
};


class TimeGenerator : public ParticleGenerator
{
public:
	TimeGenerator(float minStartTime, float maxStartTime) : m_minStartTime(minStartTime), m_maxStartTime(maxStartTime){}
	~TimeGenerator(){}
	float m_minStartTime;
	float m_maxStartTime;

	void generate(ParticleData &particles, size_t startId, size_t endId);

};

/*
class ColorGenerator : public ParticleGenerator
{
public:
	
	glm::vec3 m_minStartColor{ 0.0 };
	glm::vec3 m_maxStartColor{ 0.0 };
	glm::vec3 m_minEndColor{ 0.0 };
	glm::vec3 m_maxEndColor{ 0.0 };


	void generate(double dt, ParticleData &particles, size_t startId, size_t endId);
};

*/

class VelocityGenerator : public ParticleGenerator
{
public:
	VelocityGenerator(PxVec3 minStart, PxVec3 maxStart) : m_minStartVel(minStart), m_maxStartVel(maxStart){}
	PxVec3 m_minStartVel;
	PxVec3 m_maxStartVel;


void generate(ParticleData &p, size_t startId, size_t endId);
};

/*
class NormalGenerator : public ParticleGenerator
{
public:
	glm::vec3 m_startNorm{ 1.0 };
	void generate(double dt, ParticleData *p, size_t startId, size_t endId);
};
*/
