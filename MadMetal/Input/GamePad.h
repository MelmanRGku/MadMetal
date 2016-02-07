#include <windows.h>
#include <Xinput.h>
#include <cmath>
#ifndef GAMEPAD_H
#define GAMEPAD_H
#define DEADZONE_X 0.05
#define DEADZONE_Y 0.02

struct AnalogStick {
	float x, y;
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

	XINPUT_STATE state;//data struct recturned from xinput of current controller state

	float deadzoneX; //minimum range joysticks must exceed to register activity
	float deadzoneY;
	

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
	static const int StartButton = XINPUT_GAMEPAD_START;
	static const int BackButton = XINPUT_GAMEPAD_BACK;
	static const int LShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER;
	static const int RShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER;


	

	int getID();
	int getPacket();
	bool isOwned();
	void setOwned(bool owned);
	

	bool checkConnection();
	bool sampleState();

	bool isPressed(int gamePadButton);

	AnalogStick getLeftStick();
	AnalogStick getRightStick();

	float getLeftTrigger();
	float getRightTrigger();
};

#endif
