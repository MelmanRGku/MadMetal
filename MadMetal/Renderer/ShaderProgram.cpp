#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath){
	ShaderLoader *sl = new ShaderLoader();
	programID = sl->loadShaders(vertexShaderPath, fragmentShaderPath);
	delete sl;

	char *line = new char[50]; 
	sprintf_s(line, 50, "New shader loaded with program ID %u", programID);
	Debug::writeLine(line);
	delete[] line;


}


ShaderProgram::~ShaderProgram()
{
}
