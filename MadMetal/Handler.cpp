#include "Libraries\glew\glew.h"
#include "Libraries\glut\glut.h"
#include "Renderer\ShaderProgram.h"
#include "Renderer\Renderer.h"
#include "Objects\ObjModel.h"
#include "Global\Settings.h"
#include "Global\Log.h"
#include "Input\Input.h"
#include "Simulation\GameSimulation.h"
#include "Simulation\Scene.h"
#include <iostream>
#include <windows.h>

Renderer *renderer;
Input *input;
std::vector<Scene *> *scenes;
Audio *audio = new Audio();
GamePad *gamePad = new GamePad();
float lastDrawCallTime = 0;
/*int waitCounter = 0;
int packet = 0;
DummyPosition * position = new DummyPosition(0, 1);*/

/*void updateSound() {

	input->updateGamePads();
	if (packet != gamePad->currentPacket){
		packet = gamePad->currentPacket;
		if (gamePad->isPressed(gamePad->AButton))
			audio->queStaticSource(0);
		if (gamePad->isPressed(gamePad->BButton))
			audio->quePositionalSource(&position);

		if (gamePad->isPressed(gamePad->XButton))
			audio->pauseSources();
		if (gamePad->isPressed(gamePad->YButton))
			audio->resumeSources();
		if (gamePad->isPressed(gamePad->LShoulder))
			audio->stopSources();
		if (gamePad->isPressed(gamePad->RShoulder))

			if (gamePad->isPressed(gamePad->StartButton))

				if (gamePad->isPressed(gamePad->BackButton))
				{
					std::cout << "back button pressed \n";
					input->releaseGamePadHandle(gamePad->getID(), &gamePad);
				}

	}
	position->setPosition(gamePad->getLeftStick().x, gamePad->getLeftStick().y);
	audio->update();
}*/

void initStatics() {
	//load settings from a file
	Settings::loadSettingsFromFile("settings.txt");
	//initialize the debug (log)
	Log::init("debug.txt");
	//enable\disable logging based on the setting
	Log::enableLogging(std::stoi(Settings::getSetting("debugEnabled")) == 0 ? false : true);
}

void initObjects() {
	scenes = new std::vector<Scene *>();
	input = new Input();
	Scene *simulation = new GameSimulation();
	simulation->initialize();
	scenes->push_back(simulation);

	//create a renderer and give it the shader program
	renderer = new Renderer();
	ShaderProgram *sp = new ShaderProgram("Renderer/VertexShader.glsl", "Renderer/FragmentShader.glsl");
	renderer->setShader(sp);
}

void renderScene(void)
{
	float currentDrawCallTime = (float)glutGet(GLUT_ELAPSED_TIME);
	float dt = currentDrawCallTime - lastDrawCallTime;
	lastDrawCallTime = currentDrawCallTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.3, 0.3, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	input->updateGamePads();
	for (unsigned int i = 0; i < scenes->size(); i++) {
		Scene *simulation = scenes->at(i);
		simulation->simulate(dt);
		renderer->draw(simulation->getGameWorld()->getGameObjects());
	}

	glutSwapBuffers();

	glutPostRedisplay();
}

void initOpengl(int argc, char **argv) {
	//initialize the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(std::stoi(Settings::getSetting("screenWidth")), std::stoi(Settings::getSetting("screenHeight")));
	glutCreateWindow("OpenGL First Window");

	glEnable(GL_DEPTH_TEST);
	// register callbacks
	glutDisplayFunc(renderScene);

	//initialize opengl functions
	glewInit();

}

void initGamepad() {
	input->getGamePadHandle(0, &gamePad);
}


int main(int argc, char **argv)
{
	//initialize our stuff
	initStatics();
	initOpengl(argc, argv);
	initObjects();
	initGamepad();

	glutMainLoop();

	return 0;
}



/*

int main(int argc, char* argv[])
{

	bool exit = false;
	Input i = Input();
	GamePad * gp = new GamePad();

	Audio a;

	int waitCounter = 0;
	int packet = 0;

	if (!i.getGamePadHandle(0, &gp))
		exit = true;

	DummyPosition * position = new DummyPosition(0, 1);
	//a.quePositionalSource(&position);


	while (!exit)
	{
		i.updateGamePads();
		if (packet != gp->currentPacket){
			packet = gp->currentPacket;
			if (gp->isPressed(gp->AButton))
				a.queStaticSource(0);
			if (gp->isPressed(gp->BButton))
				a.quePositionalSource(&position);

			if (gp->isPressed(gp->XButton))
				a.pauseSources();
			if (gp->isPressed(gp->YButton))
				a.resumeSources();
			if (gp->isPressed(gp->LShoulder))
				a.stopSources();
			if (gp->isPressed(gp->RShoulder))

				if (gp->isPressed(gp->StartButton))

					if (gp->isPressed(gp->BackButton))
					{
						std::cout << "back button pressed \n";
						i.releaseGamePadHandle(gp->getID(), &gp);
					}

		}
		position->setPosition(gp->getLeftStickX(), gp->getLeftStickY());
		a.update();


		//position->movePosition(gp->getLeftStickX(), gp->getRightStickY());




	}






	return 0;
}*/