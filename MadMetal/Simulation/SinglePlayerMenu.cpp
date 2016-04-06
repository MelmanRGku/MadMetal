#include "SinglePlayerMenu.h"
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
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

SinglePlayerMenu::SinglePlayerMenu(Input * input, Audio *audio)
{
	m_audio = audio;
	m_gamePad = input->getGamePadHandle();
	m_defaultSceneCamera->setLookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -3), glm::vec3(0, 1, 0));

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(-2.35, 1.95, -5.1));
		a->setScale(glm::vec3(.7, .2, 0.00001));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/Back.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		backButton = new Object3D(1, au, p, a, r, NULL);
		m_world->addGameObject(backButton);
	}

	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(0, 3, -25));
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
		a->updatePosition(glm::vec3(0, 3, -25));
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
		a->updatePosition(glm::vec3(-7, -2, -25));
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
		a->updatePosition(glm::vec3(0, -2, -20));
		a->setScale(glm::vec3(4, 3, 6));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/twisted1.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		car2 = new Object3D(4, au, p, a, r, NULL);
		selectedObject = car2;
		selectedCar = car2;
		m_world->addGameObject(car2);
	}



	{
		Physicable *p = new Physicable(NULL);
		Animatable *a = new Animatable();
		a->updatePosition(glm::vec3(7, -2, -25));
		a->setScale(glm::vec3(4, 3, 6));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/Gargantulous.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		car3 = new Object3D(5, au, p, a, r, NULL);
		m_world->addGameObject(car3);
	}

	{
		Renderable3D *renderable = new Renderable3D(NULL);
		Audioable *audioable = new Audioable(*audio);
		Animatable *animatable = new Animatable();
		Physicable *physicable = new Physicable(NULL);

		Text3D *loadingInfoString = new Text3D(3, audioable, physicable, animatable, renderable, 1);
		loadingInfoString->setPosition(glm::vec3(0, 5, -20));
		loadingInfoString->setString("Computer Players");
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

	{
		Animatable *a = new Animatable();
		a->setPosition(glm::vec3(0, -0.80f, 0));
		a->setScale(glm::vec3(0.7f, 0.2f, 0));
		Audioable *au = new Audioable(*audio);
		Model2D *model;
		model = new Model2D(Assets::loadTextureFromDirectory("Assets/Textures/press_a_to_start.png"));
		model->getTexture()->Load();
		Renderable2D *r = new Renderable2D(model);
		aToStart = new TexturedObject2D(1, au, a, r);
		m_world->addGameObject(aToStart);
	}
}

SinglePlayerMenu::~SinglePlayerMenu() {
}

bool SinglePlayerMenu::simulateScene(double dt, SceneMessage &message)
{
	m_sceneGameTimeSeconds += dt;
	m_world->update(dt);
	if (messageToReturn != SceneMessage::eNone) {
		message.setTag(messageToReturn);
		if (message.getTag() == SceneMessage::eLoadScreen) {
			std::vector<ControllableTemplate *> templates;

			Characters carType;
			if (selectedCar == car1)
				carType = Characters::CHARACTER_MEOW_MIX;
			else if (selectedCar == car2)
				carType = Characters::CHARACTER_EXPLOSIVELY_DELICIOUS;
			else if (selectedCar == car3)
				carType = Characters::CHARACTER_GARGANTULOUS;

			templates.push_back(new ControllableTemplate(carType, m_gamePad));

			srand(time(NULL));
			for (int i = 0; i < numberOfAIs; i++) {
				templates.push_back(new ControllableTemplate(rand() % 3));
			}
			message.setPlayerTemplates(templates);
		}
		messageToReturn = SceneMessage::eNone;
		return true;
	}

	//music
	if (m_audio->getMusicFinished()) {
		m_audio->playMusic(CrysisTwoThemeSong(), 1);
	}

	//check gamepad stuff
	if (m_gamePad->checkConnection() && m_sceneGameTimeSeconds>1)
	{

		if (m_gamePad->isPressed(GamePad::DPadUp) || m_gamePad->isPressed(GamePad::LJoyUp)) {
			upPressed();
		} 
		else if (m_gamePad->isPressed(GamePad::DPadDown) || m_gamePad->isPressed(GamePad::LJoyDown)) {
			downPressed();
		} 
		else if (m_gamePad->isPressed(GamePad::AButton)) {
			aPressed();
		}
		else if (m_gamePad->isPressed(GamePad::DPadLeft) || m_gamePad->isPressed(GamePad::LJoyLeft)) {
			leftPressed();
		}
		else if (m_gamePad->isPressed(GamePad::DPadRight) || m_gamePad->isPressed(GamePad::LJoyRight)) {
			rightPressed();
		} 
		else if (m_gamePad->isPressed(GamePad::BButton)) {
			m_audio->queAudioSource(NULL, MenuBackButtonSound());
			message.setTag(SceneMessage::ePop);
			return true;
		}
	}
	return false;
}


