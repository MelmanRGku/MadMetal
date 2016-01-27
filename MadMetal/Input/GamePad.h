#include <windows.h>
#include <Xinput.h>
#include <cmath>

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

	const int XButton = XINPUT_GAMEPAD_X;
	const int YButton = XINPUT_GAMEPAD_Y;
	const int AButton = XINPUT_GAMEPAD_A;
	const int BButton = XINPUT_GAMEPAD_B;
	const int StartButton = XINPUT_GAMEPAD_START;
	const int BackButton = XINPUT_GAMEPAD_BACK;
	const int LShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER;
	const int RShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER;

	int currentPacket = 0;
	

	int getID();
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

