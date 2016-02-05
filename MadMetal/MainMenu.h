#include "Scene.h"

enum MenuSelection{
	SINGLEPLAYER,
	MULTIPLAYER,
	CREDITS,
	EXIT
};

class MainMenu : public Scene
{
private:
	GamePad * m_gamePad;
	MenuSelection m_currentSelection;



};