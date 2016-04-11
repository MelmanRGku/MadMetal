#include "CellShaderProgram.h"
#include <iostream>
#include "Objects\Light.h"
/*
	Constructor. Takes path to the vertex shader and fragment shader,
	loads them, links them and stores all the needed information (programID, attributes
	and uniforms) in its instance variables.
*/
CellShaderProgram::CellShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath){
	//create the shader loader and create the program
	ShaderLoader *sl = new ShaderLoader();
	programID = sl->loadShaders(vertexShaderPath, fragmentShaderPath);
	delete sl;

	//this is mostly useless.
	//TODO: remove this
	char *line = new char[50]; 
	sprintf_s(line, 50, "New shader loaded with program ID %u", programID);
	Log::writeLine(line);
	delete[] line;

	//get and store all the uniforms
	projectionMatrixUniform = glGetUniformLocation(programID, "proj_matrix");
	viewMatrixUniform = glGetUniformLocation(programID, "view_matrix");
	modelMatrixUniform = glGetUniformLocation(programID, "model_matrix");
	textureUniform = glGetUniformLocation(programID, "texObject");
	textureValidUniform = glGetUniformLocation(programID, "texValid");
	cameraPosUniform = glGetUniformLocation(programID, "camera_pos");


	bitmaskUniform = glGetUniformLocation(programID, "bitmask");		//pos of the camera
	lightPosUniform = glGetUniformLocation(programID, "lightPosArray");
	constUniform = glGetUniformLocation(programID, "constArray");
	linearUniform = glGetUniformLocation(programID, "linearArray");
	quadUniform = glGetUniformLocation(programID, "quadArray");
	lightUniform = glGetUniformLocation(programID, "lightColorArray");
	cutoffUniform = glGetUniformLocation(programID, "cutoffArray");


}


CellShaderProgram::~CellShaderProgram()
{
}

void CellShaderProgram::start(glm::mat4x4 *viewMatrix, glm::mat4x4 *projMatrix, glm::vec3 *cameraPos, std::vector<Light *> *thelights) {
	//tether the program
	glUseProgram(programID);

	loadLights(thelights);

	//set view and projection matrices
	glUniformMatrix4fv(viewMatrixUniform, 1, false, glm::value_ptr(*viewMatrix));
	glUniformMatrix4fv(projectionMatrixUniform, 1, false, glm::value_ptr(*projMatrix));
	glUniformMatrix3fv(cameraPosUniform, 1, false, glm::value_ptr(*cameraPos));

	glUniform3fv(lightPosUniform, MAX_NUM_OF_LIGHTS, lightPositions);
	glUniform3fv(lightUniform, MAX_NUM_OF_LIGHTS, lightColours);
	glUniform1fv(constUniform, MAX_NUM_OF_LIGHTS, lightConstants);
	glUniform1fv(linearUniform, MAX_NUM_OF_LIGHTS, lightLinears);
	glUniform1fv(quadUniform, MAX_NUM_OF_LIGHTS, lightQuads);
	glUniform1fv(cutoffUniform, MAX_NUM_OF_LIGHTS, lightCutoffs);


}

void CellShaderProgram::end() {
	glUseProgram(0);
}

void CellShaderProgram::loadLights(std::vector<Light *> *lights)
{
	memset(lightCutoffs, 0, sizeof(lightCutoffs));
	memset(lightConstants, 0, sizeof(lightConstants));
	memset(lightLinears, 0, sizeof(lightLinears));
	memset(lightQuads, 0, sizeof(lightQuads));
	memset(lightPositions, 0, sizeof(lightPositions));
	memset(lightColours, 0, sizeof(lightColours));

	if (lights != NULL)
	{
		for (int i = 0; i < lights->size() || i == MAX_NUM_OF_LIGHTS; i++)
		{
			lightPositions[i * 3] = lights->at(i)->getAnimatablePos().x;
			lightPositions[i * 3 + 1] = lights->at(i)->getAnimatablePos().y;
			lightPositions[i * 3 + 2] = lights->at(i)->getAnimatablePos().z;
			lightColours[i * 3] = lights->at(i)->colour.x;
			lightColours[i * 3 + 1] = lights->at(i)->colour.y;
			lightColours[i * 3 + 2] = lights->at(i)->colour.z;
			lightCutoffs[i] = lights->at(i)->cutoff;
			lightConstants[i] = lights->at(i)->constant;
			lightLinears[i] = lights->at(i)->linear;
			lightQuads[i] = lights->at(i)->quad;

		}
	}
}