#include "Scene Manager\Scene.h"
#include "Objects\Text3D.h"

class SinglePlayerMenu : public Scene
{
private:
	GamePad * m_gamePad;
	Object3D *backButton,
		*car1,
		*car2,
		*car3,
		*numberOfAIsButton,
		*selectedObject,
		*selectedCar;
	Text3D *numberOfAIsString;
	SceneMessage::SceneEnum messageToReturn = SceneMessage::eNone;
	int numberOfAIs = 4;

public:
	SinglePlayerMenu(Input * input, Audio *audio);
	~SinglePlayerMenu();
	bool simulateScene(double dt, SceneMessage &newMessage);
	void upPressed();
	void downPressed();
	void leftPressed();
	void rightPressed();
	void aPressed();
	void selectMenuItem(Object3D *menuItem);
	void unselectMenuItem(Object3D *menuItem);
};