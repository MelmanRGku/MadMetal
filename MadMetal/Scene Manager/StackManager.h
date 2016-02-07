#pragma once
#include "Scene.h"
#include <vector>
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
	int m_currentTime;
public:
	StackManager();
	//StackManager(Scene * startScene);
	~StackManager();
	
	void progressScene(int newTime);
	void readMailBox();


};

