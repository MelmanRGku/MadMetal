#pragma once

#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtc\type_ptr.hpp"
#include "../Libraries/glew/glew.h"
#include "../Global/Log.h"
#include "ShaderLoader.h"
#include "Objects\Light.h"
#include <iostream>

class ShaderProgram
{
public:
	static const GLuint POSITION_ATTRIBUTE_LOCATION = 0,
		COLOUR_ATTRIBUTE_LOCATION = 1,
		NORMAL_ATTRIBUTE_LOCATION = 2,
		UV_ATTRIBUTE_LOCATION = 3,
		TOTAL_NUMBER_OF_ATTRIBUTES = 4;

	ShaderProgram();
	~ShaderProgram();
	virtual void start(glm::mat4x4 *viewMatrix, glm::mat4x4 *projMatrix, glm::vec3 *cameraPos, std::vector<Light *> *thelights) {}
	virtual void end() {}

	GLfloat dynamicPositions[32 * 3];
	GLfloat dynamicColours[32 * 3];
	GLfloat dynamicCutoffs[32];

	GLfloat dynamicConstants[32];
	GLfloat dynamicLinears[32];
	GLfloat dynamicQuads[32];

	void loadLights(std::vector<Light *> *thelights)
	{
		for (int i = 0; i < 32; i++)
		{
			dynamicCutoffs[i],
				dynamicConstants[i],
				dynamicLinears[i],
				dynamicQuads[i] = 0.0;
		}
		for (int i = 0; i < 32 * 3; i++)
		{
			dynamicPositions[i],
			dynamicColours[i] =  0.0;
		}

		if (thelights != NULL)
		{
			for (int i = 0; i < thelights->size() || i == 32; i++)
			{
				dynamicPositions[i * 3] = thelights->at(i)->getPosition().x;
				dynamicPositions[i * 3 + 1] = thelights->at(i)->getPosition().y;
				dynamicPositions[i * 3 + 2] = thelights->at(i)->getPosition().z;
				std::cout << thelights->at(i)->getPosition().x << "   " << thelights->at(i)->getPosition().y << "    " << thelights->at(i)->getPosition().y << std::endl;
				dynamicColours[i * 3] = thelights->at(i)->dynamicColour.x;
				dynamicColours[i * 3 + 1] = thelights->at(i)->dynamicColour.y;
				dynamicColours[i * 3 + 2] = thelights->at(i)->dynamicColour.z;
				dynamicCutoffs[i] = thelights->at(i)->dynamicCutoff;
				dynamicConstants[i] = thelights->at(i)->dynamicConstant;
				dynamicLinears[i] = thelights->at(i)->dynamicLinear;
				dynamicQuads[i] = thelights->at(i)->dynamicQuad;

			}
		}
	}

};

