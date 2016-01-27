#include "GamePad.h"
#include <iostream>

int GamePad::getID()
{
	return controllerID;
}

bool GamePad::checkConnection()
{
	XINPUT_STATE tempState;
	//ERROR_SUCCESSS flag is returned when get state succeeds. 
	if (XInputGetState(controllerID, &tempState) == ERROR_SUCCESS)
		return connected = true;
	return connected = false;
}

bool GamePad::sampleState()
{
	
	ZeroMemory(&state, sizeof(XINPUT_STATE)); //zero memory of state
	
	//return if controller not connected 
	if (XInputGetState(controllerID, &state) != ERROR_SUCCESS)
		return false;
	
	//return if state is still current
	//if (state.dwPacketNumber == currentPacket)
	//	return true;

	
	currentPacket = state.dwPacketNumber;
	
	//calculate displacements of left and right joysticks
	float dispX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
	float dispY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);
	
	//left joystick
	//is displacement in each direction greater than the deadzone range?
	leftStick.x = abs(dispX) < deadzoneX ? 0 : (abs(dispX) - deadzoneX)
		* (dispX / (abs(dispX) * (1 - deadzoneX)));
		
	leftStick.y = abs(dispY) < deadzoneY ? 0 : (abs(dispY) - deadzoneY)
		* (dispY / (abs(dispY) * (1 - deadzoneY)));
	
	dispX = fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);
	dispY = fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);

	//right joystick
	rightStick.x = abs(dispX) < deadzoneX ? 0 : (abs(dispX) - deadzoneX)
		* (dispX / (abs(dispX) * (1 - deadzoneX)));

	rightStick.y = abs(dispY) < deadzoneY ? 0 : (abs(dispY) - deadzoneY)
		* (dispY / (abs(dispY) * (1 - deadzoneY)));

	//calculate trigger depression
	leftTrigger = (float)state.Gamepad.bLeftTrigger / 255;
	rightTrigger = (float)state.Gamepad.bRightTrigger / 255;
	
	return true;
	
}

bool GamePad::isPressed(int gamePadButton)
{
	
	return (gamePadButton & state.Gamepad.wButtons);
}

AnalogStick GamePad::getLeftStick()
{
	return leftStick;
}

AnalogStick GamePad::getRightStick()
{
	return rightStick;
}

float GamePad::getLeftTrigger()
{
	return leftTrigger;
}

float GamePad::getRightTrigger()
{
	return rightTrigger;
}

bool GamePad::isOwned()
{
	return owned;
}

void GamePad::setOwned(bool isOwned)
{
	
	owned = isOwned;
}