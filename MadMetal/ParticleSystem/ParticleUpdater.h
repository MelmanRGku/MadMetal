#include "ParticleData.h"

class ParticleUpdater
{
public:

	virtual void update(float dt, ParticleData *p) = 0;
};

class PositionUpdater : public ParticleUpdater
{
public:
	~PositionUpdater(){}

	glm::vec4 m_globalAcc{ 0.0 };
	void update(float dt, ParticleData *p);
};

class TimeUpdater : public ParticleUpdater
{
public:
	void update(float dt, ParticleData * p);

};
