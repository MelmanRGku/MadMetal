#include "Scene Manager\Scene.h"
#include "Objects\SinglePlayerMenuSystem.h"

class SinglePlayerMenu : public Scene
{
private:
	GamePad * m_gamePad;
	SinglePlayerMenuSystem *menuSystem;

public:
	SinglePlayerMenu(Input * input, Audio *audio);
	~SinglePlayerMenu();
	bool simulateScene(double dt, SceneMessage &newMessage);
};