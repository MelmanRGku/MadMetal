#pragma once

#include "Object3D.h"
#include "Simulation\World.h"
#include "Scene Manager\Scene.h"

class MenuSystem
{
protected:
	std::vector<Object3D*> m_objects;
	Object3D *m_selectedObject;
	int m_selectedObjectIndex;
	World *m_world;
	Audio *m_audio;
	SceneMessage::SceneEnum messageToReturn = SceneMessage::eNone;

public:
	MenuSystem(Audio *audio, World *world);
	~MenuSystem();
	void addMenuObject(Object3D *obj);
	virtual void upPressed() = 0;
	virtual void downPressed() = 0;
	virtual void leftPressed() = 0;
	virtual void rightPressed() = 0;
	virtual void aPressed() = 0;
	SceneMessage::SceneEnum getMessage() { return messageToReturn; }
};

