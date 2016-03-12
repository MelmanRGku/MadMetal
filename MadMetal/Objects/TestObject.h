#pragma once

#include <vector>
#include "Libraries\glm\vec3.hpp"
#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtc\matrix_transform.hpp"
#include "Libraries\glm\gtx\quaternion.hpp"
#include "Renderer\Renderable.h"
#include "Renderer\Renderer.h"
#include "Physicable.h"
#include "Animatable.h"
#include "Audioable.h"
#include "Audio\Audio.h"
#include "Audio\Sound.h"

class TestObject
{
protected:
	long id;
	Renderable *m_renderable;
	Physicable *m_physicable;
	Animatable *m_animatable;
	Audioable *m_audioable;
	bool hasToBeDeleted = false;
	float totalLifeTime = 0;
	float maxLifeTime = -1;
	Sound m_sound;

public:
	TestObject(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable *rable);
	virtual ~TestObject();

	virtual bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	
	virtual glm::mat4x4 getModelMatrix();
	glm::vec3 getFullPosition() { return m_animatable->getPosition() + glm::vec3(m_physicable->getActor().getGlobalPose().p.x, m_physicable->getActor().getGlobalPose().p.y, m_physicable->getActor().getGlobalPose().p.z); }
	glm::vec3 getGlobalPose() { PxVec3 globalPose = m_physicable->getActor().getGlobalPose().p; return glm::vec3(globalPose.x, globalPose.y, globalPose.z); }
	glm::vec3 getForwardVector() { return m_physicable->getForwardVector(); }
	glm::vec3 getPosition();
	glm::vec3 getFullRotation();
	glm::vec3 getScale() { return m_animatable->getScale(); }
	glm::vec3 getAnimatablePos() { return m_animatable->getPosition(); }
	void setPosition(glm::vec3 pos) { m_animatable->setPosition(pos); }
	void setScale(glm::vec3 scale) { m_animatable->setScale(scale); }
	void updateScale(glm::vec3 ds) { m_animatable->updateScale(ds); }
	PxBounds3 getWorldBounds() { return m_physicable->getActor().getWorldBounds(); }
	long getId() { return id; }
	virtual void update(float dt) { totalLifeTime += dt; if (maxLifeTime != -1 && totalLifeTime > maxLifeTime) hasToBeDeleted = true; }
	PxRigidActor &getActor() { return m_physicable->getActor(); }
	void setHasToBeDeleted(bool hasToBeDeleted) { this->hasToBeDeleted = hasToBeDeleted; }
	bool getHasToBeDeleted() { return hasToBeDeleted; }
	void playSound();
	void setSound(Sound theSound);
	void setMaxLifeTime(float maxTime){ maxLifeTime = maxTime; }
};

