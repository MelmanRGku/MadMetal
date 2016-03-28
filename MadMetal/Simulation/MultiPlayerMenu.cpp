#include "MultiPlayerMenu.h"
#include "Objects\Text3D.h"
#include "Global\Assets.h"
#include "Objects\Cars\MeowMix.h"
#include "Objects\ObjectUpdaters\ObjectPositionUpdater.h"
#include "Objects\ObjectUpdaters\ObjectRotationUpdater.h"
#include "Objects\ObjectUpdaters\ObjectScaleUpdater.h"
#include "Objects\ObjectUpdaters\ObjectUpdaterSequence.h"
#include "Objects\ObjectUpdaters\ObjectUpdaterParallel.h"
#include "Settings.h"
#include <sstream>

PlayerSelection::PlayerSelection(GamePad *gamePad, Audio *audio, World *world) {
	m_gamePad = gamePad;
	m_world = world;
	m_audio = audio;
	tempSelection = CHARACTER_MEOW_MIX;

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->setScale(glm::vec3(0, 0, 0));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/Meowmix.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		selectedCar = new Object3D(2, au, p, a, r, NULL);
		world->addGameObject(selectedCar);
	}

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->setScale(glm::vec3(0, 0, 0));
		Audioable *au = new Audioable(*m_audio);
		Model3D *model;
		model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/Player1.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		selectionIndicator = new Object3D(1, au, p, a, r, NULL);
		m_world->addGameObject(selectionIndicator);
	}


	/*
	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(0, -0.8, 0));
		a->setScale(glm::vec3(0.8, 0.2, 0.1));
		Audioable *au = new Audioable(*audio);
		Model2D *model = new Model2D(Assets::loadTextureFromDirectory("Assets/Textures/JoinQuit.png"));
		Renderable2D *r = new Renderable2D(model);
		joinquit = new TexturedObject2D(3, au, a, r);
		m_world->addGameObject(joinquit);
	}
	*/
	{
		Renderable3D *renderable = new Renderable3D(NULL);
		Audioable *audioable = new Audioable(*audio);
		Animatable *animatable = new Animatable();
		Physicable *physicable = new Physicable(NULL);

		Text3D *loadingInfoString = new Text3D(3, audioable, physicable, animatable, renderable, 1);
		loadingInfoString->setPosition(glm::vec3(0, -7, -20));
		loadingInfoString->setString("A to join        B to quit");
		m_world->addGameObject(loadingInfoString);
	}

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(0, 0, -30));
		a->setScale(glm::vec3(33, 24.5, 1));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/Background.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		background = new Object3D(3, au, p, a, r, NULL);
		m_world->addGameObject(background);
	}
}

void PlayerSelection::joinGame(int position, glm::vec3 selectionIndicatorInitialPosition, glm::vec3 carPosition) {
	assignedPosition = position;
	selectedCarPosition = carPosition;
	playerTemplate = new ControllableTemplate(m_gamePad);
	this->selectionIndicatorInitialPosition = selectionIndicatorInitialPosition;

	selectionIndicator->setPosition(glm::vec3(selectionIndicatorInitialPosition + (float)tempSelection * selectionIndicatorOffset));
	selectionIndicator->setScale(glm::vec3(1.5, 1.5, 0.000000001f));
	Model3D *model;
	if (position == 1)
		model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/Player1.obj"));
	else if (position == 2)
		model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/Player2.obj"));
	else if (position == 3)
		model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/Player3.obj"));
	else
		model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/Player4.obj"));
	model->setupVAOs();
	Renderable3D *renderable = static_cast<Renderable3D*>(selectionIndicator->getRenderable());
	renderable->setModel(model);
	renderable->adjustModel(true, true);

}

bool PlayerSelection::joinedGame() {
	return playerTemplate != NULL;
}

void PlayerSelection::unjoinGame() {
	selectionIndicator->setScale(glm::vec3(0, 0, 0));
	assignedPosition = -1;
	delete playerTemplate;
	playerTemplate = NULL;
}

void PlayerSelection::selectCar() {
	playerTemplate->setCarSelection(tempSelection);
	selectedCar->setPosition(selectedCarPosition);
	selectedCar->setScale(glm::vec3(.8, .8, .2));

	Model3D *model = NULL;

	if (tempSelection == Characters::CHARACTER_MEOW_MIX)
		model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/Meowmix.obj"));
	else if (tempSelection == Characters::CHARACTER_EXPLOSIVELY_DELICIOUS)
		model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/twisted1.obj"));
	else if (tempSelection == Characters::CHARACTER_GARGANTULOUS)
		model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/Gargantulous.obj"));

	model->setupVAOs();
	Renderable3D *renderable = static_cast<Renderable3D*>(selectedCar->getRenderable());
	renderable->setModel(model);
	renderable->adjustModel(true, true);

	selectionIndicator->setScale(glm::vec3(0, 0, 0));
}

