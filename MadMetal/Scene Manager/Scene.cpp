#include "Scene.h"

#define NUM_PLAYERS 2

MainMenuScene::MainMenuScene(Input * input)
{
	std::cout << "Main menu Pushed on Stack \n";
	m_gamePad = input->getGamePadHandle();
	m_currentSelection = 0;
	m_selections[0] = SceneMessage::eSingleCharSelect;
	m_selections[1] = SceneMessage::eMultiCharSelect;
	

}

bool MainMenuScene::simulateScene(double dt, SceneMessage &message)
{
	//go straight to char select screen
	message.setTag(SceneMessage::eSingleCharSelect);
	return true;

	//check gamepad stuff
	if (m_gamePad->checkConnection())
	{
		if (m_gamePad->isPressed(m_gamePad->DPadLeft))
		{
			m_currentSelection = ++m_currentSelection % 2;
			std::cout << m_currentSelection << " \n";
		}
		
		if (m_gamePad->isPressed(m_gamePad->DPadRight))
		{
			if (--m_currentSelection < 0)
			{
				m_currentSelection = 1;
			}
			std::cout << m_currentSelection << " \n";
		}

		if (m_gamePad->isPressed(m_gamePad->AButton))
		{	
			
				std::cout << "X Button Pressed \n";
				message.setTag(m_selections[m_currentSelection]);
				return true;
		}
		
	}
	else
	{
		std::cout << "Controller is Disconnected \n";
	}
	return false;
}

SinglePlayerCharSelectScene::SinglePlayerCharSelectScene(Input * input)
{
	
	std::cout << "SinglePlayer Pushed on Stack \n";
	m_gamePad = input->getGamePadHandle();
	m_playerTemplates.push_back(new ControllableTemplate(m_gamePad));

	m_currentSelection = 0;
	m_charConfirmed = false;
	
}

bool SinglePlayerCharSelectScene::simulateScene(double dt, SceneMessage &message)
{
	//go straight to load screen. remove when testing char select screen
	message.setTag(SceneMessage::eLoadScreen);
	for (int i = m_playerTemplates.size(); i < NUM_PLAYERS; i++)
	{
		//TODO:: Puts the same character in for every AI. Make random or something
		m_playerTemplates.push_back(new ControllableTemplate(m_selections[0]));
	}
	message.setPlayerTemplates(m_playerTemplates);
	
	return true;



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
			if (!m_charConfirmed)
			{
				m_charConfirmed = true;
				m_playerTemplates[0]->setCarSelection(m_currentSelection);
			}
		}
		

		if (m_gamePad->isPressed(m_gamePad->BButton))
		{
			if (m_charConfirmed)
			{
				m_charConfirmed = false;
			}
			else 
			{
				message.setTag(SceneMessage::ePop);
				return true;
			}
		}

		if (m_gamePad->isPressed(m_gamePad->StartButton))
		{
			if (m_charConfirmed)
			{
				message.setTag(SceneMessage::eLoadScreen);
				for (int i = m_playerTemplates.size(); i < NUM_PLAYERS; i++)
				{
					//TODO:: Puts the same character in for every AI. Make random or something
					m_playerTemplates.push_back(new ControllableTemplate(m_selections[0]));
				}
				message.setPlayerTemplates(m_playerTemplates);
				return true;
			}
		}
	}
	else
	{
		std::cout << "Controller is Disconnected \n";
	}
	return false;
}

MultiPlayerCharSelectScene::MultiPlayerCharSelectScene(Input * input)
{

	//distribute gamepads to scene
	for (int gpNum = 0, inputNum = 0; gpNum < 4; inputNum++)//for each game pad
	{
		if (inputNum < 4) //still gamepads to give out
		{
			if (input->getGamePadHandle(inputNum, m_gamePads[gpNum]))
			{
				std::cout << "Assigned controller " << inputNum << " to player " << gpNum << std::endl;
				gpNum++;//successfully assigned gp, go to next
			}
		}
		else 
		{
			//no more gp's to distribute
			m_gamePads[gpNum] = NULL;
		}
	}
	
	//get first non 
	for (int i = 0; i < 4; i++)
	{
		if (m_gamePads[i] != NULL)
		{
			m_playerTemplates.push_back(new ControllableTemplate(m_gamePads[i]));
			break;
		}
	}
	

}

bool MultiPlayerCharSelectScene::simulateScene(double dt, SceneMessage &message)
{


	/*/check gamepad stuff
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
			if (!m_charConfirmed)
			{
				m_charConfirmed = true;
				m_playerTemplates[0]->setCarSelection(m_currentSelection);
			}
		}


		if (m_gamePad->isPressed(m_gamePad->BButton))
		{
			if (m_charConfirmed)
			{
				m_charConfirmed = false;
			}
			else
			{
				message.setTag(SceneMessage::ePop);
				return true;
			}
		}

		if (m_gamePad->isPressed(m_gamePad->StartButton))
		{
			if (m_charConfirmed)
			{
				message.setTag(SceneMessage::eGameSimulation);
				for (int i = m_playerTemplates.size(); i < NUM_PLAYERS; i++)
				{
					//TODO:: Puts the same character in for every AI. Make random or something
					m_playerTemplates.push_back(new ControllableTemplate(m_selections[0]));
				}
				message.setPlayerTemplates(m_playerTemplates);
				return true;
			}
		}
	}
	else
	{
		std::cout << "Controller is Disconnected \n";
	}
	*/
	return false;
}

PauseScene::PauseScene(std::vector<ControllableTemplate *> playerTemplates)
{
	std::cout << "Paused the game. A to restart, B to resume \n";
	m_gamePad = playerTemplates.back()->getGamePad();
	playerTemplates.pop_back();
	toDeliver.setPlayerTemplates(playerTemplates);
}

bool PauseScene::simulateScene(double dt, SceneMessage& newMessage)
{


	//skip straight to reset
	toDeliver.setTag(SceneMessage::eRestart);
	newMessage = toDeliver;
	return true;

	if (m_gamePad->checkConnection())
	{
		if (m_gamePad->isPressed(GamePad::AButton))
		{
			toDeliver.setTag(SceneMessage::eRestart);
			newMessage = toDeliver;
			return true;
		}
		if (m_gamePad->isPressed(GamePad::BButton))
		{
			newMessage.setTag(SceneMessage::ePop);
			return true;
		}
	}
}




