#pragma once
#include "Scene.h"
#include <vector>
#include "Renderer\Renderer.h"
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
	Scene * m_currentScene;
	bool m_newMessage;
	SceneMessage * m_mailBox;

	Renderer* m_renderer;
public:
	StackManager();
	//StackManager(Scene * startScene);
	~StackManager();
	
	void progressScene(int newTime);
	void readMailBox();


};

