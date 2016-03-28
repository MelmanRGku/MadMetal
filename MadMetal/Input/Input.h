#pragma once
#include "GamePad.h"
#include "../Global/Log.h"
#include <iostream>
#include <vector>
class Input
{
private:
	GamePad * gamePads[4];

public:
	Input();
	~Input();

	void updateGamePads(double dt);
	bool getGamePadHandle(int portNumber, GamePad** handle);
	GamePad * getGamePadHandle();
	std::vector<GamePad *> getAllGamePads();
	void releaseGamePadHandle(int portNumber, GamePad* handle);
};