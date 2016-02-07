#pragma once
#include "Libraries\glew\glew.h"
#include "Libraries\glut\glut.h"
#include "ParticleSystem\ParticleSystem.h"
#include "Renderer\ShaderProgram.h"
#include "Renderer\Renderer.h"
#include "Global\Settings.h"
#include "Global\Log.h"
#include "Input\Input.h"
#include "Simulation\GameSimulation.h"
#include "Simulation\Scene.h"
#include <iostream>
#include <windows.h>
#include "Scene Manager\StackManager.h"


Renderer *renderer;
StackManager * m_stackManager;
float lastDrawCallTime = 0;
//ParticleSystem * psystem = new ParticleSystem(10000);

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

	//simulation = new Simulation();
	//simulation->setupBasicGameWorldObjects();

	//create a renderer and give it the shader program
	renderer = new Renderer();
	ShaderProgram *sp = new ShaderProgram("Renderer/VertexShader.glsl", "Renderer/FragmentShader.glsl");
	renderer->setShader(sp);

	psystem->initSystem(glutGet(GLUT_ELAPSED_TIME));
	m_stackManager = new StackManager();
}

//MAIN GAME LOOP
//TODO:: Clean up function be giving it a more accurate name, and moving rendering specif code to the renderer
//TODO:: Enforce 60fps to ensure the physics system doesn't flip out. i.e. Insert a condition after the dt is calculated that ensures the correct timestep has passed

void renderScene(void)
{
	float currentDrawCallTime = (float)glutGet(GLUT_ELAPSED_TIME);
	float dt = currentDrawCallTime - lastDrawCallTime;
	if (dt > 33)
		dt = 33;
	lastDrawCallTime = currentDrawCallTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//input->updateGamePads();
	//simulation->simulate();
	//psystem->update(glutGet(GLUT_ELAPSED_TIME));
	//renderer->draw(psystem);
	//renderer->draw(simulation->getGameWorld()->getGameObjects());

	//updateSound();
	m_stackManager->progressScene(glutGet(GLUT_ELAPSED_TIME));
	glutSwapBuffers();

	//glutPostRedisplay();
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
	glutIdleFunc(renderScene);
	//initialize opengl functions
	glewInit();

}

//void initGamepad() {
	//input->getGamePadHandle(&gamePad);
//}


int main(int argc, char **argv)
{
	//initialize our stuff
	initStatics();
	initOpengl(argc, argv);
	initObjects();
	

	glutMainLoop();

	return 0;
}



