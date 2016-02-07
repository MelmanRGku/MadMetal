#include "StackManager.h"

SceneStack::SceneStack(Scene * scene)
{
	m_top = scene;
	pushScene(scene);
}

SceneStack::SceneStack()
{

}

SceneStack::~SceneStack()
{
	delete m_top;
	for (int i = 0; i < m_sceneStack.size(); i++)
	{
		//handle deleting scene
	}
}

void SceneStack::clearStack()
{
	for (int i = 0; i < m_sceneStack.size(); i++)
	{
		delete m_sceneStack[i];
	}
	std::cout << "Cleared the Stack!! \n";
	m_sceneStack.clear();
}

Scene * SceneStack::pushScene(Scene * scene)
{
	m_sceneStack.push_back(scene);
	return m_top = scene;
}

void SceneStack::popScene()
{
	std::cout << "Popped top Scene. \n";
	//delete m_top
	m_sceneStack.pop_back();
	m_top = m_sceneStack.back();
}

Scene * SceneStack::getTopScene()
{
	return m_top;
}


StackManager::StackManager()
{
	//initaliaze inptu
	m_input = new Input();
	//set starting scene to Main Menu and pass a controller handle
	m_currentScene = new MainMenuScene(m_input->getGamePadHandle());
	//intialize mail box
	m_mailBox = new SceneMessage();
	//set mail box to empty
	m_newMessage = false;
	//create stack with main menu on top
	m_stack = new SceneStack(m_currentScene);
}

StackManager::~StackManager()
{
	delete m_input;
	delete m_currentScene;
	delete m_mailBox;
	delete m_stack;
}

void StackManager::readMailBox()
{
	std::cout << "New Message!! \n";
	switch (m_mailBox->getTag())
	{
	case(MAIN_MENU) :
		m_stack->clearStack();
		m_stack->pushScene(new MainMenuScene(m_input->getGamePadHandle()));
		break;
	case(SINGLE_CHAR_SELECT) :
		m_currentScene->setPaused(true);
		m_stack->pushScene(new SinglePlayerCharSelectScene(m_input->getGamePadHandle()));
		m_currentScene = m_stack->getTopScene();
		break;
	case (START_SINGLE_GAME) :
		m_stack->clearStack();
		m_currentScene = m_stack->pushScene(new SinglePlayerGameScene(m_mailBox->getPlayers().front(), 4));
		break;
	case (MULTI_CHAR_SELECT) :
		
		break;
	case (START_MULTI_GAME) :
		
		break;
	case (POP) :
		m_stack->popScene();
		m_currentScene = m_stack->getTopScene();
		m_currentScene->setPaused(false);
		break;
	}
}

void StackManager::progressScene(int newTime)
{
	//update gamecontrollers
	m_input->updateGamePads();

	//calculate delta time
	double dt = (double)(newTime - m_currentTime) / 1000;

	//progress the state of the top scene on the stack
	m_newMessage = m_currentScene->simulateScene(dt, *m_mailBox);
	//check if the scene return a message for manager
	if (m_newMessage)
	{
		m_newMessage = false;
		readMailBox();
		
	}
}

