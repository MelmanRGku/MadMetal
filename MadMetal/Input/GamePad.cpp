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

void GamePad::setButtonStates()
{
	//xbutton
	if (state.Gamepad.wButtons & XButton)
	{
		if (xState == IDLE) xState = PRESSED;
		else if (xState == PRESSED) xState = HELD;
	}
	else {
		if (xState == RELEASED) xState = IDLE;
		else xState = RELEASED;
	}

	//ybutton
	if (state.Gamepad.wButtons & YButton)
	{
		if (yState == IDLE) yState = PRESSED;
		else if (yState == PRESSED) yState = HELD;
	}
	else {
		if (yState == RELEASED) yState = IDLE;
		else yState = RELEASED;
	}

	//abutton
	if (state.Gamepad.wButtons & AButton)
	{
		if (aState == IDLE) aState = PRESSED;
		else if (aState == PRESSED) aState = HELD;
	}
	else {
		if (aState == RELEASED) aState = IDLE;
		else aState = RELEASED;
	}

	//bbutton
	if (state.Gamepad.wButtons & BButton)
	{
		if (bState == IDLE) bState = PRESSED;
		else if (bState == PRESSED) bState = HELD;
	}
	else {
		if (bState == RELEASED) bState = IDLE;
		else bState = RELEASED;
	}

	
	if (state.Gamepad.wButtons & DPadLeft)
	{
		if (dplState == IDLE)
		{
			
			dplState = PRESSED;
		}
		else if (dplState == PRESSED)
		{
		
			dplState = HELD;
		}
		else {}
		
	} else {
		
		if (dplState == PRESSED || dplState == HELD)
		{
			
			dplState = RELEASED;
		}
		else {
			
			dplState = IDLE;
		}
	}

	//dpad right button
	if (state.Gamepad.wButtons & DPadRight)
	{
		if (dprState == IDLE) dprState = PRESSED;
		else if (dprState == PRESSED) dprState = HELD;
	}
	else if (dprState != IDLE) {
		if (dprState != RELEASED) dprState = RELEASED;
		else dprState = IDLE;
	}

	//dpad up button
	if (state.Gamepad.wButtons & DPadUp)
	{
		if (dpuState == IDLE) dpuState = PRESSED;
		else if (dpuState == PRESSED) dpuState = HELD;
	}
	else {
		if (dpuState != RELEASED) dpuState = RELEASED;
		else dpuState = IDLE;
	}

	//dpad down button
	if (state.Gamepad.wButtons & DPadDown)
	{
		if (dpdState == IDLE) dpdState = PRESSED;
		else if (dpdState == PRESSED) dpdState = HELD;
	}
	else {
		if (dpdState == RELEASED) dpdState = IDLE;
		else dpdState = RELEASED;
	}

	//left Shoulder button
	if (state.Gamepad.wButtons & LShoulder)
	{
		if (lsState == IDLE) lsState = PRESSED;
		else if (lsState == PRESSED) lsState = HELD;
	}
	else {
		if (lsState == RELEASED) lsState = IDLE;
		else lsState = RELEASED;
	}

	//right shoulder button
	if (state.Gamepad.wButtons & RShoulder)
	{
		if (rsState == IDLE) rsState = PRESSED;
		else if (rsState == PRESSED) rsState = HELD;
	}
	else {
		if (rsState == RELEASED) rsState = IDLE;
		else rsState = RELEASED;
	}

	//Left JoyStick Left
	//std::cout << leftStick.x << std::endl;
	if (leftStick.x < -.4)
	{
		
		if (ljlState == IDLE)
		{
			ljlState = PRESSED;
		}
		else {
			ljlState = HELD;
		}
	}
	else {
		if (ljlState == RELEASED)
		{
			ljlState = IDLE;
		}
		else{
			ljlState = RELEASED;
		}
	}

	//Left Joystick Right
	if (leftStick.x > 0.5)
	{
		if (ljrState == IDLE) ljrState = PRESSED;
		else if (ljrState == PRESSED) ljrState = HELD;
	}
	else {
		if (ljrState == RELEASED) ljrState = IDLE;
		else ljrState = RELEASED;
	}

	//Left Joystick Up
	if (leftStick.y > 0)
	{
		if (ljuState == IDLE) ljuState = PRESSED;
		else if (ljuState == PRESSED) ljuState = HELD;
	}
	else {
		if (ljuState == RELEASED) ljuState = IDLE;
		else ljuState = RELEASED;
	}

	//Left Joystick Down
	if (leftStick.y < 0)
	{
		if (ljdState == IDLE) ljdState = PRESSED;
		else if (ljdState == PRESSED) ljdState = HELD;
	}
	else {
		if (ljdState == RELEASED) ljdState = IDLE;
		else ljdState = RELEASED;
	}

	


}


