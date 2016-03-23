#include "Input.h"
#include <sstream>
#include <string>
#include "Global\Log.h"

Input::Input() {
	
	int counter = 0;
	for (int i = 0; i< XUSER_MAX_COUNT; i++)
	{

		gamePads[i] = new GamePad(i);
		if (gamePads[i]->checkConnection()){
			counter++;
		}

	}
	
	std::stringstream ss;
	ss << "Initialized Input. " << counter << " controllers connected";
	Log::writeLine(ss.str());
};

Input::~Input() {
	for (int i = 0; i< XUSER_MAX_COUNT; i++)
	{

		delete gamePads[i];

	}
}

void Input::updateGamePads(double dt)
{
	for (int i = 0; i < XUSER_MAX_COUNT; i++)
	{
		if (gamePads[i]->checkConnection())
		{
			gamePads[i]->sampleState(dt);
		}
	}

}

bool Input::getGamePadHandle(int portNum, GamePad** handle)
{
	if (gamePads[portNum]->checkConnection())
	{	
		*handle = gamePads[portNum];
		return true;
	}
	else 
	{
		char *line = new char[100];
		sprintf_s(line, 100, "Request for controller at port %d. No controller connected", portNum);
		Log::writeLine(line);
		delete[] line;
		return false;
	}
}


GamePad * Input::getGamePadHandle()
{

	for (int portNum = 0; portNum < 4; portNum++)
	{
		if (gamePads[portNum]->checkConnection())
		{
			return gamePads[portNum];
		}
	}
	return NULL;
}