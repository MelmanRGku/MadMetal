#pragma once
#include "Object3D.h"


#define TRAIN_SPEED 70
#define TRAIN_DISTANCE 800
class TrainCar : public Object3D
{
public:
	TrainCar(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, PxVec3 startPos) : Object3D(id, aable, pable, anable, rable, NULL)
	{
		m_startPos = startPos;
		m_endPos = m_startPos + PxVec3(0, 0, TRAIN_DISTANCE);
		m_vel = PxVec3(0, 0, TRAIN_SPEED);
		m_physicable->getActor().setGlobalPose(PxTransform(m_startPos));
	}

	virtual ~TrainCar(){}
	void update(float dtMillis)
	{
		static_cast<PxRigidDynamic *>(&m_physicable->getActor())->setLinearVelocity(m_vel);
		if ((m_endPos - m_physicable->getActor().getGlobalPose().p).dot(PxVec3(m_physicable->getForwardVector().x, m_physicable->getForwardVector().y, m_physicable->getForwardVector().z)) < 0)
		{
			
			m_physicable->getActor().setGlobalPose(PxTransform(m_startPos));
		}
	}

	void playSound()
	{
		m_audioable->getAudioHandle().queAudioSource(&this->getActor(), m_sound, 1.0f, false, -1);
	}


private: //members
	PxVec3 m_startPos;
	PxVec3 m_endPos;
	PxVec3 m_vel;


};