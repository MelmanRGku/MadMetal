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
		
		if (m_gamePad->isPressed(m_gamePad->DPadRight))
		{
			if (!m_rightPressed)
			{
				m_currentSelection = ++m_currentSelection % 2;
				m_rightPressed = true;
				std::cout << "Left arrow Pressed \n";
				std::cout << m_currentSelection << " \n";
			}	
		}
		else {
			m_rightPressed = false;
		}
		if (m_gamePad->isPressed(m_gamePad->DPadLeft))
		{
			if (!m_leftPressed)
			{
				m_leftPressed = true;
				if(--m_currentSelection < 0)
				{
					m_currentSelection = 1;
				}
				std::cout << "Left arrow Pressed \n";
				std::cout << m_currentSelection << " \n";
			}
		}
		else {
			m_leftPressed = false;
		}
		if (m_gamePad->isPressed(m_gamePad->AButton))
		{
			if (!m_aPressed)
			{
				m_aPressed = true;
				std::cout << "X Button Pressed \n";
				message = SceneMessage(m_selections[m_currentSelection]);
				return true;
			}
		}
		else {
			m_aPressed = false;
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
	m_aPressed = true;
	m_leftPressed = true;
	m_rightPressed = true;
	m_bPressed = true;
}

bool SinglePlayerCharSelectScene::simulateScene(double dt, SceneMessage &message)
{


	//check gamepad stuff
	if (m_gamePad->checkConnection())
	{

		if (m_gamePad->isPressed(m_gamePad->DPadRight))
		{
			if (!m_rightPressed)
			{
				m_currentSelection = ++m_currentSelection % 3;
				m_rightPressed = true;
				std::cout << "Left arrow Pressed \n";
				std::cout << m_selections[m_currentSelection] << " \n";
			}
		}
		else {
			m_rightPressed = false;
		}
		if (m_gamePad->isPressed(m_gamePad->DPadLeft))
		{
			if (!m_leftPressed)
			{
				m_leftPressed = true;
				if (--m_currentSelection < 0)
				{
					m_currentSelection = 2;
				}
				std::cout << "Right arrow Pressed \n";
				std::cout << m_selections[m_currentSelection] << " \n";
			}
		}
		else {
			m_leftPressed = false;
		}
		if (m_gamePad->isPressed(m_gamePad->AButton))
		{
			if (!m_aPressed)
			{
				m_aPressed = true;
				std::cout << "X Button Pressed \n";
				PlayerControllable * newPlayer = new PlayerControllable(m_selections[m_currentSelection], m_gamePad);
				m_message = new SceneMessage(START_SINGLE_GAME);
				m_message->addPlayer(newPlayer);
				message = *m_message;

				return true;
			}
		}
		else {
			m_aPressed = false;
		}

		if (m_gamePad->isPressed(m_gamePad->BButton))
		{
			if (!m_bPressed)
			{
				m_aPressed = true;
				std::cout << "B Button Pressed \n";
				message = SceneMessage(POP);
				return true;
			}
		}
		else {
			m_bPressed = false;
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
	m_bPressed = true;
	

}

bool SinglePlayerGameScene::simulateScene(double dt, SceneMessage &message)
{


	//check gamepad stuff
	if (m_gamePad->checkConnection())
	{
		if (m_gamePad->isPressed(m_gamePad->BButton))
		{
			if (!m_bPressed)
			{
				m_bPressed = true;
				std::cout << "B Button Pressed \n";
				message = SceneMessage(MAIN_MENU);
				return true;
			}
		}
		else {
			m_bPressed = false;
		}
	}
	else
	{
		std::cout << "Controller is Disconnected \n";
	}

	m_player->playFrame(dt);
	return false;
}


