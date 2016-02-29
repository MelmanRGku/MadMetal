#pragma once

#include <vector>
#include "Libraries\glm\vec3.hpp"
#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtc\matrix_transform.hpp"
#include "Renderer\TestRenderable.h"
#include "Physicable.h"
#include "Animatable.h"
#include "Audioable.h"
#include "Audio\Audio.h"

class TestObject
{
protected:
	//glm::vec3 position, rotation, scale, forward, up;
	TestRenderable &m_renderable;
	Physicable &m_physicable;
	Animatable &m_animatable;
	Audioable &m_audioable;
	Audio& m_audio;

public:
	TestObject(Audioable &aable, Physicable &pable, Animatable &anable, TestRenderable &rable, Audio& audio);
	virtual ~TestObject();

	virtual void draw(Renderer *renderer);
	
	virtual glm::mat4x4 getModelMatrix();
	glm::vec3 getFullPosition() { return m_animatable.getPosition() + glm::vec3(m_physicable.getActor().getGlobalPose().p.x, m_physicable.getActor().getGlobalPose().p.y, m_physicable.getActor().getGlobalPose().p.z); }
};

