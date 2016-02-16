#include "LoadingScreen.h"


LoadingScreen::LoadingScreen(PlayerControllable *pc)
{

	status = new LoadingStatus();
	Assets::status = status;
	Assets::loadObjsFromDirectory( "Assets/Models", true );
	this->pc = pc;
	//t.join();
}


LoadingScreen::~LoadingScreen()
{
}


bool LoadingScreen::simulateScene(double dt, SceneMessage &newMessage) {
	/*std::cout << status->getMessage() << " " << status->getPercentage() << std::endl;
	if (status->getPercentage() >= 1)
		t.join();*/
	newMessage.setTag(NORMAL_GAME);
	newMessage.addPlayer(pc);
	return true;
}