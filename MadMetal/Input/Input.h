#include <iostream>
#include <vector>

class controllerState{};

class GamePad
{
private:
	controllerState state;
public:
	void update()
	{
		std::cout << "Controller state sampled \n";
	}

};

class Input
{
private:
	GamePad gamePads[4];
public:
	void update()
	{
		std::cout << "Updating Controllers.... \n";
		for (int i = 0; i < 4; i++)
		{
			gamePads[i].update();
		}
	}
	void getController(GamePad &gamePad);

};