void SinglePlayerMenu::upPressed() {
	m_audio->queAudioSource(NULL, MenuButtonChangeSound());
	unselectMenuItem(selectedObject);
	if (selectedObject == backButton) {
		if (selectedCar != NULL)
			selectedObject = selectedCar;
		else
			selectedObject = car2;
		aToStart->setScale(glm::vec3(0.7f, 0.2f, 0));
	}
	else if (selectedObject == numberOfAIsButton) {
		selectedObject = backButton;
	}
	else if (selectedObject == car1 || selectedObject == car2 || selectedObject == car3) {
		selectedObject = numberOfAIsButton;
		aToStart->setScale(glm::vec3(0, 0, 0));
	}
	selectMenuItem(selectedObject);
}

void SinglePlayerMenu::downPressed() {
	m_audio->queAudioSource(NULL, MenuButtonChangeSound());
	unselectMenuItem(selectedObject);
	if (selectedObject == backButton) {
		selectedObject = numberOfAIsButton;
	}
	else if (selectedObject == numberOfAIsButton) {
		if (selectedCar != NULL)
			selectedObject = selectedCar;
		else
			selectedObject = car2;
		aToStart->setScale(glm::vec3(0.7f, 0.2f, 0));
	}
	else if (selectedObject == car1 || selectedObject == car2 || selectedObject == car3) {
		selectedObject = backButton;
		aToStart->setScale(glm::vec3(0, 0, 0));
	}
	selectMenuItem(selectedObject);
}

void SinglePlayerMenu::leftPressed() {
	unselectMenuItem(selectedObject);
	if (selectedObject == car1) {
		m_audio->queAudioSource(NULL, MenuButtonChangeSound());
		selectedObject = car3;
		selectedCar = car3;
	}
	else if (selectedObject == car2) {
		m_audio->queAudioSource(NULL, MenuButtonChangeSound());
		selectedObject = car1;
		selectedCar = car1;
	}
	else if (selectedObject == car3) {
		m_audio->queAudioSource(NULL, MenuButtonChangeSound());
		selectedObject = car2;
		selectedCar = car2;
	}
	else if (selectedObject == numberOfAIsButton) {
		m_audio->queAudioSource(NULL, MenuButtonNextPrevSound());
		numberOfAIs--;
		if (numberOfAIs < 0)
			numberOfAIs = 0;
		std::stringstream s;
		s << numberOfAIs;
		numberOfAIsString->setString(s.str());
	}
	selectMenuItem(selectedObject);
}

void SinglePlayerMenu::rightPressed() {
	unselectMenuItem(selectedObject);
	if (selectedObject == car1) {
		m_audio->queAudioSource(NULL, MenuButtonChangeSound());
		selectedObject = car2;
		selectedCar = car2;
	}
	else if (selectedObject == car2) {
		m_audio->queAudioSource(NULL, MenuButtonChangeSound());
		selectedObject = car3;
		selectedCar = car3;
	}
	else if (selectedObject == car3) {
		m_audio->queAudioSource(NULL, MenuButtonChangeSound());
		selectedObject = car1;
		selectedCar = car1;
	}
	else if (selectedObject == numberOfAIsButton) {
		m_audio->queAudioSource(NULL, MenuButtonNextPrevSound());
		numberOfAIs++;
		if (numberOfAIs > MAX_NUM_OF_AIS - 1)
			numberOfAIs = MAX_NUM_OF_AIS - 1;
		std::stringstream s;
		s << numberOfAIs;
		numberOfAIsString->setString(s.str());
	}
	selectMenuItem(selectedObject);
}

void SinglePlayerMenu::aPressed() {
	if (selectedObject == backButton) {
		messageToReturn = SceneMessage::ePop;
		m_audio->queAudioSource(NULL, MenuBackButtonSound());
	}
	else if (selectedObject == car1 || selectedObject == car2 || selectedObject == car3) {
		m_audio->queAudioSource(NULL, MenuButtonClickSound());
		m_audio->stopMusic();
		messageToReturn = SceneMessage::eLoadScreen;
	}
}

void SinglePlayerMenu::selectMenuItem(Object3D *menuItem) {
	glm::vec3 offset = glm::vec3(0, 0, 5);
	if (menuItem == backButton) {
		offset = glm::vec3(0, 0, .1f);
	}
	{
		ObjectPositionUpdater *upd = new ObjectPositionUpdater(menuItem, offset, .5);
		m_world->addObjectUpdater(upd);
	}

	if (menuItem == numberOfAIsButton) {
		{
			ObjectPositionUpdater *upd = new ObjectPositionUpdater(numberOfAIsString, offset, .5);
			m_world->addObjectUpdater(upd);
		}
	}
}

void SinglePlayerMenu::unselectMenuItem(Object3D *menuItem) {
	glm::vec3 offset = glm::vec3(0, 0, -5);
	if (menuItem == backButton) {
		offset = glm::vec3(0, 0, -.1f);
	}
	{
		ObjectPositionUpdater *upd = new ObjectPositionUpdater(menuItem, offset, .5);
		m_world->addObjectUpdater(upd);
	}
	if (menuItem == numberOfAIsButton) {
		{
			ObjectPositionUpdater *upd = new ObjectPositionUpdater(numberOfAIsString, offset, .5);
			m_world->addObjectUpdater(upd);
		}
	}
}
