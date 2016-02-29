#pragma once

#include <vector>
#include "Libraries\glm\vec3.hpp"
#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtc\matrix_transform.hpp"
#include "Renderer\Renderable.h"
#include "Renderer\Renderer.h"
#include "Physicable.h"
#include "Animatable.h"
#include "Audioable.h"
#include "Audio\Audio.h"

class TestObject
{
protected:
	long id;
	Renderable &m_renderable;
	Physicable &m_physicable;
	Animatable &m_animatable;
	Audioable &m_audioable;
	Audio& m_audio;

public:
	TestObject(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio);
	virtual ~TestObject();

	virtual void draw(Renderer *renderer);
	
	virtual glm::mat4x4 getModelMatrix();
	glm::vec3 getFullPosition() { return m_animatable.getPosition() + glm::vec3(m_physicable.getActor().getGlobalPose().p.x, m_physicable.getActor().getGlobalPose().p.y, m_physicable.getActor().getGlobalPose().p.z); }
	glm::vec3 getForwardVector() { return m_physicable.getForwardVector(); }
	glm::vec3 getPosition();
	void updateScale(glm::vec3 ds) { m_animatable.updateScale(ds); }
	PxBounds3 getWorldBounds() { return m_physicable.getActor().getWorldBounds(); }
	long getId() { return id; }
};

