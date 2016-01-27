#include "Input.h"

Input::Input() {
	int counter = 0;
	for (int i = 0; i< XUSER_MAX_COUNT; i++)
	{

		gamePads[i] = new GamePad(i);
		if (gamePads[i]->checkConnection()){
			counter++;
		}

	}
};

void Input::updateGamePads()
{
	for (int i = 0; i < XUSER_MAX_COUNT; i++)
	{
		if (gamePads[i]->checkConnection())
		{
			gamePads[i]->sampleState();
		}
	}

}

bool Input::getGamePadHandle(int portNum, GamePad** handle)
{
	if (gamePads[portNum]->checkConnection())
	{	
		if (!gamePads[portNum]->isOwned())
		{
			*handle = gamePads[portNum];
			char *line = new char[50];
			sprintf_s(line, 50, "Controller at port %d is now owned", portNum);
			Log::writeLine(line);
			return true;
		}
		else 
		{
			char *line = new char[100];
			sprintf_s(line, 100, "Request for controller at port %d. Controller is already owned", portNum);
			Log::writeLine(line);
			return false;
		}

	}
	else 
	{
		char *line = new char[100];
		sprintf_s(line, 100, "Request for controller at port %d. No controller connected", portNum);
		Log::writeLine(line);
		return false;
	}
}

void Input::releaseGamePadHandle(int portNum, GamePad ** handle)
{
	char *line = new char[100];
	sprintf_s(line, 100, "Handle for controller at port %d is returned ", portNum);
	Log::writeLine(line);

	*handle = new GamePad();
	gamePads[portNum]->setOwned(false);
	
}