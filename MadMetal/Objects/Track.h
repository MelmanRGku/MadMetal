#pragma once

#include "TestObject.h"

class Track : public TestObject
{
public:
	Track(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable *rable, TestObject *drivablePart, TestObject *nonDrivablePart);
	~Track();
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	TestObject *getDrivablePart() { return drivablePart; }

private: //members
	TestObject *drivablePart,
		*nonDrivablePart;
	
};
