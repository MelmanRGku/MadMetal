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

void GamePad::updateButtonState(ButtonState &state, bool isPressed)
{
	if (isPressed)
	{
		if (state == IDLE || state == RELEASED) state = PRESSED;
		else if (state == PRESSED) state = HELD;
	}
	else {
		if (state == RELEASED) state = IDLE;
		else state = RELEASED;
	}
}

void GamePad::setButtonStates()
{
	//xbutton
	updateButtonState(xState, m_state.Gamepad.wButtons & XButton);

	//ybutton
	updateButtonState(yState, m_state.Gamepad.wButtons & YButton);

	//abutton
	updateButtonState(aState, m_state.Gamepad.wButtons & AButton);

	//bbutton
	updateButtonState(bState, m_state.Gamepad.wButtons & BButton);

	//dpad left
	updateButtonState(dplState, m_state.Gamepad.wButtons & DPadLeft);

	//dpad right button
	updateButtonState(dprState, m_state.Gamepad.wButtons & DPadRight);

	//dpad up button
	updateButtonState(dpuState, m_state.Gamepad.wButtons & DPadUp);

	//dpad down button
	updateButtonState(dpdState, m_state.Gamepad.wButtons & DPadDown);

	//left Shoulder button
	updateButtonState(lsState, m_state.Gamepad.wButtons & LShoulder);

	//right shoulder button
	updateButtonState(rsState, m_state.Gamepad.wButtons & RShoulder);

	//startButton
	updateButtonState(startState, m_state.Gamepad.wButtons & StartButton);


#define JOYSTICK_SENSITIVITY 0.3
	//Left JoyStick Left
	updateButtonState(ljlState, leftStick.x < -JOYSTICK_SENSITIVITY);

	//Left Joystick Right
	updateButtonState(ljrState, leftStick.x > JOYSTICK_SENSITIVITY);

	//Left Joystick Up
	updateButtonState(ljuState, leftStick.y > JOYSTICK_SENSITIVITY);

	//Left Joystick Down
	updateButtonState(ljdState, leftStick.y < -JOYSTICK_SENSITIVITY);

}


bool GamePad::sampleState(double dt)
{
	
	ZeroMemory(&m_state, sizeof(XINPUT_STATE)); //zero memory of state
	
	//return if controller not connected 
	if (XInputGetState(controllerID, &m_state) != ERROR_SUCCESS)
		return false;
		
	currentPacket = m_state.dwPacketNumber;
	setButtonStates();
	
		
	//calculate displacements of left and right joysticks
	float dispX = fmaxf(-1, (float)m_state.Gamepad.sThumbLX / 32767);
	float dispY = fmaxf(-1, (float)m_state.Gamepad.sThumbLY / 32767);
	
	//left joystick
	//is displacement in each direction greater than the deadzone range?
	leftStick.x = abs(dispX) < deadzoneX ? 0 : (abs(dispX) - deadzoneX)
		* (abs(dispX)/dispX);
	leftStick.y = abs(dispY) < deadzoneY ? 0 : (abs(dispY) - deadzoneY)
		* (abs(dispY) / dispY);
	
	dispX = fmaxf(-1, (float)m_state.Gamepad.sThumbRX / 32767);
	dispY = fmaxf(-1, (float)m_state.Gamepad.sThumbRY / 32767);

	//right joystick
	rightStick.x = abs(dispX) < deadzoneX ? 0 : (abs(dispX) - deadzoneX)
		* (abs(dispX) / dispX);

	rightStick.y = abs(dispY) < deadzoneY ? 0 : (abs(dispY) - deadzoneY)
		* (abs(dispY) / dispY);

	//calculate trigger depression
	leftTrigger = (float)m_state.Gamepad.bLeftTrigger / 255;
	rightTrigger = (float)m_state.Gamepad.bRightTrigger / 255;
	
	
	
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
	case (StartButton) :
		return startState == PRESSED;
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
	case (StartButton) :
		return startState == HELD;
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
	case (StartButton) :
		return startState == RELEASED;
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