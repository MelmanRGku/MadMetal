#include "ParticleData.h"

class ParticleUpdater
{
public:
	ParticleUpdater(){}
	virtual void update(float dt, ParticleData &p) = 0;
};

class PositionUpdater : public ParticleUpdater
{
public:
	PositionUpdater(PxVec3 globalAcc) : m_globalAcc(globalAcc){}
	~PositionUpdater(){}

	PxVec3 m_globalAcc;
	void update(float dt, ParticleData &p);
};

class TimeUpdater : public ParticleUpdater
{
public:
	void update(float dt, ParticleData & p);

};
