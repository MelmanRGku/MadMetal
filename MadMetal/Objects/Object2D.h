#pragma once

#include "TestObject.h"
#include "Renderer\Renderable2D.h"

class Object2D : public TestObject
{
protected:
	bool hasToBeDeleted = false;
	float totalLifeTime = 0;
	float maxLifeTime = -1;

public:
	Object2D(long id, Audioable *aable, Animatable *anable, Renderable2D *rable);
	virtual ~Object2D();

	virtual bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);

	virtual glm::mat4x4 getModelMatrix();
	virtual void update(float dt);
	void playSound();
};