bool GamePad::sampleState(double dt)
{
	
	ZeroMemory(&state, sizeof(XINPUT_STATE)); //zero memory of state
	
	//return if controller not connected 
	if (XInputGetState(controllerID, &state) != ERROR_SUCCESS)
		return false;
		
	currentPacket = state.dwPacketNumber;
	setButtonStates();
	
		
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

int GamePad::getPacket()
{
	return currentPacket;
}

bool GamePad::isPressed(int gamePadButton)
{
	switch (gamePadButton)
	{
	case (AButton) :
		return aState == PRESSED;
	case (BButton) :
		return bState == PRESSED;
	case (XButton) :
		return xState == PRESSED;
	case(YButton) :
		return yState == PRESSED;
	case (DPadLeft) :
		return dplState == PRESSED;
	case (DPadRight) :
		return dprState == PRESSED;
	case (DPadUp) :
		return dpuState == PRESSED;
	case (DPadDown) :
		return dpdState == PRESSED;
	case (LJoyLeft) :
		
		return ljlState == PRESSED;
	case (LJoyRight) :
		return ljrState == PRESSED;
	case (LJoyUp) :
		return ljuState == PRESSED;
	case (LJoyDown) :
		return ljdState == PRESSED;
	default:
		std::cout << "Checking for button not yet assigned \n";
		return false;
	}
}

bool GamePad::isHeld(int gamePadButton)
{
	switch (gamePadButton)
	{
	case (AButton) :
		return aState == HELD;
	case (BButton) :
		return bState == HELD;
	case (XButton) :
		return xState == HELD;
	case(YButton) :
		return yState == HELD;
	case (DPadLeft) :
		return dplState == HELD;
	case (DPadRight) :
		return dprState == HELD;
	case (DPadUp) :
		return dpuState == HELD;
	case (DPadDown) :
		return dpdState == HELD;
	case (LJoyLeft) :
		return ljlState == HELD;
	case (LJoyRight) :
		return ljrState == HELD;
	case (LJoyUp) :
		return ljuState == HELD;
	case (LJoyDown) :
		return ljdState == HELD;
	default:
		std::cout << "Checking for button not yet assigned \n";
		return false;
	}
}

bool GamePad::isReleased(int gamePadButton)
{
	switch (gamePadButton)
	{
	case (AButton) :
		return aState == RELEASED;
	case (BButton) :
		return bState == RELEASED;
	case (XButton) :
		return xState == RELEASED;
	case(YButton) :
		return yState == RELEASED;
	case (DPadLeft) :
		return dplState == RELEASED;
	case (DPadRight) :
		return dprState == RELEASED;
	case (DPadUp) :
		return dpuState == RELEASED;
	case (DPadDown) :
		return dpdState == RELEASED;
	case (LJoyLeft) :
		return ljlState == RELEASED;
	case (LJoyRight) :
		return ljrState == RELEASED;
	case (LJoyUp) :
		return ljuState == RELEASED;
	case (LJoyDown) :
		return ljdState == RELEASED;
	default:
		std::cout << "Checking for button not yet assigned \n";
		return false;
	}
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