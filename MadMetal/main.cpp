#include "Libraries\glew\glew.h"
#include "Libraries\glut\glut.h"
#include "Renderer\ShaderProgram.h"
#include "Renderer\Renderer.h"
#include "Objects\ObjModel.h"
#include "Global\Settings.h"
#include "Global\Log.h"
#include <iostream>

Renderer *r;
ObjModel *om;

void renderScene(void)
{
	std::cout << 1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.3, 0.3, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//initialize drawing
	r->startDrawing();
	//draw the obj model
	r->draw(om);
	//uninitialize drawing
	r->stopDrawing();

	glutSwapBuffers();
}

void rendererTest() {
	//create a renderer and give it the shader program
	r = new Renderer();
	ShaderProgram *sp = new ShaderProgram("Renderer/VertexShader.glsl", "Renderer/FragmentShader.glsl");
	r->setShader(sp);
	//load obj model from a file 
	om = new ObjModel();
	om->loadFromFile("Assets/Models/Stormtrooper.obj");
}

void init() {
	//load settings from a file
	Settings::loadSettingsFromFile("settings.txt");
	//initialize the debug (log)
	Log::init("debug.txt");
	//enable\disable logging based on the setting
	Log::enableLogging(std::stoi(Settings::getSetting("debugEnabled")));
}

int main(int argc, char **argv)
{
	//initialize our stuff
	init();

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

	//initialize the renderer test
	rendererTest();

	glutMainLoop();

	return 0;
}