#pragma once
#include "Scene.h"
#include <vector>
#include "Renderer\Renderer.h"
#include "Simulation\PhysicsManager.h"
#include "Simulation\LoadingScreen.h"
#include "Audio\Audio.h"
#include "Input\Input.h"

class SceneStack
{
private:
	Scene * m_top;
	std::vector<Scene*> m_sceneStack;
	
public:
	SceneStack();
	SceneStack(Scene * scene);
	~SceneStack();
	Scene * pushScene(Scene *scene);
	void popScene();
	void clearStack();
	Scene * getTopScene();

};

class StackManager
{
private:
	Input * m_input;
	SceneStack * m_stack;
	bool m_newMessage;
	SceneMessage * m_mailBox;
	std::thread *loadingThread;

	Renderer* m_renderer;
	Audio *m_audio;
	
	
public:
	StackManager();
	//StackManager(Scene * startScene);
	~StackManager();
	
	//true if game has ended, false otherwise
	bool progressScene(int newTime);
	void readMailBox();
	void onWindowResize(float width, float height);

};