void PlayerSelection::unselectCar() {
	playerTemplate->setCarSelection(-1);
	selectedCar->setScale(glm::vec3(0, 0, 0));
	selectionIndicator->setScale(glm::vec3(1.5, 1.5, 0.000000001f));
}

bool PlayerSelection::carSelected() {
	return joinedGame() && playerTemplate->carSelected();
}

void PlayerSelection::selectNextCar() {
	if (tempSelection != CHARACTER_GARGANTULOUS) {
		tempSelection = (Characters)((int)tempSelection + 1);
		selectionIndicator->updatePosition(selectionIndicatorOffset);
	}
}


void PlayerSelection::selectPrevCar() {
	if (tempSelection != CHARACTER_MEOW_MIX) {
		tempSelection = (Characters)((int)tempSelection - 1);
		selectionIndicator->updatePosition(-selectionIndicatorOffset);
	}
}

ControllableTemplate *PlayerSelection::getControllableTemplate() {
	return playerTemplate;
}

GamePad *PlayerSelection::getGamePad() {
	return m_gamePad;
}

int PlayerSelection::getAssignedPosition() {
	return assignedPosition;
}


MultiPlayerMenu::MultiPlayerMenu(Input * input, Audio *audio)
{
	m_gamePads = input->getAllGamePads();
	m_defaultSceneCamera->setLookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -3), glm::vec3(0, 1, 0));

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(-2.2, 1.5, -5.));
		a->setScale(glm::vec3(1, 1, 0.001));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/LoadingBox.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		playerBoxes.push_back(new Object3D(2, au, p, a, r, NULL));
		m_world->addGameObject(playerBoxes.at(0));
	}

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(2.2, 1.5, -5.));
		a->setScale(glm::vec3(1, 1, 0.001));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/LoadingBox.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		playerBoxes.push_back(new Object3D(2, au, p, a, r, NULL));
		m_world->addGameObject(playerBoxes.at(1));
	}

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(-2.2, -1.5, -5.));
		a->setScale(glm::vec3(1, 1, 0.001));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/LoadingBox.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		playerBoxes.push_back(new Object3D(2, au, p, a, r, NULL));
		m_world->addGameObject(playerBoxes.at(2));
	}

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(2.2, -1.5, -5.));
		a->setScale(glm::vec3(1, 1, 0.001));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/LoadingBox.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		playerBoxes.push_back(new Object3D(2, au, p, a, r, NULL));
		m_world->addGameObject(playerBoxes.at(3));
	}

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(0, -5, -25));
		a->setScale(glm::vec3(5, 1, 1));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/Arrows.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		numberOfAIsButton = new Object3D(2, au, p, a, r, NULL);
		m_world->addGameObject(numberOfAIsButton);
	}

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(0, -5, -25));
		a->setScale(glm::vec3(5, 1, 1));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/loadingBox.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		numberOfAIsString = new Text3D(2, au, p, a, r, 3);
		numberOfAIsString->setString("4");
		m_world->addGameObject(numberOfAIsString);
	}

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(-7, -1, -25));
		a->setScale(glm::vec3(4, 3, 6));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/Meowmix.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		car1 = new Object3D(3, au, p, a, r, NULL);
		m_world->addGameObject(car1);
	}



	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(0, -1, -25));
		a->setScale(glm::vec3(4, 3, 6));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/twisted1.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		car2 = new Object3D(4, au, p, a, r, NULL);
		m_world->addGameObject(car2);
	}



	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(7, -1, -25));
		a->setScale(glm::vec3(4, 3, 6));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/Gargantulous.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		car3 = new Object3D(5, au, p, a, r, NULL);
		m_world->addGameObject(car3);
	}

	for (int i = 0; i < m_gamePads.size(); i++) {
		m_players.push_back(new PlayerSelection(m_gamePads.at(i), audio, m_world));
	}
}


MultiPlayerMenu::~MultiPlayerMenu()
{
	for (PlayerSelection *ps : m_players) {
		delete ps;
	}
}

