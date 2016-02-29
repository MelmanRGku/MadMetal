#include "StackManager.h"
#include "Simulation\GameSimulation.h"
#include "Global\Log.h"

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
	for (unsigned int i = 0; i < m_sceneStack.size(); i++)
	{
		//handle deleting scene
	}
}

void SceneStack::clearStack()
{
	for (unsigned int i = 0; i < m_sceneStack.size(); i++)
	{
		delete m_sceneStack[i];
	}
	Log::writeLine("Cleared the Stack (SceneStack::clearStack())");
	m_sceneStack.clear();
}

Scene * SceneStack::pushScene(Scene * scene)
{
	m_sceneStack.push_back(scene);
	return m_top = scene;
}

void SceneStack::popScene()
{
	Log::writeLine("Popped top Scene (SceneStack::popScene())");
	delete m_top;
	m_sceneStack.pop_back();
	if (m_sceneStack.size() > 0)
	{
		m_top = m_sceneStack.front();
	}
	
}

Scene * SceneStack::getTopScene()
{
	return m_top;
}


StackManager::StackManager()
{
	//initaliaze input
	m_input = new Input();
	//set starting scene to Main Menu and pass a controller handle
	PhysicsManager::init();
	//intialize mail box
	m_mailBox = new SceneMessage();
	//set mail box to empty
	m_newMessage = false;

	//create a renderer and give it the shader program
	m_renderer = new Renderer();
	ShaderProgram *sp = new ShaderProgram("Renderer/VertexShader.glsl", "Renderer/FragmentShader.glsl");
	m_renderer->setShader(sp);

	m_audio = new Audio();

	//create stack with main menu on top
	m_stack = new SceneStack(new MainMenuScene(m_input));
}

StackManager::~StackManager()
{
	delete m_stack;
	delete m_audio;
	delete m_renderer;
	delete m_mailBox;
	delete m_input;
}

void StackManager::readMailBox()
{
	Log::writeLine("New Message (StackManager::readMailBox())");
	switch (m_mailBox->getTag())
	{
	case(SceneMessage::eMainMenu) :
		m_stack->clearStack();
		m_stack->pushScene(new MainMenuScene(m_input));
		break;
	case(SceneMessage::eSingleCharSelect) :
		m_stack->pushScene(new SinglePlayerCharSelectScene(m_input));
		break;
			
	case (SceneMessage::eMultiCharSelect):
		m_stack->pushScene(new MultiPlayerCharSelectScene(m_input));
		break;

	case (SceneMessage::eLoadScreen) :
		m_stack->pushScene(new LoadingScreen(*m_mailBox));
		break;
	case (SceneMessage::eGameSimulation) :
		m_stack->clearStack();
		m_stack->pushScene(new GameSimulation(m_mailBox->getPlayerTemplates(), *m_audio));
		break;

	case (SceneMessage::ePause):
		
		break;
		
	case (SceneMessage::eRestart):
		m_stack->clearStack();
		m_stack->pushScene(new GameSimulation(m_mailBox->getPlayerTemplates(), *m_audio));
		break;

	case (SceneMessage::ePop) :
		m_stack->popScene();
		break;
	case (SceneMessage::eDefault) :
		std::cout << "Got a Default message.. Something went wrong \n";
		break;
	}
	//set message to blank
	m_mailBox->resetMessage();
}

void StackManager::progressScene(int newTime)
{
	
	//calculate delta time
	double dt = static_cast<double>(newTime) / 1000;
	if (dt > .1) dt = .1;
	
	//update gamecontrollers
	m_input->updateGamePads(dt);

	//progress the state of the top scene on the stack
	m_newMessage = m_stack->getTopScene()->simulateScene(dt, *m_mailBox);
	Scene * currentScene = m_stack->getTopScene();
	if (currentScene->getMainCamera() != NULL)
	{
		
		m_renderer->setViewMatrixLookAt(
			currentScene->getMainCamera()->getPosition(),
			currentScene->getMainCamera()->getUpVector(),
			currentScene->getMainCamera()->getLookAt()
			);
	}
	m_renderer->draw(currentScene->getWorld()->getGameObjects());
	//check if the scene return a message for manager
	if (m_newMessage)
	{
		m_newMessage = false;
		readMailBox();
		
	}
}

