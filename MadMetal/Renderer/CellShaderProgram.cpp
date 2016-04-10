#include "CellShaderProgram.h"
#include <iostream>
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

	lightPosDynamic = glGetUniformLocation(programID, "lightPosArrayDynamic");
	constDynamic = glGetUniformLocation(programID, "constArrayDynamic");
	linearDynamic = glGetUniformLocation(programID, "linearArrayDynamic");
	quadDynamic = glGetUniformLocation(programID, "quadArrayDynamic");
	lightDynamic = glGetUniformLocation(programID, "lightColorArrayDynamic");
	cutoffDynamic = glGetUniformLocation(programID, "cutoffArrayDynamic");


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
	GLfloat testArray[30] = { 100, 10, 100, 130, 10, 440, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	GLfloat lightArray[30] = { 1.0, 1.0, 1.0, 0.0, 1.0, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	GLfloat testArray2[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	GLfloat testArray3[10] = { 0.01, 0.01, 0, 0, 0, 0, 0, 0, 0, 0 };
	GLfloat testArray4[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


	glUniform3fv(lightPosUniform, 10, testArray);

//	glm::vec3 lightArray[10] = { glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0) };

	glUniform3fv(lightUniform, 10, lightArray);

	glUniform1fv(constUniform, 10, testArray2);
	glUniform1fv(linearUniform, 10, testArray3);
	glUniform1fv(quadUniform, 10, testArray4);

	GLfloat cutArray[10] = { 500.0, 100.0, 0, 0, 0, 0, 0, 0, 0, 0 };
	glUniform1fv(cutoffUniform, 10, cutArray);

	glUniform3fv(lightPosDynamic, 32, dynamicPositions);
	glUniform3fv(lightDynamic, 32, dynamicColours);

	glUniform1fv(constDynamic, 10, dynamicConstants);
	glUniform1fv(linearDynamic, 10, dynamicLinears);
	glUniform1fv(quadDynamic, 10, dynamicQuads);

	glUniform1fv(cutoffDynamic, 10, dynamicCutoffs);


}

void CellShaderProgram::end() {
	glUseProgram(0);
}