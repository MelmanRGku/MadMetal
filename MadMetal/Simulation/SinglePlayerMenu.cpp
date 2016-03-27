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

SinglePlayerMenu::SinglePlayerMenu(Input * input, Audio *audio)
{
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
		a->updatePosition(glm::vec3(-7, -2, -35));
		a->setScale(glm::vec3(5, 4, 7));
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
		a->updatePosition(glm::vec3(0, -2, -25));
		a->setScale(glm::vec3(5, 4, 7));
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
		a->updatePosition(glm::vec3(7, -2, -35));
		a->setScale(glm::vec3(5, 4, 7));
		Audioable *au = new Audioable(*audio);
		Model3D *model = static_cast<Model3D *>(Assets::loadObjFromDirectory("Assets/Models/Gargantulous.obj"));
		model->setupVAOs();
		Renderable3D *r = new Renderable3D(model, true, true);
		car3 = new Object3D(5, au, p, a, r, NULL);
		m_world->addGameObject(car3);
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
			for (int i = 0; i < numberOfAIs; i++) {
				templates.push_back(new ControllableTemplate(1));
			}
			message.setPlayerTemplates(templates);
		}
		messageToReturn = SceneMessage::eNone;
		return true;
	}
	//check gamepad stuff
	if (m_gamePad->checkConnection() && m_sceneGameTimeSeconds>1)
	{

		if (m_gamePad->isPressed(GamePad::DPadUp)) {
			upPressed();
		}

		if (m_gamePad->isPressed(GamePad::DPadDown)) {
			downPressed();
		}

		if (m_gamePad->isPressed(GamePad::AButton)) {
			aPressed();
		}

		if (m_gamePad->isPressed(GamePad::DPadLeft)) {
			leftPressed();
		}

		if (m_gamePad->isPressed(GamePad::DPadRight)) {
			rightPressed();
		}

		if (m_gamePad->isPressed(GamePad::BButton)) {
			message.setTag(SceneMessage::ePop);
			return true;
		}
	}
	return false;
}


void SinglePlayerMenu::upPressed() {
	unselectMenuItem(selectedObject);
	if (selectedObject == backButton) {
		if (selectedCar != NULL)
			selectedObject = selectedCar;
		else
			selectedObject = car2;
	}
	else if (selectedObject == numberOfAIsButton) {
		selectedObject = backButton;
	}
	else if (selectedObject == car1 || selectedObject == car2 || selectedObject == car3) {
		selectedObject = numberOfAIsButton;
	}
	selectMenuItem(selectedObject);
}

void SinglePlayerMenu::downPressed() {
	unselectMenuItem(selectedObject);
	if (selectedObject == backButton) {
		selectedObject = numberOfAIsButton;
	}
	else if (selectedObject == numberOfAIsButton) {
		if (selectedCar != NULL)
			selectedObject = selectedCar;
		else
			selectedObject = car2;
	}
	else if (selectedObject == car1 || selectedObject == car2 || selectedObject == car3) {
		selectedObject = backButton;
	}
	selectMenuItem(selectedObject);
}

void SinglePlayerMenu::leftPressed() {
	unselectMenuItem(selectedObject);
	if (selectedObject == car1) {
		selectedObject = car3;
		selectedCar = car3;
	}
	else if (selectedObject == car2) {
		selectedObject = car1;
		selectedCar = car1;
	}
	else if (selectedObject == car3) {
		selectedObject = car2;
		selectedCar = car2;
	}
	else if (selectedObject == numberOfAIsButton) {
		numberOfAIs--;
		if (numberOfAIs < 1)
			numberOfAIs = 1;
		std::stringstream s;
		s << numberOfAIs;
		numberOfAIsString->setString(s.str());
	}
	selectMenuItem(selectedObject);
}

void SinglePlayerMenu::rightPressed() {
	unselectMenuItem(selectedObject);
	if (selectedObject == car1) {
		selectedObject = car2;
		selectedCar = car2;
	}
	else if (selectedObject == car2) {
		selectedObject = car3;
		selectedCar = car3;
	}
	else if (selectedObject == car3) {
		selectedObject = car1;
		selectedCar = car1;
	}
	else if (selectedObject == numberOfAIsButton) {
		numberOfAIs++;
		if (numberOfAIs > MAX_NUM_OF_AIS)
			numberOfAIs = MAX_NUM_OF_AIS;
		std::stringstream s;
		s << numberOfAIs;
		numberOfAIsString->setString(s.str());
	}
	selectMenuItem(selectedObject);
}

void SinglePlayerMenu::aPressed() {
	if (selectedObject == backButton) {
		messageToReturn = SceneMessage::ePop;
	}
	else if (selectedObject == car1 || selectedObject == car2 || selectedObject == car3) {
		messageToReturn = SceneMessage::eLoadScreen;
	}
}

void SinglePlayerMenu::selectMenuItem(Object3D *menuItem) {
	glm::vec3 offset = glm::vec3(0, 0, 10);
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
	glm::vec3 offset = glm::vec3(0, 0, -10);
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
