#include "StackManager.h"
#include "Simulation\GameSimulation.h"
#include "Global\Log.h"
#include "Simulation\MainMenu.h"
#include "Simulation\SinglePlayerMenu.h"
#include "Simulation\MultiPlayerMenu.h"
#include "Simulation\PauseMenu.h"
#include "Simulation\EndingScene.h"
#include "Simulation\ControlsMenu.h"
#include "Simulation\MadMetalPresentsScreen.h"
#include <windows.h>
#include "winbase.h"
#include "wingdi.h"
#include "winerror.h"
#include "winternl.h"
#include "winnt.h"
#include "Renderer/CellShaderProgram.h"
#include "Renderer/NoShaderProgram.h"
#include "Renderer/CellTireShaderProgram.h"

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
	for (unsigned int i = 0; i < m_sceneStack.size(); i++)
	{
		delete m_sceneStack[i];
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
	Assets::status = new LoadingStatus();

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
	m_renderer->setShader(Renderer::ShaderType::SHADER_TYPE_CELL, new CellShaderProgram("Renderer/VertexShader.glsl", "Renderer/FragmentShader.glsl"));
	m_renderer->setShader(Renderer::ShaderType::SHADER_TYPE_NONE, new NoShaderProgram());
	m_renderer->setShader(Renderer::ShaderType::SHADER_TYPE_CELLTIRE, new CellTireShaderProgram("Renderer/VertexShader.glsl", "Renderer/TireFragmentShader.glsl"));

	m_audio = new Audio();


	//get the current opengl context and create a new one for the current device
	HGLRC ctx = wglGetCurrentContext();
	HGLRC shared = wglCreateContext(wglGetCurrentDC());

	//share lists between the two (this does not share vao and vfo)
	wglShareLists(ctx, shared);

	//create stack with loadingScreen on top
	m_mailBox->setTag(SceneMessage::eMainMenu);
	m_stack = new SceneStack(new MadMetalPresentsScreen(*m_audio, Assets::status, new std::thread(Assets::loadBeforeGameStarts, wglGetCurrentDC(), shared)));
}

StackManager::~StackManager()
{
	delete m_stack;
	delete m_audio;
	delete m_renderer;
	delete m_mailBox;
	delete m_input;
	PhysicsManager::release();
}

void StackManager::readMailBox()
{
	Log::writeLine("New Message (StackManager::readMailBox())");
	switch (m_mailBox->getTag())
	{
	case(SceneMessage::eMainMenu) :
		m_stack->clearStack();
		if (loadingThread == NULL) {
			//get the current opengl context and create a new one for the current device
			HGLRC ctx = wglGetCurrentContext();
			HGLRC shared = wglCreateContext(wglGetCurrentDC());

			//share lists between the two (this does not share vao and vfo)
			wglShareLists(ctx, shared);
			//start loading assets in the second thread and give it access to the current DC and GLRC
			loadingThread = new std::thread(Assets::load, "Assets/Models", "Assets/Textures", wglGetCurrentDC(), shared);
		}
		m_stack->pushScene(new MainMenu(m_input, m_audio));
		break;
	case(SceneMessage::eSingleCharSelect) :
		m_stack->pushScene(new SinglePlayerMenu(m_input, m_audio));
		break;
			
	case (SceneMessage::eMultiCharSelect):
		m_stack->pushScene(new MultiPlayerMenu(m_input, m_audio));
		break;

	case (SceneMessage::eLoadScreen) :
		m_mailBox->setTag(SceneMessage::eGameSimulation);
		m_stack->pushScene(new LoadingScreen(*m_mailBox, *m_audio, Assets::status, loadingThread));
		break;
	case (SceneMessage::eGameSimulation) :
	{
		m_stack->clearStack();
		int numPlayers = 0;
		for (ControllableTemplate *temp : m_mailBox->getPlayerTemplates()) {
			if (temp->getGamePad() != NULL)
				numPlayers++;
		}
		m_stack->pushScene(new GameSimulation(m_mailBox->getPlayerTemplates(), *m_audio));
		break;
	}
	case (SceneMessage::ePause) :
		m_stack->getTopScene()->onPause();
		m_stack->pushScene(new PauseMenu(m_mailBox->getPlayerTemplates(), m_audio));
		break;
	case (SceneMessage::eEnd) :
		m_stack->clearStack();
		m_stack->pushScene(new EndingScene(m_mailBox->getPlayerTemplates(), *m_audio));
		break;
	case (SceneMessage::eRestart):
		m_stack->clearStack();
		m_stack->pushScene(new MainMenu(m_input, m_audio));
		break;
	case (SceneMessage::eControls):
		m_stack->pushScene(new ControlsMenu(m_input, m_audio));
		break;
	case (SceneMessage::ePop) :
		m_stack->popScene();
		m_stack->getTopScene()->onResume();
		break;
	case (SceneMessage::eDefault) :
		std::cout << "Got a Default message.. Something went wrong \n";
		break;
	}

	//set message to blank
	m_mailBox->resetMessage();
}

bool StackManager::progressScene(int newTime)
{
	
	//calculate delta time
	double dt = static_cast<double>(newTime) / 1000;
	if (dt > .1) dt = .1;
	
	//update gamecontrollers
	m_input->updateGamePads(dt);

	//update Audio
	m_audio->update();
	
	//progress the state of the top scene on the stack
	m_newMessage = m_stack->getTopScene()->simulateScene(dt, *m_mailBox);

	
	//get cameras from the scene
	m_renderer->setViewMatrixLookAt(m_stack->getTopScene()->getSceneCameras());
	//get objects from the scene and draw
	GameSimulation *sim = dynamic_cast<GameSimulation *>(m_stack->getTopScene());
	
	if (sim != NULL)
		m_renderer->draw(sim->getWorld()->getGameObjects(), sim->getHumanPlayers(), sim->getWorld()->getLights());
	else 
		m_renderer->draw(m_stack->getTopScene()->getWorld()->getGameObjects(), NULL, m_stack->getTopScene()->getWorld()->getLights());
		
	if (m_mailBox->getTag() == SceneMessage::eExit)
		return true;

	//check if the scene return a message for manager
	if (m_newMessage)
	{
		//delete the thread if it is loading screen (when it is done)
		if (dynamic_cast<LoadingScreen *>(m_stack->getTopScene()) != NULL) {
			delete loadingThread;
			loadingThread = NULL;
		}
		m_newMessage = false;
		readMailBox();
	}

	return false;
}


void StackManager::onWindowResize(float width, float height) {
	m_renderer->recalculateViewPorts(width, height);
}
