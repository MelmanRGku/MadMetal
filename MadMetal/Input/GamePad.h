#include <windows.h>
#include <Xinput.h>
#include <cmath>
#ifndef GAMEPAD_H
#define GAMEPAD_H
#define DEADZONE_X 0.2
#define DEADZONE_Y 0.2
#define UPDATE_DELAY 0.002

struct AnalogStick {
	float x, y;
};

enum ButtonState
{
	IDLE,
	PRESSED,
	HELD,
	RELEASED
};

class GamePad
{
private:
	int controllerID; //0-3 based on port location
	bool connected;
	bool owned;
	AnalogStick leftStick,
		rightStick;
	float leftTrigger;
	float rightTrigger;
	int currentPacket;
	double updateAccumulator;

	XINPUT_STATE state;//data struct recturned from xinput of current controller state

	float deadzoneX; //minimum range joysticks must exceed to register activity
	float deadzoneY;

	//button states
	ButtonState xState;
	ButtonState bState;
	ButtonState aState;
	ButtonState yState;
	ButtonState dprState;
	ButtonState dplState;
	ButtonState dpuState;
	ButtonState dpdState;
	ButtonState lsState;
	ButtonState rsState;
	ButtonState ljuState;
	ButtonState ljdState;
	ButtonState ljlState;
	ButtonState ljrState;

	

public:
	GamePad() : deadzoneX(DEADZONE_X), deadzoneY(DEADZONE_Y), controllerID(-1) 
	{
		owned = false;
	}
	GamePad(int cID) : deadzoneX(DEADZONE_X), deadzoneY(DEADZONE_Y), controllerID(cID) 
	{
		owned = false;
	}

	~GamePad(){}

	static const int XButton = XINPUT_GAMEPAD_X;
	static const int YButton = XINPUT_GAMEPAD_Y;
	static const int AButton = XINPUT_GAMEPAD_A;
	static const int BButton = XINPUT_GAMEPAD_B;
	static const int DPadRight = XINPUT_GAMEPAD_DPAD_RIGHT;
	static const int DPadLeft = XINPUT_GAMEPAD_DPAD_LEFT;
	static const int DPadUp = XINPUT_GAMEPAD_DPAD_UP;
	static const int DPadDown = XINPUT_GAMEPAD_DPAD_DOWN;
	static const int StartButton = XINPUT_GAMEPAD_START;
	static const int BackButton = XINPUT_GAMEPAD_BACK;
	static const int LShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER;
	static const int RShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER;
	static const int LJoyLeft = 0x8001;
	static const int LJoyRight = 0x8002;
	static const int LJoyUp = 0x8003;
	static const int LJoyDown = 0x8004;


	

	int getID();
	int getPacket();
	bool isOwned();
	void setOwned(bool owned);
	

	bool checkConnection();
	bool sampleState(double dt);


	void setButtonStates();
	bool isPressed(int gamePadButton);
	bool isHeld(int gamePadButton);
	bool isReleased(int gamePadButton);

	AnalogStick getLeftStick();
	AnalogStick getRightStick();

	float getLeftTrigger();
	float getRightTrigger();
};

#endif
