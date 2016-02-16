#include "LoadingScreen.h"


LoadingScreen::LoadingScreen(PlayerControllable *pc)
{

	status = new LoadingStatus();
	Assets::status = status;
	t = std::thread(Assets::loadObjsFromDirectory, "Assets/Models", false );
	this->pc = pc;
}


LoadingScreen::~LoadingScreen()
{
}


bool LoadingScreen::simulateScene(double dt, SceneMessage &newMessage) {
//	std::cout << status->getMessage() << " " << status->getPercentage() << std::endl;
	if (status->getPercentage() >= 1){
		t.join();

		Assets::initializeVAOs();

		newMessage.setTag(NORMAL_GAME);
		newMessage.addPlayer(pc);
		return true;
	}
	return false;
}