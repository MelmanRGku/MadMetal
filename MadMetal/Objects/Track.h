#pragma once

#include "TestObject.h"

class Track : public TestObject
{
public:
	Track(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio* audio, TestObject *drivablePart, TestObject *nonDrivablePart);
	~Track();
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);

private: //members
	TestObject *drivablePart,
		*nonDrivablePart;
	
};
