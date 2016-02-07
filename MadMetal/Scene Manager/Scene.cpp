#include "Scene.h"

MainMenuScene::MainMenuScene(GamePad * gamePad)
{
	m_gamePad = gamePad;
	std::cout << "Main menu Pushed on Stack \n";
	m_currentSelection = 0;
	m_selections[0] = SINGLE_CHAR_SELECT;
	m_selections[1] = MULTI_CHAR_SELECT;
	

}

bool MainMenuScene::simulateScene(double dt, SceneMessage &message)
{
	
	//check gamepad stuff
	if (m_gamePad->checkConnection())
	{
		
		if (m_gamePad->isPressed(m_gamePad->DPadLeft))
		{
			m_currentSelection = ++m_currentSelection % 2;
			std::cout << "Right arrow Pressed \n";
			std::cout << m_currentSelection << " \n";
		}
		
		if (m_gamePad->isPressed(m_gamePad->DPadRight))
		{
			if (--m_currentSelection < 0)
			{
				m_currentSelection = 1;
			}
			std::cout << "Left arrow Pressed \n";
			std::cout << m_currentSelection << " \n";
		}
		if (m_gamePad->isPressed(m_gamePad->AButton))
		{	
				std::cout << "X Button Pressed \n";
				message = SceneMessage(m_selections[m_currentSelection]);
				return true;
		}
		
	}
	else
	{
		std::cout << "Controller is Disconnected \n";
	}
	return false;
}

SinglePlayerCharSelectScene::SinglePlayerCharSelectScene(GamePad * gamePad)
{
	m_gamePad = gamePad;
	std::cout << "SinglePlayer Pushed on Stack \n";
	m_currentSelection = 0;
	m_selections[0] = m_character1;
	m_selections[1] = m_character2;
	m_selections[2] = m_character3;
}

bool SinglePlayerCharSelectScene::simulateScene(double dt, SceneMessage &message)
{


	//check gamepad stuff
	if (m_gamePad->checkConnection())
	{

		if (m_gamePad->isPressed(m_gamePad->DPadRight))
		{
			m_currentSelection = ++m_currentSelection % 3;
			std::cout << "Left arrow Pressed \n";
			std::cout << m_selections[m_currentSelection] << " \n";
		}
		
		if (m_gamePad->isPressed(m_gamePad->DPadLeft))
		{
			if (--m_currentSelection < 0)
			{
				m_currentSelection = 2;
			}
			std::cout << "Right arrow Pressed \n";
			std::cout << m_selections[m_currentSelection] << " \n";
		}
		
		if (m_gamePad->isPressed(m_gamePad->AButton))
		{
			std::cout << "X Button Pressed \n";
			PlayerControllable * newPlayer = new PlayerControllable(m_selections[m_currentSelection], m_gamePad);
			m_message = new SceneMessage(START_SINGLE_GAME);
			m_message->addPlayer(newPlayer);
			message = *m_message;
			return true;
		}
		

		if (m_gamePad->isPressed(m_gamePad->BButton))
		{
			
			std::cout << "B Button Pressed \n";
			message = SceneMessage(POP);
			return true;
			
		}
	}
	else
	{
		std::cout << "Controller is Disconnected \n";
	}
	return false;
}

SinglePlayerGameScene::SinglePlayerGameScene(PlayerControllable * player, int numPlayers)
{
	std::cout << "SinglePlayer Game Pushed onto Stack!!! \n";

	for (int i = 0; i < numPlayers - 1; i++)
	{
		//add ai players to player list
	}
	m_gamePad = player->getGamePad();
	m_player = player;
	

}

bool SinglePlayerGameScene::simulateScene(double dt, SceneMessage &message)
{


	//check gamepad stuff
	if (m_gamePad->checkConnection())
	{
		if (m_gamePad->isPressed(m_gamePad->BButton))
		{
			std::cout << "B Button Pressed \n";
			message = SceneMessage(MAIN_MENU);
			return true;
		}
	}
	else
	{
		std::cout << "Controller is Disconnected \n";
	}

	m_player->playFrame(dt);
	return false;
}


