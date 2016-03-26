#pragma once

#include "TestObject.h"
#include "Renderer\Renderable3D.h"

class Object3D : public TestObject
{
protected:
	Physicable *m_physicable;
	Animation *m_animation;

public:
	Object3D(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Animation *aniable);
	virtual ~Object3D();

	virtual bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	virtual void update(float dt) { TestObject::update(dt); }

	virtual glm::mat4x4 getModelMatrix();
	glm::vec3 getAnimatablePosition() { return m_animatable->getPosition(); }
	glm::vec3 getFullPosition() { return m_animatable->getPosition() + glm::vec3(m_physicable->getActor().getGlobalPose().p.x, m_physicable->getActor().getGlobalPose().p.y, m_physicable->getActor().getGlobalPose().p.z); }
	glm::vec3 getGlobalPose() { PxVec3 globalPose = m_physicable->getActor().getGlobalPose().p; return glm::vec3(globalPose.x, globalPose.y, globalPose.z); }
	glm::vec3 getForwardVector() { return m_physicable->getForwardVector(); }
	glm::vec3 getPosition();
	glm::vec3 getFullRotation();
	PxBounds3 getWorldBounds() { return m_physicable->getActor().getWorldBounds(); }
	PxRigidActor &getActor() { return m_physicable->getActor(); }
	void playSound();
	void startAnimation();
	void updateAnimation();
};

