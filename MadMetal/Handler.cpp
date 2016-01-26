#include "Libraries\glew\glew.h"
#include "Libraries\glut\glut.h"
#include "Renderer\ShaderProgram.h"
#include "Renderer\Renderer.h"
#include "Objects\ObjModel.h"
#include "Global\Settings.h"
#include "Global\Log.h"
#include "Input\Input.h"
#include "Simulation\Simulation.h"
#include <iostream>

Renderer *renderer;
Input *input;
Simulation *simulation;

void renderScene(void)
{
	std::cout << "Begining new Game cycle.... \n";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.3, 0.3, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	input->update();
	simulation->simulate();
	renderer->draw(simulation->getGameWorld()->getGameObjects());

	glutSwapBuffers();
	std::cout << "Game Cycle finished.... \n\n";
}

void initStatics() {
	//load settings from a file
	Settings::loadSettingsFromFile("settings.txt");
	//initialize the debug (log)
	Log::init("debug.txt");
	//enable\disable logging based on the setting
	Log::enableLogging(std::stoi(Settings::getSetting("debugEnabled")));
}

void initObjects() {
	input = new Input();
	simulation = new Simulation();
	simulation->setupBasicGameWorldObjects();

	//create a renderer and give it the shader program
	renderer = new Renderer();
	ShaderProgram *sp = new ShaderProgram("Renderer/VertexShader.glsl", "Renderer/FragmentShader.glsl");
	renderer->setShader(sp);
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

int main(int argc, char **argv)
{
	//initialize our stuff
	initStatics();
	initOpengl(argc, argv);
	initObjects();

	glutMainLoop();

	return 0;
}