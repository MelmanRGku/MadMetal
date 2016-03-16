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
#include "Renderer\Animation.h"
#include <time.h>

class TestObject
{
protected:
	long id;
	Renderable *m_renderable;
	Animatable *m_animatable;
	Audioable *m_audioable;
	Animation *m_animation;
	bool hasToBeDeleted = false;
	float totalLifeTime = 0;
	float maxLifeTime = -1;
	Sound m_sound;
	clock_t start;
	int current;
	int frame;
	bool animating = false;
	Model * previousModel;

public:
	TestObject(long id, Audioable *aable, Animatable *anable, Renderable *rable);
	virtual ~TestObject();

	virtual bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) = 0;
	
	virtual glm::mat4x4 getModelMatrix() = 0;
	glm::vec3 getScale() { return m_animatable->getScale(); }
	glm::vec3 getAnimatablePos() { return m_animatable->getPosition(); }
	void setPosition(glm::vec3 pos) { m_animatable->setPosition(pos); }
	void setScale(glm::vec3 scale) { m_animatable->setScale(scale); }
	void updateScale(glm::vec3 ds) { m_animatable->updateScale(ds); }
	long getIndex() { return id; }
	void updatePosition(glm::vec3 dp) { m_animatable->updatePosition(dp); }
	void updateRotation(glm::vec3 dr) { m_animatable->updateRotation(dr); }
	long getId() { return id; }
	virtual void update(float dt) { totalLifeTime += dt; if (maxLifeTime != -1 && totalLifeTime > maxLifeTime) hasToBeDeleted = true; }
	void setHasToBeDeleted(bool hasToBeDeleted) { this->hasToBeDeleted = hasToBeDeleted; }
	bool getHasToBeDeleted() { return hasToBeDeleted; }
	virtual void playSound() = 0;
	void setSound(Sound theSound);
	void setMaxLifeTime(float maxTime){ maxLifeTime = maxTime; }
	Renderable * getRenderable(){ return m_renderable; }
};

