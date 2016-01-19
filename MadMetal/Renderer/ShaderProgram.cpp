#include "ShaderProgram.h"

/*
	Constructor. Takes path to the vertex shader and fragment shader,
	loads them, links them and stores all the needed information (programID, attributes
	and uniforms) in its instance variables.
*/
ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath){
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

	//get and store all the attributes and uniforms
	positionAttribute = glGetAttribLocation(programID, "position_attr");
	colourAttribute = glGetAttribLocation(programID, "colour_attr");
	normalAttribute = glGetAttribLocation(programID, "normal_attr");
	uvAttribute = glGetAttribLocation(programID, "texcoords_attr");
	projectionMatrixUniform = glGetUniformLocation(programID, "proj_matrix");
	viewMatrixUniform = glGetUniformLocation(programID, "view_matrix");
	modelMatrixUniform = glGetUniformLocation(programID, "model_matrix");
	textureUniform = glGetUniformLocation(programID, "texObject");
	textureValidUniform = glGetUniformLocation(programID, "texValid");

}


ShaderProgram::~ShaderProgram()
{
}
