#include "ParticleData.h"

class ParticleUpdater
{
public:

	virtual void update(double dt, ParticleData *p) = 0;
};

class PositionUpdater : public ParticleUpdater
{
public:
	~PositionUpdater(){}

	glm::vec4 m_globalAcc{ 0.0 };
	void update(double dt, ParticleData *p);
};

class TimeUpdater : public ParticleUpdater
{
public:
	void update(double dt, ParticleData * p);

};


class AttractorUpdater : public ParticleUpdater
{
public:
	glm::vec4 m_pos;
	//glm::vec4 m_strength;
	float m_radius;
	void update(double dt, ParticleData * p);
};

class ColorUpdater : public ParticleUpdater
{
public:
~ColorUpdater(){}
void update(double dt, ParticleData *p);
};
