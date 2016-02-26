#pragma once
#include "PhysicsFactory.h"
#include "RenderFactory.h"
#include "AudioFactory.h"

class GameFactory
{
public:
	GameFactory(){}
	~GameFactory(){}
private: //members
	PhysicsFactory * m_physicsFactory;
	RenderFactory * m_renderFactory;
	AudioFactory * m_audioFactory;
	
private:

};