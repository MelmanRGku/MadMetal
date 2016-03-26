#include "Renderer.h"
#include <FTGL/ftgl.h>
#include "Global\Fonts.h"
#include "Objects\Camera.h"
#include "Objects\TestObject.h"
#include "Game Logic\PlayerControllable.h"
#include "Libraries\freeglut\freeglut.h"

/*
	Constructor.
	TODO: definitely change this. This was done for testing purposes
	*/
Renderer::Renderer()
{
	float windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	float windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

	defaultProjectionMatrix = projectionMatrix = glm::perspective(
		glm::radians(std::stof(Settings::getSetting("fovy"))),
		windowWidth / windowHeight,
		0.5f,
		1000.f
		);

	viewMatrix = glm::lookAt(
		glm::vec3(50, 3, 50),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
		);

	recalculateViewPorts(windowWidth, windowHeight);
}


Renderer::~Renderer()
{
	for (int i = 0; i < NUMBER_OF_SHADER_TYPES; i++) {
		delete shader[i];
	}
}

void Renderer::setViewMatrixLookAt(glm::vec3 pos, glm::vec3 up, glm::vec3 lookAt)
{
	viewMatrix = glm::lookAt(
		pos,
		lookAt,
		up
		);
}

//todo: split screen
void Renderer::setViewMatrixLookAt(std::vector<Camera *> cameras)
{
	//currently will just get the first camera in the list and set view matrix to that
	viewMatrix = glm::lookAt(
		cameras[0]->getPosition(),
		cameras[0]->getLookAt(),
		cameras[0]->getUpVector()
		);
}

void Renderer::recalculateViewPorts(float windowWidth, float windowHeight) {
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	viewPorts.clear();
	std::vector<glm::vec4> viewPortDesc;

	//1 player
	viewPortDesc.clear();
	viewPortDesc.push_back(glm::vec4(0, 0, windowWidth, windowHeight));
	viewPorts.push_back(viewPortDesc);

	//2 players
	viewPortDesc.clear();
	viewPortDesc.push_back(glm::vec4(0, windowHeight / 2, windowWidth, windowHeight / 2));
	viewPortDesc.push_back(glm::vec4(0, 0, windowWidth, windowHeight / 2));
	viewPorts.push_back(viewPortDesc);

	//3 players
	viewPortDesc.clear();
	viewPortDesc.push_back(glm::vec4(0, windowHeight / 2, windowWidth / 2, windowHeight / 2));
	viewPortDesc.push_back(glm::vec4(windowWidth / 2, windowHeight / 2, windowWidth / 2, windowHeight / 2));
	viewPortDesc.push_back(glm::vec4(0, 0, windowWidth, windowHeight / 2));
	viewPorts.push_back(viewPortDesc);

	//4 players
	viewPortDesc.clear();
	viewPortDesc.push_back(glm::vec4(0, windowHeight / 2, windowWidth / 2, windowHeight / 2));
	viewPortDesc.push_back(glm::vec4(windowWidth / 2, windowHeight / 2, windowWidth / 2, windowHeight / 2));
	viewPortDesc.push_back(glm::vec4(0, 0, windowWidth / 2, windowHeight / 2));
	viewPortDesc.push_back(glm::vec4(windowWidth / 2, 0, windowWidth / 2, windowHeight / 2));
	viewPorts.push_back(viewPortDesc);
}

void Renderer::setShader(ShaderType type, ShaderProgram *sp) {
	shader[type] = sp;
}

void Renderer::draw(std::vector<TestObject *> *objects, std::vector<PlayerControllable *> *players) {
	std::vector<glm::vec4> viewPortDesc;

	if (players == NULL) {
		viewPortDesc = viewPorts.at(0);
		projectionMatrix = defaultProjectionMatrix;
		totalNumberOfViewPorts = 1;
	}
	else {
		viewPortDesc = viewPorts.at(players->size() - 1);
		totalNumberOfViewPorts = players->size();
	}

	for (int j = 0; j < viewPortDesc.size(); j++) {
		if (players != NULL) {
			projectionMatrix = glm::perspective(
				glm::radians(std::stof(Settings::getSetting("fovy")) + 0.3f * max(players->at(j)->getCar()->getCar().computeForwardSpeed(), 1) + 30),
				windowWidth / windowHeight,
				0.5f,
				1000.f
				);
			viewMatrix = players->at(j)->getCamera()->getMatrix();
		}
		currentViewPort = viewPortDesc.at(j);
		glViewport(currentViewPort.x, currentViewPort.y, currentViewPort.z, currentViewPort.w);
		bool keepGoing = false;
		int passNumber = 1;
		do {
			keepGoing = false;
			for (int i = 0; i < NUMBER_OF_SHADER_TYPES; i++) {
				if (shader[i] != NULL) {
					shader[i]->start(&viewMatrix, &projectionMatrix);
					for (unsigned int j = 0; j < objects->size(); j++) {
						TestObject *obj = objects->at(j);
						keepGoing = keepGoing || obj->draw(this, (ShaderType)i, passNumber);
					}
					if (players != NULL) {
						keepGoing = keepGoing || players->at(j)->getCar()->getUI()->draw(this, (ShaderType)i, passNumber);
					}
					shader[i]->end();
				}
			}
			passNumber++;
		} while (keepGoing);
	}
}