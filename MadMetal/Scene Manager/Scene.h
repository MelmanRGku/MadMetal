#pragma once
#include "..\Input\Input.h"
#include "..\Game Logic\PlayerControllable.h"
#include "Simulation\World.h"


const int MAIN_MENU = 0;
const int SINGLE_CHAR_SELECT = 1;
const int START_SINGLE_GAME = 2;
const int PAUSE_GAME = 3;
const int MULTI_CHAR_SELECT = 4;
const int START_MULTI_GAME = 5;
const int POP = 6;

class SceneMessage
{


	int m_tag;
	int m_numPlayers;

	std::vector<PlayerControllable *> m_players;


public:
	

	//used for main menu, single char select, multi char select and pop
	SceneMessage(int tag) : m_tag(tag)
	{
		m_players.clear();
	}
	SceneMessage() : m_tag(-1){}

	//used for starting new single game, starting new multi game
	SceneMessage(int tag, int numPlayers, std::vector<PlayerControllable *> players) : m_tag(tag), m_numPlayers(numPlayers), m_players(players){}


	int getTag() { return m_tag; } //message type
	int getNumPlayers() { return m_numPlayers; } //max number of players 
	std::vector<PlayerControllable *> getPlayers() { return m_players; } //player controllable characters for new game

	void setTag(int tag) {
		m_tag = tag;
	}
	void addPlayer(PlayerControllable * toAdd)
	{
		m_players.push_back(toAdd);
	}

};

class Scene 
{

protected:
	bool m_isPaused;
	SceneMessage * m_message;
	World *world;
public:
	Scene() {
		world = new World();
	}

	virtual ~Scene() {
		delete world;
	}
	virtual bool simulateScene(double dt, SceneMessage &newMessage) = 0;
	bool isPaused() { return m_isPaused; }
	//set paused will need to be updated to pause sound at the same time
	void setPaused(bool paused) { m_isPaused = paused; }
	World* getWorld() { return world; }
	//virtual void loadFromFile();
};

class MainMenuScene : public Scene
{
private:
	GamePad * m_gamePad;
	int m_currentSelection;
	int m_selections[2];
	
public:
	MainMenuScene(GamePad * gamePad);
	bool simulateScene(double dt, SceneMessage &newMessage);
};

class SinglePlayerCharSelectScene : public Scene
{
private:
	GamePad * m_gamePad;
	int m_currentSelection;
	
	char * m_character1 = "Character1.txt";
	char * m_character2 = "Character2.txt";
	char * m_character3 = "Character3.txt";
	char * m_selections[3]; 
	

public:
	SinglePlayerCharSelectScene(GamePad * gamePad);
	bool simulateScene(double dt, SceneMessage &newMessage);
};

class SinglePlayerGameScene : public Scene
{
private:
	GamePad * m_gamePad;
	PlayerControllable * m_player;

public:
	SinglePlayerGameScene(PlayerControllable * player, int numPlayers);
	bool simulateScene(double dt, SceneMessage &newMessage);
};

/*
class MultiPlayerCharSelectionScene : Scene
{
private:
	GamePad * m_gamePads[4];
	int * m_charSelections[4];
	std::vector<PlayerControllable *> m_players;
public:
	MultiPlayerCharSelectionScene(GamePad * gamePads);
	bool simulateScene(SceneMessage &newMessage);
	
};*/