bool MultiPlayerMenu::simulateScene(double dt, SceneMessage &message) {
	m_sceneGameTimeSeconds += dt;
	m_world->update(dt);
	if (messageToReturn != SceneMessage::eNone) {
		message.setTag(messageToReturn);
		std::vector<ControllableTemplate *> templates;
		for (int i = 0; i < m_players.size(); i++) {
			if (m_players.at(i)->joinedGame()) {
				templates.push_back(m_players.at(i)->getControllableTemplate());
			}
		}
		for (int i = 0; i < numberOfAIs; i++) {
			templates.push_back(new ControllableTemplate(1));
		}
		message.setPlayerTemplates(templates);
		messageToReturn = SceneMessage::eNone;
		return true;
	}

	//calculate number of players who joined the game
	int numOfPlayersWhoJoinedTheGame = 0;
	for (PlayerSelection *ps : m_players) {
		if (ps->joinedGame())
			numOfPlayersWhoJoinedTheGame++;
	}

	//if none joined and someone pressed B - go to main menu
	if (numOfPlayersWhoJoinedTheGame == 0) {
		for (int i = 0; i < m_gamePads.size(); i++) {
			if (m_gamePads.at(i)->isPressed(GamePad::BButton)) {
				messageToReturn = SceneMessage::ePop;
			}
		}
	}

	//check the number of players who have selected the cars
	int numOfPlayersWhoSelectedTheCar = 0;
	for (int i = 0; i < m_players.size(); i++) {
		if (m_players.at(i)->carSelected())
			numOfPlayersWhoSelectedTheCar++;
	}

	//if everyone has selected the car, choose the number of AI's and go into the game
	if (numOfPlayersWhoJoinedTheGame == numOfPlayersWhoSelectedTheCar && numOfPlayersWhoJoinedTheGame != 0) {
		//check the inpur for all players who have joined the game
		for (PlayerSelection *ps : m_players) {
			if (!ps->joinedGame())
				continue;

			//left press indicates that the number of AI's should be decreased
			if (ps->getGamePad()->isPressed(GamePad::DPadLeft)) {
				numberOfAIs--;
				if (numberOfAIs < 1)
					numberOfAIs = 1;
				std::stringstream s;
				s << numberOfAIs;
				numberOfAIsString->setString(s.str());
			}

			//right press indicates that the number of AI's should be increased
			if (ps->getGamePad()->isPressed(GamePad::DPadRight)) {
				numberOfAIs++;
				if (numberOfAIs > MAX_NUM_OF_AIS)
					numberOfAIs = MAX_NUM_OF_AIS;
				std::stringstream s;
				s << numberOfAIs;
				numberOfAIsString->setString(s.str());
			}

			//a button press indicates that the game should be started
			if (ps->getGamePad()->isPressed(GamePad::AButton)) {
				messageToReturn = SceneMessage::eLoadScreen;
			}
		}
	}

	//parse the input from players who have joined the game
	for (PlayerSelection *ps : m_players) {
		
		//discard players who haven't joined the game yet
		if (!ps->joinedGame())
			continue;

		//right click when the car hasn't been selected means to go to the next car
		if (ps->getGamePad()->isPressed(GamePad::DPadRight) && !ps->carSelected()) {
			ps->selectNextCar();
		}

		//left click when the car hasn't been selected means to go to the previous car
		if (ps->getGamePad()->isPressed(GamePad::DPadLeft) && !ps->carSelected()) {
			ps->selectPrevCar();
		}

		//a button click when the car hasn't been selected means that the player wants to select the car
		if (ps->getGamePad()->isPressed(GamePad::AButton) && !ps->carSelected()) {
			ps->selectCar();
		}

		if (ps->getGamePad()->isPressed(GamePad::BButton)) {
			//b button click when the car has been selected means that the player wants to unselect it
			if (ps->carSelected()) {
				ps->unselectCar();
			}
			//b button click when the car hasn't been selected means that the player wants to unjoin the game
			else {
				ps->unjoinGame();
			}
		}
	}

	//let the new players join the game
	for (PlayerSelection *ps : m_players) {
		//if the player has already joined the game - we have nothing to do here
		if (ps->joinedGame())
			continue;

		//a button press means that the player wants to join the game
		if (ps->getGamePad()->isPressed(GamePad::AButton)) {
			//here we have to calculate what position does the player get
			bool positionsTaken[] = { false, false, false, false };

			for (PlayerSelection *ps2 : m_players) {
				if (ps2->joinedGame())
					positionsTaken[ps2->getAssignedPosition() - 1] = true;
			}
			int positionToAssign = -1;
			for (int i = 0; i < 4; i++) {
				if (!positionsTaken[i]) {
					positionToAssign = i + 1;
					break;
				}
			}

			//now get the apropriate player indicator position
			glm::vec3 playerIndicatorInitialPosition = car1->getAnimatablePos();
			glm::vec3 xOffset = glm::vec3(2.5, 0, 0);
			glm::vec3 yOffset = glm::vec3(0, 2.5, 0);
			if (positionToAssign == 1)
				playerIndicatorInitialPosition = playerIndicatorInitialPosition - xOffset + yOffset;
			else if (positionToAssign == 2)
				playerIndicatorInitialPosition = playerIndicatorInitialPosition + xOffset + yOffset;
			else if (positionToAssign == 3)
				playerIndicatorInitialPosition = playerIndicatorInitialPosition - xOffset - yOffset;
			else if (positionToAssign == 4)
				playerIndicatorInitialPosition = playerIndicatorInitialPosition + xOffset - yOffset;

			ps->joinGame(positionToAssign, playerIndicatorInitialPosition, playerBoxes.at(positionToAssign - 1)->getAnimatablePos());
		}
	}

	return false;
}