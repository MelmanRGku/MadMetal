#pragma once
#include "..\Input\Input.h"
#include "..\Game Logic\ControllableTemplate.h"
#include "Simulation\World.h"
#include "Objects\Camera.h"

#define NUM_CHARACTERS_AVAILABLE 3
#define MAX_NUM_HUMAN_PLAYERS 4

class SceneMessage
{
public:

	enum SceneEnum
	{
		eMainMenu,
		eSingleCharSelect,
		eMultiCharSelect,
		eLoadScreen,
		eGameSimulation,
		ePause,
		eRestart,
		ePop,
		eDefault
	};

	SceneMessage()
	{
		m_sceneType = eDefault;
	}

	SceneEnum getTag() { return m_sceneType; } //message type

	std::vector<ControllableTemplate *> getPlayerTemplates() { return m_playerTemplates; }

	void setTag(SceneEnum sceneType) {
		m_sceneType = sceneType;
	}
	void setPlayerTemplates(std::vector<ControllableTemplate *> playerTempaltes)
	{
		m_playerTemplates = playerTempaltes;
	}

	void addPlayerTemplate(ControllableTemplate* playerTemplate)
	{
		m_playerTemplates.push_back(playerTemplate);
	}

	void resetMessage()
	{
		m_sceneType = eDefault;
		m_playerTemplates.clear();

	}
private://members
	SceneEnum m_sceneType;
	std::vector<ControllableTemplate *> m_playerTemplates;
};

class Scene 
{

protected:
	bool m_isPaused;
	SceneMessage * m_message;
	World *m_world;
	Camera * m_mainCamera;

public:
	Scene() {
		m_world = new World();
		m_mainCamera = new Camera(); //dummy camera?
	}

	virtual ~Scene() {
		delete m_mainCamera;
		delete m_world;
	}
	virtual bool simulateScene(double dt, SceneMessage &newMessage) = 0;

	World* getWorld() { return m_world; }
	Camera* getMainCamera() { return m_mainCamera; }
	//virtual void loadFromFile();
};

class MainMenuScene : public Scene
{
private:
	GamePad * m_gamePad;
	int m_currentSelection;
	SceneMessage::SceneEnum m_selections[2];
	
public:
	MainMenuScene(Input * input);
	bool simulateScene(double dt, SceneMessage &newMessage);
};

class SinglePlayerCharSelectScene : public Scene
{
private:
	GamePad * m_gamePad; //handle for menu interaction
	std::vector<ControllableTemplate * > m_playerTemplates; //templates to pass to game simulation
	
	bool m_charConfirmed; //has a character been selected?
	int m_currentSelection; //the current character selected
	int m_selections[NUM_CHARACTERS_AVAILABLE]; //fill with car enums later
	

public:
	SinglePlayerCharSelectScene(Input * input);
	bool simulateScene(double dt, SceneMessage &newMessage);
};



class MultiPlayerCharSelectScene : public Scene
{
private:
	GamePad * m_gamePads[MAX_NUM_HUMAN_PLAYERS];
	bool m_charConfirmed[MAX_NUM_HUMAN_PLAYERS];
	int m_currentSelection[MAX_NUM_HUMAN_PLAYERS];
	int m_selections[NUM_CHARACTERS_AVAILABLE];

	std::vector<ControllableTemplate *> m_playerTemplates;

public:
	MultiPlayerCharSelectScene(Input * input);
	bool simulateScene(double dt, SceneMessage &newMessage);
	
};

