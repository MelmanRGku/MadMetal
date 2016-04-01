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
}


CellShaderProgram::~CellShaderProgram()
{
}

void CellShaderProgram::start(glm::mat4x4 *viewMatrix, glm::mat4x4 *projMatrix, glm::vec3 *cameraPos) {
	//tether the program
	glUseProgram(programID);


	//set view and projection matrices
	glUniformMatrix4fv(viewMatrixUniform, 1, false, glm::value_ptr(*viewMatrix));
	glUniformMatrix4fv(projectionMatrixUniform, 1, false, glm::value_ptr(*projMatrix));
	glUniformMatrix3fv(cameraPosUniform, 1, false, glm::value_ptr(*cameraPos));
	GLfloat testArray[30] = { 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	glUniform3fv(lightPosUniform, 30, testArray);

	GLfloat testArray2[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	GLfloat testArray3[10] = { 0.01, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	GLfloat testArray4[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	glUniform1fv(constUniform, 10, testArray2);
	glUniform1fv(linearUniform, 10, testArray3);
	glUniform1fv(quadUniform, 10, testArray4);
}

void CellShaderProgram::end() {
	glUseProgram(0);
}