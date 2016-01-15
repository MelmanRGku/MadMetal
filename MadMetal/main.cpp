#include "Libraries\glew\glew.h"
#include "Libraries\glut\glut.h"
#include "Renderer\ShaderProgram.h"
#include "Global\Settings.h"
#include "Global\Debug.h"
#include <iostream>

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.3, 0.3, 1.0);

	glutSwapBuffers();
}

void settingsTest() {
	Settings *s = new Settings("settings.txt");
	std::cout << s->getSetting("Team") << std::endl;
	std::cout << s->getSetting("ASD") << std::endl;
	std::cout << s->getSetting("jfiwe") << std::endl;
	s->setSetting("grer", "some other weird Value");
	std::cout << s->getSetting("grer") << std::endl;
	s->storeToFile("settings.txt");
}

void init() {
	Debug::init("debug.txt");
	Debug::enableDebug();
}

int main(int argc, char **argv)
{
	init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL First Window");
	
	glEnable(GL_DEPTH_TEST);
	// register callbacks
	glutDisplayFunc(renderScene);

	glewInit();


	ShaderProgram *sp = new ShaderProgram("Renderer/VertexShader.glsl", "Renderer/FragmentShader.glsl");


	glutMainLoop();

	return 0;
}