#include "ShaderLoader.h"
#include "Files\FIleHandlingHelpers.h"

ShaderLoader::ShaderLoader()
{
}

ShaderLoader::~ShaderLoader()
{
}

/*
	Loads vertex and fragment shaders. Compiles and links them together.
	Returns the program ID
*/
GLuint ShaderLoader::loadShaders(const char* vertexShaderPath, const char* fragmentShaderPath) {

	GLint result = GL_FALSE;
	int logLength;

	//create two default shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Read shaders into strings
	std::string vertexShaderCode = FileHandlingHelpers::readFile(vertexShaderPath);
	std::string fragmentShaderCode = FileHandlingHelpers::readFile(fragmentShaderPath);
	const char *vertexShaderCodeChar = vertexShaderCode.c_str();
	const char *fragmentShaderCodeChar = fragmentShaderCode.c_str();

	// Compile vertex shader
	Log::writeLine("Compiling vertex shader.");
	glShaderSource(vertexShader, 1, &vertexShaderCodeChar, NULL);
	glCompileShader(vertexShader);

	// Check vertex shader
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
		Log::writeLine("Error occurred when compiling vertex shader.");
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> vertexShaderErrorLog((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(vertexShader, logLength, NULL, &vertexShaderErrorLog[0]);
	Log::writeLine(&vertexShaderErrorLog[0]);

	// Compile fragment shader
	Log::writeLine("Compiling fragment shader.");
	glShaderSource(fragmentShader, 1, &fragmentShaderCodeChar, NULL);
	glCompileShader(fragmentShader);

	// Check fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
		Log::writeLine("Error occurred when compiling fragment shader.");
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> fragmentShaderErrorLog((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(fragmentShader, logLength, NULL, &fragmentShaderErrorLog[0]);
	Log::writeLine(&fragmentShaderErrorLog[0]);

	// Link shaders together into a program
	Log::writeLine("Linking program");
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	// Check linking
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
		Log::writeLine("Error occurred when linking shaders.");
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> programErrorLog((logLength > 1) ? logLength : 1);
	glGetProgramInfoLog(program, logLength, NULL, &programErrorLog[0]);
	Log::writeLine(&programErrorLog[0]);

	// Clean up
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}