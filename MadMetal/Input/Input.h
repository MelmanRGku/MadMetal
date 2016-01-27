#include "GamePad.h"
#include "../Global/Log.h"
#include <iostream>

class Input
{
private:
	GamePad * gamePads[4];

public:
	Input();

	void updateGamePads();
	bool getGamePadHandle(int portNumber, GamePad** handle);
	void releaseGamePadHandle(int portNumber, GamePad** handle);
};