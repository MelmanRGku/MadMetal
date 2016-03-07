#pragma once
#include "Libraries\glew\glew.h"
#include "Libraries\freeglut\freeglut.h"
#include "Global\Settings.h"
#include "Global\Log.h"
#include "Scene Manager\StackManager.h"
#include "Global\Assets.h"
#include "Global\Fonts.h"

#define MAX_FPS (60)
#define MIN_DT (1000 / MAX_FPS)

StackManager * m_stackManager;
float lastDrawCallTime = 0;
//ParticleSystem * psystem = new ParticleSystem(10000);

void initStatics(){
	//load settings from a file
	Settings::loadSettingsFromFile("settings.txt");
	//enable\disable logging based on the setting
	Log::enableLogging(std::stoi(Settings::getSetting("debugEnabled")) == 0 ? false : true);
	//initialize assets and load all objs
	Assets::init();
	Fonts::init();
}

void initObjects()
{
	//	psystem->initSystem(glutGet(GLUT_ELAPSED_TIME));
	Fonts::loadTTFFontsFromDirectory("Assets/Fonts");
	m_stackManager = new StackManager();
}

void renderScene(void)
{
	int currentDrawCallTime = glutGet(GLUT_ELAPSED_TIME);
	int dt = currentDrawCallTime - lastDrawCallTime;
	if (dt < MIN_DT)
		return;
	lastDrawCallTime = currentDrawCallTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3, 0.3, 0.3, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	m_stackManager->progressScene(dt);
	glutSwapBuffers();

	//glutPostRedisplay();
}

void initOpengl(int argc, char **argv) {
	//initialize the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(std::stoi(Settings::getSetting("screenWidth")), std::stoi(Settings::getSetting("screenHeight")));
	glutCreateWindow("OpenGL First Window");

	glEnable(GL_DEPTH_TEST);
	// register callbacks
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	//initialize opengl functions
	glewInit();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char **argv)
{
	initStatics();
	initOpengl(argc, argv);
	initObjects();

	glutMainLoop();

	return 0;
}



