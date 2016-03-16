#include "MenuSystem.h"


MenuSystem::MenuSystem(Audio *audio, World *world)
{
	m_audio = audio;
	m_world = world;
}


MenuSystem::~MenuSystem()
{
}

void MenuSystem::addMenuObject(Object3D *obj) {
	m_objects.push_back(obj);
}
