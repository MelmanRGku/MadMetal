#pragma once
#include "GamePad.h"
#include "../Global/Log.h"
#include <iostream>
#ifndef INPUT_H
#define INPUT_H
class Input
{
private:
	GamePad * gamePads[4];

public:
	Input();

	void updateGamePads(double dt);
	bool getGamePadHandle(int portNumber, GamePad* handle);
	GamePad * getGamePadHandle();
	void releaseGamePadHandle(int portNumber, GamePad* handle);
};

#endif