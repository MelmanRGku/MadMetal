#pragma once
#include "Settings.h"
#include "Libraries\glew\glew.h"
#include "Libraries\freeglut\freeglut.h"
#include "Global\Settings.h"
#include "Global\Log.h"
#include "Scene Manager\StackManager.h"
#include "Global\Assets.h"
#include "Global\Fonts.h"

#ifdef _USE_MEMORY_LEAK_DETECTOR
	#include <vld.h>
#endif

#define MAX_FPS (60)
#define MIN_DT (1000 / MAX_FPS)

StackManager * m_stackManager;
float lastDrawCallTime = 0;

void setVSync(bool sync)
{
	// Function pointer for the wgl extention function we need to enable/disable
	// vsync
	typedef BOOL(APIENTRY *PFNWGLSWAPINTERVALPROC)(int);
	PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

	const char *extensions = (char*)glGetString(GL_EXTENSIONS);

	if (strstr(extensions, "WGL_EXT_swap_control") == 0)
	{
		return;
	}
	else
	{
		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");

		if (wglSwapIntervalEXT)
			wglSwapIntervalEXT(sync);
	}
}

void initStatics(){
	//load settings from a file
	Settings::init();
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
	std::cout << "FPS: " << (1000.f / dt) << std::endl;
	lastDrawCallTime = currentDrawCallTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3, 0.3, 0.3, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (m_stackManager->progressScene(dt))
		glutLeaveMainLoop();
	glutSwapBuffers();

	//glutPostRedisplay();
}

void close() {
	delete m_stackManager;
	//delete assets
	Assets::release();
	Fonts::release(); 
	Settings::release();
}

void onWindowResize(int width, int height) {
	m_stackManager->onWindowResize(width, height);
}

void initOpengl(int argc, char **argv) {
	//initialize the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(std::stoi(Settings::getSetting("screenWidth")), std::stoi(Settings::getSetting("screenHeight")));
	glutCreateWindow("MadMetal");

#ifdef FULL_SCREEN
	glutFullScreen();
#endif
	// register callbacks
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutCloseFunc(close);
	glutReshapeFunc(onWindowResize);
	//initialize opengl functions
	glewInit();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	setVSync(false);
}

int main(int argc, char **argv)
{
	initStatics();
	initOpengl(argc, argv);
	initObjects();

	glutMainLoop();

	return 0;
}



